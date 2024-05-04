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
#include <FS.h>
#include <project.h>
#include <math.h>
#include <game_manager.h>
#include <sprites.h>

// Game data
int n_sprites;
uint8 indicator_countdown[5];
struct Sprite sprites[1<<5];
struct GameState game_state;

// Global rendering variables
int n_points;
struct Point points[1<<10];
uint8 new_flag;
int new_n_points;
struct Point new_points[1<<10];

// File I/O stuff
#define N_BUFFERS 4
#define BUFFER_LEN 4096
FS_FILE *audio_file;
int buffer_len[N_BUFFERS];
int fill_buffer, play_buffer, play_idx;
uint8 audio_done;
uint8 buffer[N_BUFFERS][BUFFER_LEN];

// Declare custom ISRs
CY_ISR_PROTO(FPS_isr);
CY_ISR_PROTO(BLE_Rx_isr);
CY_ISR_PROTO(Audio_isr);

/*
 * Initialize the system hardware
 */
void hw_init() {
    x_DAC_Start();
    y_DAC_Start();
    Audio_DAC_Start();
    
    LCD_Start();
    LCD_ClearDisplay();
    LCD_Position(0, 0);
    
    BLE_UART_Init();
    BLE_UART_Start();

    FPS_isr_StartEx(FPS_isr);
    BLE_Rx_isr_StartEx(BLE_Rx_isr);
    
    FS_Init();
}

/*
 * Start a new game of Guitar Hero
 */
void game_init() {
    init_sprites();
    
    // Set up the game frame
    n_sprites = 0;
    sprites[n_sprites++] = make_fretboard();
    for (int i = 0; i < 5; i++) {
        sprites[n_sprites++] = make_ellipse(i, 5, 0);
    }
    
    game_state = new_game();
}

/*
 * Loads a song from the SD card and begins playback
 */
void audio_init() {
    char wav_filename[14] = "feelgood.wav";
    audio_file = FS_FOpen(wav_filename, "r");
    if (audio_file) {
        for (int i = 0; i < N_BUFFERS; i++) {
            buffer_len[i] = FS_Read(audio_file, buffer[i], BUFFER_LEN);
        }
        fill_buffer = 0, play_buffer = 0, play_idx = 0;
        audio_done = 0;
        Audio_isr_StartEx(Audio_isr);
    }
}

/*
 * Given a list of points, draws a polygon connecting them
 * on the oscilloscope using the DAC
 */
void draw_points() {   
    for (int i = 0; i < n_points; i++) {
        x_DAC_SetValue(points[i].x);
        y_DAC_SetValue(points[i].y);
    }
}

/*
 * Updates the list of points to render
 */
void update_render() {
    // Decrement feedback counter 
    for (int i = 0; i < 5; i++) {
        if (indicator_countdown[i]) {
            sprites[i + 1] = make_ellipse(i, 5, 1);
            indicator_countdown[i]--;
        } else {
            sprites[i + 1] = make_ellipse(i, 5, 0);
        }
    }
    // Update sprites
    n_sprites = create_sprites(&game_state, sprites + 6) + 6;
    // Convert to polyline
    new_n_points = sprites_to_polyline(n_sprites, sprites, new_points);
    // Convert to perspective
    ortho_to_perspective(new_n_points, new_points);
    // Signal that a new frame is ready
    new_flag = 1;
}

/*
 * Run the game at 20 FPS
 */
CY_ISR(FPS_isr) {
    tick(&game_state);
    // LCD_Position(0, 0);
    // LCD_PrintString("     ");
    // LCD_Position(0, 0);
    // LCD_PrintNumber(game_state.score);
    update_render();
}

CY_ISR(BLE_Rx_isr) {
    uint8 c = BLE_UART_GetChar();
    uint8 mask = c - 0x30;
    // Reject out-of-bounds inputs
    if (mask > 31) return;
    // Fill the affected tracks for 5 frames
    for (int i = 0; i < 5; i++) {
        if (mask & (1 << i))
            indicator_countdown[i] = 5;
    }
    // Calculate scoring
    update_score(&game_state, mask);
}

CY_ISR(Audio_isr) {
    // WAV data is 8-bit unsigned PCM
    Audio_DAC_SetValue(buffer[play_buffer][play_idx++]);
    if (play_idx == buffer_len[play_buffer]) {
        play_idx = 0;
        play_buffer++;
        if (play_buffer == N_BUFFERS)
            play_buffer = 0;
        // Stop playing when we reach the end of the file
        if (play_buffer == fill_buffer && audio_done)
            Audio_isr_Stop();
    }
}

int main() {
    CyGlobalIntEnable; /* Enable global interrupts. */

    hw_init();
    game_init();
    audio_init();

    for (;;) {
        // "Latch" the new points
        if (new_flag) {
            n_points = new_n_points;
            for (int i = 0; i < n_points; i++)
                points[i] = new_points[i];
            new_flag = 0;
        }
        
        // Continuously fill the ring buffer
        if (!audio_done) {
            if (fill_buffer != play_buffer) {
                buffer_len[fill_buffer] = FS_Read(audio_file, buffer[fill_buffer], BUFFER_LEN);
                if (!buffer_len[fill_buffer]) {
                    audio_done = 1;
                    FS_FClose(audio_file);
                } else {
                    fill_buffer++;
                    if (fill_buffer == N_BUFFERS)
                        fill_buffer = 0;
                }
            }
        }

        // Render!
        draw_points();
    }
}

/* [] END OF FILE */
