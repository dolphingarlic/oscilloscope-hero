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

struct Point {
    uint8 x;
    uint8 y;
};

struct Sprite {
    int n;
    struct Point position;
    struct Point *vertices;
};

struct Sprite make_fretboard();

struct Sprite make_barline();

struct Sprite make_ellipse(struct Point position, uint8 width, uint8 height, uint8 filled);

int sprites_to_polyline(int n_sprites, struct Sprite *sprites, struct Point *points);

void ortho_to_perspective(int n_points, struct Point *points);

/* [] END OF FILE */
