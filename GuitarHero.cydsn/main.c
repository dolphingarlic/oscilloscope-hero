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
#include <sprite_utils.h>

// Global constants
const uint16 DAC_SETTLE_TIME_US = 3;
const float PI = 3.14159265358979323846;

// Global rendering variables
int n;
uint8 x[1<<12], y[1<<12];
uint8 new_flag;
uint8 new_x[1<<12], new_y[1<<12];

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
 * Given a list of points, draws a polygon connecting them
 * on the oscilloscope using the DAC
 */
void draw_points() {   
    for (int i = 0; i < n ; i++) {
        x_DAC_SetValue(x[i]);
        y_DAC_SetValue(y[i]);
        CyDelayUs(DAC_SETTLE_TIME_US); // Wait for DAC to settle
    }
}

/*
 * Updates the list of points to render
 */
int circle_idx = 0;
void update_points() {
    // Reset everything
    n = 0;
    // Fretboard
    make_fretboard(&n, new_x, new_y);
    // Move the circle
    circle_idx++;
    if (circle_idx == 60) circle_idx = 0;
    for (int i = 0; i <= 64; i++) {
        new_x[n] = (uint8)(32 * (cos(i * 2 * PI / 64) + cos(circle_idx * 2 * PI / 60)) + 128);
        new_y[n] = (uint8)(32 * (sin(i * 2 * PI / 64) + sin(circle_idx * 2 * PI / 60)) + 128);
        n++;
    }
    // Signal that a new frame is ready
    new_flag = 1;
}

/*
 * Run the game at 60 FPS
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
    update_points();

    for (;;) {
        if (new_flag == 1) {
            for (int i = 0; i < n; i++) {
                x[i] = new_x[i];
                y[i] = new_y[i];
            }
            new_flag = 0;
        }

        draw_points();
    }
}

/* [] END OF FILE */
