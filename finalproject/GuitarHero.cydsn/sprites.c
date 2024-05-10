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
        sprite_n[BARLINE] = n;
    }
    
    // Ellipses
    {
        const int resolution = 8;
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
        sprite_n[OPEN_ELLIPSE] = n;
        sprite_n[FILLED_ELLIPSE] = n;
    }
}

struct Sprite make_fretboard() {
    return (struct Sprite) {
        .n = sprite_n[FRETBOARD], .x = 0, .y = 0,
        .vertices = sprite_vertices[FRETBOARD]
    };
}

struct Sprite make_barline(int y) {
    return (struct Sprite) {
        .n = sprite_n[BARLINE], .x = 0, .y = y,
        .vertices = sprite_vertices[BARLINE]
    };
}

struct Sprite make_ellipse(uint8 track, int y, uint8 filled) {
    enum SpriteType tp = (filled ? FILLED_ELLIPSE : OPEN_ELLIPSE);
    return (struct Sprite) {
        .n = sprite_n[tp], .x = 48 * track + 10, .y = y,
        .vertices = sprite_vertices[tp],
    };
}

/*
 * Recursively constructs a chain of ellipses to minimize extraneous distance
 *
 * Returns the number of new points added to the render list
 */
static int ellipse_chain(int idx, int offset, int n_sprites, struct Sprite *sprites, struct Point *points) {
    int n_points = 0;
    // Decide where (and whether) to approach the next ellipse
    int next_offset_src = -1, next_offset_dest = -1;
    if (idx != n_sprites - 1) {
        if (sprites[idx].x == sprites[idx + 1].x) {
            next_offset_src = 4;
            next_offset_dest = 12;
        } else if (sprites[idx].x < sprites[idx + 1].x) {
            next_offset_src = 8;
            next_offset_dest = 0;
        } else {
            next_offset_src = 0;
            next_offset_dest = 8;
        }
    }
    // Iterate through the vertices and pause as necessary
    for (int i = 0; i <= sprites[idx].n; i++) {
        int v = i + offset;
        if (v >= sprites[idx].n) v -= sprites[idx].n;
        int x = sprites[idx].vertices[v].x + sprites[idx].x;
        int y = sprites[idx].vertices[v].y + sprites[idx].y;
        // Clip if overflow (i.e. out of bounds)
        struct Point p = {
            .x = (uint8)(x < 0 ? 0 : x > UINT8_MAX ? UINT8_MAX : x),
            .y = (uint8)(y < 0 ? 0 : y > UINT8_MAX ? UINT8_MAX : y)
        };
        points[n_points++] = p;
        // Process the next ellipse when it's time
        if (v == next_offset_src) {
            n_points += ellipse_chain(idx + 1, next_offset_dest, n_sprites, sprites, points + n_points);
            points[n_points++] = p;
            next_offset_src = -1; // Set this so we only recurse once
        }
    }
    return n_points;
}

int sprites_to_polyline(int n_sprites, struct Sprite *sprites, struct Point *points) {
    // Render ellipses and stuff first
    int n_points = ellipse_chain(1, 0, n_sprites, sprites, points);
    // Then render the fretboard
    for (int i = 0; i < sprites[0].n; i++)
        points[n_points++] = sprites[0].vertices[i];
    return n_points;
}

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
