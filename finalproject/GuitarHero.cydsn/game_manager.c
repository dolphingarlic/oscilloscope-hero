/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include <game_manager.h>

static struct Note notes[1000];
static float barlines[1000];

struct GameState new_game() {
    // Approximates the Tetris theme w/o audio
    notes[0] = (struct Note) { .track = 4, .time = 2, .played = 0 };
    notes[1] = (struct Note) { .track = 1, .time = 2.5, .played = 0 };
    notes[2] = (struct Note) { .track = 2, .time = 2.75, .played = 0 };
    notes[3] = (struct Note) { .track = 3, .time = 3, .played = 0 };
    notes[4] = (struct Note) { .track = 2, .time = 3.5, .played = 0 };
    notes[5] = (struct Note) { .track = 1, .time = 3.75, .played = 0 };
    notes[6] = (struct Note) { .track = 0, .time = 4, .played = 0 };
    notes[7] = (struct Note) { .track = 0, .time = 4.5, .played = 0 };
    notes[8] = (struct Note) { .track = 2, .time = 4.75, .played = 0 };
    notes[9] = (struct Note) { .track = 4, .time = 5, .played = 0 };
    notes[10] = (struct Note) { .track = 3, .time = 5.5, .played = 0 };
    notes[11] = (struct Note) { .track = 2, .time = 5.75, .played = 0 };
    notes[12] = (struct Note) { .track = 1, .time = 6, .played = 0 };
    notes[13] = (struct Note) { .track = 2, .time = 6.75, .played = 0 };
    notes[14] = (struct Note) { .track = 3, .time = 7, .played = 0 };
    notes[15] = (struct Note) { .track = 4, .time = 7.5, .played = 0 };
    notes[16] = (struct Note) { .track = 2, .time = 8, .played = 0 };
    notes[17] = (struct Note) { .track = 0, .time = 8.5, .played = 0 };
    notes[18] = (struct Note) { .track = 0, .time = 9, .played = 0 };
    
    for (int i = 0; i < 9; i++)
        barlines[i] = i + 2;
    
    return (struct GameState) {
        .song = (struct Song) { .tempo = 120, .duration = 12 },
        .time = 0,
        .score = 0,
        .n_notes = 19,
        .notes = notes,
        .notes_window = {0, 0},
        .n_barlines = 9,
        .barlines = barlines,
        .barlines_window = {0, 0}
    };
}

static int obj_pos(struct GameState *state, float obj_time) {
    return (int)((256 / 2) * 60 * (obj_time - state->time) / state->song.tempo) + 5;
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
