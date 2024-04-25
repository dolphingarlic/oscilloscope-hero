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

#include <sprite_utils.h>

void make_fretboard(int *n, uint8 *x, uint8 *y) {
    const int resolution = 32;
    const int slant = 100;
    // Bottom edge
    for (int i = 0; i < resolution; i++) {
        *(x + *n) = UINT8_MAX * i / resolution;
        *(y + *n) = 0;
        (*n)++;
    }
    // Right edge
    for (int i = 0; i < resolution; i++) {
        *(x + *n) = UINT8_MAX - slant * i / resolution;
        *(y + *n) = UINT8_MAX * i / resolution;
        (*n)++;
    }
    // Top edge
    for (int i = 0; i < resolution; i++) {
        *(x + *n) = UINT8_MAX - slant - (UINT8_MAX - 2 * slant) * i / resolution;
        *(y + *n) = UINT8_MAX;
        (*n)++;
    }
    // Left edge
    for (int i = 0; i < resolution; i++) {
        *(x + *n) = slant - slant * i / resolution;
        *(y + *n) = UINT8_MAX - UINT8_MAX * i / resolution;
        (*n)++;
    }
    // Complete the polygon
    *(x + *n) = 0;
    *(y + *n) = 0;
    (*n)++;
}

/* [] END OF FILE */
