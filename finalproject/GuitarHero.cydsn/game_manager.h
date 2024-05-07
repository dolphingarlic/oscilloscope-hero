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

#include "cytypes.h"
#include <sprites.h>

#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

struct Song {
    // Tempo in BPM
    float tempo;
    // Duration in seconds
    float duration;
};

struct Note {
    uint8 track;
    float time;
    uint8 played;
};

struct GameState {
    // Each frame can hold 2 bars (8 beats)
    struct Song song;
    float time;
    int score;
    // Sprite data
    int n_notes;
    struct Note *notes;
    int n_barlines;
    float *barlines;
    // Sliding window for keeping track of notes to render
    struct RenderWindow {
        int l;
        int r;
    } notes_window, barlines_window;
};

/*
 * Starts a new game
 */
struct GameState new_game(char *song_name);

/*
 * Updates the state of the game at 20 FPS
 */
void tick(struct GameState *state);

/*
 * Translates a keypress into a score update
 */
void update_score(struct GameState *state, uint8 mask);

/*
 * Creates new sprites, given the current state of the game
 */
int create_sprites(struct GameState *state, struct Sprite *sprites);

#endif

/* [] END OF FILE */
