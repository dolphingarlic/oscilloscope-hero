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

#include "cytypes.h"

#ifndef SPRITES_H
#define SPRITES_H

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

/*
 * Initializes the vertices to be shared between sprites
 */
void init_sprites();

/*
 * Creates a fretboard instance
 */
struct Sprite make_fretboard();

/*
 * Creates a barline instance at the specified y offset
 */
struct Sprite make_barline(int y);

/*
 * Creates an ellipse instance in the specified track and location
 */
struct Sprite make_ellipse(uint8 track, int y, uint8 filled);

/*
 * Converts a list of sprites into a polyline that the scope can render.
 */
int sprites_to_polyline(int n_sprites, struct Sprite *sprites, struct Point *points);

/*
 * Mutates a list of points from an orthographic view to a perspective view.
 *
 * Matrix coefficients calculated using OpenCV by taking the perspective transform
 * [(0, 0), (0, 255), (255, 255), (255, 0)] -> [(0, 0), (84, 255), (171, 255), (255, 0)]
 * which yields
 * [1   0.96551724  0
 *  0   2.93103448  0
 *  0   0.00757268  1]
 */
void ortho_to_perspective(int n_points, struct Point *points);

#endif

/* [] END OF FILE */
