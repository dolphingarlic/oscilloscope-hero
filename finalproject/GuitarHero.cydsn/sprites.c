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

#include <sprites.h>
#include <math.h>

static const float PI = 3.14159265358979323846;

static struct Point sprite_vertices[4][128];
static int sprite_n[4];

/*
 * Initializes the vertices to be shared between sprites
 */
void init_sprites() {
    // Fretboard
    {
        const int resolution = 16;
        int n = 0;
        // Bottom edge
        for (int i = 0; i < resolution; i++) {
            sprite_vertices[FRETBOARD][n++] = (struct Point) {
                .x = UINT8_MAX * i / resolution,
                .y = 0
            };
        }
        // Right edge
        for (int i = 0; i < resolution; i++) {
            sprite_vertices[FRETBOARD][n++] = (struct Point) {
                .x = UINT8_MAX,
                .y = UINT8_MAX * i * i / resolution / resolution
            };
        }
        // Top edge
        for (int i = 0; i < resolution; i += 2) {
            sprite_vertices[FRETBOARD][n++] = (struct Point) {
                .x = UINT8_MAX - UINT8_MAX * i / resolution,
                .y = UINT8_MAX
            };
        }
        // Left edge
        for (int i = 0; i < resolution; i++) {
            sprite_vertices[FRETBOARD][n++] = (struct Point) {
                .x = 0,
                .y = UINT8_MAX - UINT8_MAX * sqrt(i) / sqrt(resolution)
            };
        }
        // Complete the polygon
        sprite_vertices[FRETBOARD][n++] = (struct Point) { .x = 0, .y = 0 };
        sprite_n[FRETBOARD] = n;
    }
    
    // Barline
    {
        const int resolution = 8;
        int n = 0;
        for (int i = 0; i < resolution; i++) {
            sprite_vertices[BARLINE][n++] = (struct Point) {
                .x = UINT8_MAX * i / resolution,
                .y = 0
            };
        }
        for (int i = 0; i < resolution; i++) {
            sprite_vertices[BARLINE][n++] = (struct Point) {
                .x = UINT8_MAX - UINT8_MAX * i / resolution,
                .y = 0
            };
        }
        sprite_vertices[BARLINE][n++] = (struct Point) { .x = 0, .y = 0 };        
        sprite_n[BARLINE] = n;
    }
    
    // Ellipses
    {
        const int resolution = 10;
        const int width = 20, height = 5;
        int n = 0;
        
        // Top half
        for (int i = 0; i < resolution; i++) {
            sprite_vertices[OPEN_ELLIPSE][n] = (struct Point) {
                .x = (uint8)(width * (-cos(i * PI / resolution) + 1)),
                .y = (uint8)(height * (sin(i * PI / resolution) + 1))
            };
            sprite_vertices[FILLED_ELLIPSE][n++] = (struct Point) {
                .x = (uint8)(width * (-cos(i * PI / resolution) + 1)),
                .y = (uint8)(height * (sin(i * PI / resolution) * (i & 1 ? -1 : 1) + 1))
            };
        }
        // Bottom half
        for (int i = 0; i < resolution; i++) {
            sprite_vertices[OPEN_ELLIPSE][n] = (struct Point) {
                .x = (uint8)(width * (cos(i * PI / resolution) + 1)),
                .y = (uint8)(height * (-sin(i * PI / resolution) + 1))
            };
            sprite_vertices[FILLED_ELLIPSE][n++] = (struct Point) {
                .x = (uint8)(width * (cos(i * PI / resolution) + 1)),
                .y = (uint8)(height * (-sin(i * PI / resolution) * (i & 1 ? -1 : 1) + 1))
            };
        }
        // Complete the polygon
        sprite_vertices[OPEN_ELLIPSE][n] = (struct Point) {
            .x = 0, .y = (uint8)(height)
        };
        sprite_vertices[FILLED_ELLIPSE][n++] = (struct Point) {
            .x = 0, .y = (uint8)(height)
        };
        sprite_n[OPEN_ELLIPSE] = n;
        sprite_n[FILLED_ELLIPSE] = n;
    }
}

/*
 * Creates a fretboard instance
 */
struct Sprite make_fretboard() {
    return (struct Sprite) {
        .n = sprite_n[FRETBOARD], .x = 0, .y = 0,
        .vertices = sprite_vertices[FRETBOARD]
    };
}

/*
 * Creates a barline instance at the specified y offset
 */
struct Sprite make_barline(int y) {
    return (struct Sprite) {
        .n = sprite_n[BARLINE], .x = 0, .y = y,
        .vertices = sprite_vertices[BARLINE]
    };
}

/*
 * Creates an ellipse instance in the specified track and location
 */
struct Sprite make_ellipse(uint8 track, int y, uint8 filled) {
    enum SpriteType tp = (filled ? FILLED_ELLIPSE : OPEN_ELLIPSE);
    return (struct Sprite) {
        .n = sprite_n[tp], .x = 48 * track + 10, .y = y,
        .vertices = sprite_vertices[tp],
    };
}

/*
 * Converts a list of sprites into a polyline that the scope can render.
 */
int sprites_to_polyline(int n_sprites, struct Sprite *sprites, struct Point *points) {
    // For now, naively convert to points
    int n_points = 0;
    for (int i = 0; i < n_sprites; i++) {
        // TODO: precompute whether to even show the sprite
        for (int j = 0; j < sprites[i].n; j++) {
            int x = sprites[i].vertices[j].x + sprites[i].x;
            int y = sprites[i].vertices[j].y + sprites[i].y;
            // Clip if overflow (i.e. out of bounds)
            points[n_points++] = (struct Point) {
                .x = (uint8)(x < 0 ? 0 : x > UINT8_MAX ? UINT8_MAX : x),
                .y = (uint8)(y < 0 ? 0 : y > UINT8_MAX ? UINT8_MAX : y)
            };
        }
    }
    return n_points;
}

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
void ortho_to_perspective(int n_points, struct Point *points) {
    for (int i = 0; i < n_points; i++) {
        float scaled_x = points[i].x + 0.96551724 * points[i].y;
        float scaled_y = 2.93103448 * points[i].y;
        float scaling = 1 + 0.00757268 * points[i].y;
        points[i].x = (uint8)(scaled_x / scaling);
        points[i].y = (uint8)(scaled_y / scaling);
    }
}

/* [] END OF FILE */
