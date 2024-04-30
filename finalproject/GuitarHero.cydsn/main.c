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
#include <project.h>
#include <math.h>
#include <sprites.h>

// Global constants
const uint16 DAC_SETTLE_TIME_US = 0;

// Sprites
int n_sprites;
uint8 indicator_countdown[5];
struct Sprite sprites[1<<5];

// Global rendering variables
int n_points;
struct Point points[1<<10];
uint8 new_flag;
int new_n_points;
struct Point new_points[1<<10];

// Declare custom ISRs
CY_ISR_PROTO(FPS_isr);
CY_ISR_PROTO(BLE_Rx_isr);

/*
 * Initialize the system hardware
 */
void hw_init() {
    x_DAC_Start();
    y_DAC_Start();
    
    LCD_Start();
    LCD_ClearDisplay();
    LCD_Position(0, 0);
    
    BLE_UART_Init();
    BLE_UART_Start();

    FPS_isr_StartEx(FPS_isr);
    BLE_Rx_isr_StartEx(BLE_Rx_isr);
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
}

/*
 * Given a list of points, draws a polygon connecting them
 * on the oscilloscope using the DAC
 */
void draw_points() {   
    for (int i = 0; i < n_points; i++) {
        x_DAC_SetValue(points[i].x);
        y_DAC_SetValue(points[i].y);
        CyDelayUs(DAC_SETTLE_TIME_US); // Wait for DAC to settle
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
    // TODO: Calculate scoring
    LCD_PutChar(c);
}

int main() {
    CyGlobalIntEnable; /* Enable global interrupts. */

    hw_init();
    game_init();

    for (;;) {
        // "Latch" the new points
        if (new_flag == 1) {
            n_points = new_n_points;
            for (int i = 0; i < n_points; i++)
                points[i] = new_points[i];
            new_flag = 0;
        }

        draw_points();
    }
}

/* [] END OF FILE */
