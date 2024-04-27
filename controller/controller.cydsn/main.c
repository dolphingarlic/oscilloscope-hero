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

// Declare custom ISRs
CY_ISR_PROTO(Strum_isr);

/*
 * Initialize the system hardware
 */
void hw_init() {
    BLE_UART_Init();
    BLE_UART_Start();

    Strum_isr_StartEx(Strum_isr);
}

CY_ISR(Strum_isr) {
    uint8 chr = 0x30 + Btn_1_Read() + 2 * Btn_2_Read() + 4 * Btn_3_Read()
                     + 8 * Btn_4_Read() + 16 * Btn_5_Read();
    BLE_UART_PutChar(chr);
}

int main() {
    CyGlobalIntEnable; /* Enable global interrupts. */

    hw_init();

    for(;;) {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
