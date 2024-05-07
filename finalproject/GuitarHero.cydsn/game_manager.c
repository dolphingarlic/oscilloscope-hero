/* ========================================
 *
 * Copyright Andi Qu, 2024
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF ANDI QU.
 *
 * ========================================
 */

#include <game_manager.h>
#include <FS.h>
#include <stdlib.h>

static struct Note notes[1000];
static float barlines[1000];

struct GameState new_game(char *song_name) {
    int n_notes = 0;
    float tempo = 0;
    float duration = 0;
    // Parse the notes from a chart file
    FS_FILE *chart_file = FS_FOpen(song_name, "r");
    if (chart_file) {
        int buffer_len;
        int float_len = 0;
        char buffer[512], curr_float[10];
        uint8 parse_mode = 0;
        while ((buffer_len = FS_Read(chart_file, buffer, sizeof(buffer)))) {
            for (int i = 0; i < buffer_len; i++) {
                switch (parse_mode) {
                    case 2: // Track
                        notes[n_notes].track = buffer[i] - '0';
                        notes[n_notes].played = 0;
                    case 3: // Whitespace
                        parse_mode++;
                        break;
                    case 4: // Note time
                    case 0: // Tempo
                    case 1: // Song duration
                        if (buffer[i] == '\n') {
                            if (parse_mode == 4) {
                                notes[n_notes++].time = atof(curr_float);
                                parse_mode -= 3;
                            } else if (parse_mode == 0) {
                                tempo = atof(curr_float);
                            } else if (parse_mode == 1)
                                duration = atof(curr_float);
                            parse_mode++;
                            // Reset the float buffer
                            float_len = 0;
                            for (int j = 0; j < 10; j++)
                                curr_float[j] = 0;
                        } else {
                            curr_float[float_len++] = buffer[i];
                        }
                }
            }
        }
    }
    
    // TODO: Generate barlines too
    
    return (struct GameState) {
        .song = (struct Song) { .tempo = tempo, .duration = duration },
        .time = 0,
        .score = 0,
        .n_notes = n_notes,
        .notes = notes,
        .notes_window = {0, 0},
        .n_barlines = 0,
        .barlines = barlines,
        .barlines_window = {0, 0}
    };
}

static int obj_pos(struct GameState *state, float obj_time) {
    return (int)(256 * 60 * (obj_time - state->time) / state->song.tempo) + 5;
}

void tick(struct GameState *state) {
    if (state->time > state->song.duration) return;
    state->time += 0.05;
    // Update sliding windows
    while (state->notes_window.r < state->n_notes) {
        int y = obj_pos(state, state->notes[state->notes_window.r].time);
        if (y < UINT8_MAX) state->notes_window.r++;
        else break;
    }
    while (state->notes_window.l < state->notes_window.r) {
        int y = obj_pos(state, state->notes[state->notes_window.l].time);
        if (y < -10) state->notes_window.l++;
        else break;
    }
    while (state->barlines_window.r < state->n_barlines) {
        int y = obj_pos(state, state->barlines[state->barlines_window.r]) + 5;
        if (y < UINT8_MAX) state->barlines_window.r++;
        else break;
    }
    while (state->barlines_window.l < state->barlines_window.r) {
        int y = obj_pos(state, state->barlines[state->barlines_window.l]) + 5;
        if (y < 0) state->barlines_window.l++;
        else break;
    }
}

void update_score(struct GameState *state, uint8 mask) {
    int new_score = state->score;
    for (int i = 0; i < 5; i++) {
        if (mask & (1 << i)) {
            uint8 hit = 0;
            // Realistically, we only need to check up to 10 notes
            for (int j = state->notes_window.l; j < state->notes_window.r && j < state->notes_window.l + 10; j++) {
                if (state->notes[j].track != i || state->notes[j].played)
                    continue;
                // Calculate the score and break if non-zero
                float delta = state->notes[j].time - state->time;
                if (delta < 0) delta = -delta;
                float max_delta = 10 * 2 * state->song.tempo / 60 / 256;
                if (delta < max_delta) {
                    new_score += (int)(100 * (1 - delta / max_delta));
                    state->notes[j].played = 1;
                    hit = 1;
                    break;
                }
            }
            // Check that every note is hit to prevent spamming
            if (hit == 0) return;
        }
    }
    state->score = new_score;
}

int create_sprites(struct GameState *state, struct Sprite *sprites) {
    // Recall that the fretboard holds 8 beats, and tempo is in BPM
    int n = 0;
    for (int i = state->notes_window.l; i < state->notes_window.r; i++) {
        // +5 because the target indicators are offset by +5
        int y = obj_pos(state, state->notes[i].time);
        sprites[n++] = make_ellipse(state->notes[i].track, y, state->notes[i].played);
    }
    for (int i = state->barlines_window.l; i < state->barlines_window.r; i++) {
        // +10 because of the aforementioned offset, plus half the height of an ellipse
        int y = obj_pos(state, state->barlines[i]) + 5;
        sprites[n++] = make_barline(y);
    }
    return n;
}

/* [] END OF FILE */
