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
const uint16 DAC_SETTLE_TIME_US = 3;
const float PI = 3.14159265358979323846;

// Sprites
int n_sprites;
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
    n_sprites = 0;
    sprites[n_sprites++] = make_fretboard();
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
void update_points() {
    // TODO: create a moving ellipse
    
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
    update_points();
}

CY_ISR(BLE_Rx_isr) {
    uint8 c = BLE_UART_GetChar();
    if (c != '\n') LCD_PutChar(c);
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
