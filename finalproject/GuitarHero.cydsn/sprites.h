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

enum SpriteType {
    FRETBOARD,
    BARLINE,
    OPEN_ELLIPSE,
    FILLED_ELLIPSE
};

struct Sprite {
    int n, x, y;
    struct Point *vertices;
};

void init_sprites();

struct Sprite make_fretboard();

struct Sprite make_barline(int y);

struct Sprite make_ellipse(uint8 track, int y, uint8 filled);

int sprites_to_polyline(int n_sprites, struct Sprite *sprites, struct Point *points);

void ortho_to_perspective(int n_points, struct Point *points);

/* [] END OF FILE */
