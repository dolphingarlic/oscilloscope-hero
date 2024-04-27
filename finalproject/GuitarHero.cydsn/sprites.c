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

static struct Point sprite_vertices[1<<10];

/*
 * Creates the boundaries of the fretboard
 */
struct Sprite make_fretboard(int offset) {
    const int resolution = 16;
    int n = 0;

    // Bottom edge
    for (int i = 0; i < resolution; i++) {
        sprite_vertices[offset + n++] = (struct Point) {
            .x = UINT8_MAX * i / resolution,
            .y = 0
        };
    }
    // Right edge
    for (int i = 0; i < resolution; i++) {
        sprite_vertices[offset + n++] = (struct Point) {
            .x = UINT8_MAX,
            .y = UINT8_MAX * i / resolution
        };
    }
    // Top edge
    for (int i = 0; i < resolution; i++) {
        sprite_vertices[offset + n++] = (struct Point) {
            .x = UINT8_MAX - UINT8_MAX * i / resolution,
            .y = UINT8_MAX
        };
    }
    // Left edge
    for (int i = 0; i < resolution; i++) {
        sprite_vertices[offset + n++] = (struct Point) {
            .x = 0,
            .y = UINT8_MAX - UINT8_MAX * i / resolution
        };
    }
    // Complete the polygon
    sprite_vertices[offset + n++] = (struct Point) { .x = 0, .y = 0 };

    return (struct Sprite) {
        .n = n, .x = 0, .y = 0,
        .vertices = sprite_vertices + offset
    };
}

/*
 * Creates a barline at the specified y offset
 */
struct Sprite make_barline(int offset, int y) {
    const int resolution = 8;
    int n = 0;
    
    for (int i = 0; i < resolution; i++) {
        sprite_vertices[offset + n++] = (struct Point) {
            .x = UINT8_MAX * i / resolution,
            .y = 0
        };
    }
    for (int i = 0; i < resolution; i++) {
        sprite_vertices[offset + n++] = (struct Point) {
            .x = UINT8_MAX - UINT8_MAX * i / resolution,
            .y = 0
        };
    }
    sprite_vertices[offset + n++] = (struct Point) { .x = 0, .y = 0 };
    
    return (struct Sprite) {
        .n = n, .x = 0, .y = y,
        .vertices = sprite_vertices + offset
    };
}

/*
 * Creates an ellipse in the specified track and location
 */
struct Sprite make_ellipse(int offset, uint8 track, int y, uint8 filled) {
    const int resolution = 16;
    const float width = 22.5, height = 7.5;
    int n = 0;

    // Top half
    for (int i = 0; i < resolution; i++) {
        sprite_vertices[offset + n++] = (struct Point) {
            .x = (uint8)(width * (cos(i * PI / resolution) + 1)),
            .y = (uint8)(height * (sin(i * PI / resolution) + 1))
        };
    }
    // Bottom half
    for (int i = 0; i < resolution; i++) {
        sprite_vertices[offset + n++] = (struct Point) {
            .x = (uint8)(width * (cos(-i * PI / resolution) + 1)),
            .y = (uint8)(height * (-sin(i * PI / resolution) + 1))
        };
    }
    // Complete the polygon
    sprite_vertices[offset + n++] = (struct Point) {
        .x = (uint8)(2 * width),
        .y = (uint8)(height)
    };
    
    if (filled == 1) {
        // TODO: interleave the top and bottom halves
    }
    
    return (struct Sprite) {
        .n = n, .x = 50 * track + 5, .y = y,
        .vertices = sprite_vertices + offset,
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
 * [(0, 0), (0, 255), (255, 255), (255, 0)] -> [(0, 0), (100, 255), (155, 255), (255, 0)]
 * which yields
 * [1   1.81818182  0
 *  0   4.63636364  0
 *  0   0.01426025  1]
 */
void ortho_to_perspective(int n_points, struct Point *points) {
    for (int i = 0; i < n_points; i++) {
        float scaled_x = points[i].x + 1.81818182 * points[i].y;
        float scaled_y = 4.63636364 * points[i].y;
        float scaling = 1 + 0.01426025 * points[i].y;
        points[i].x = (uint8)(scaled_x / scaling);
        points[i].y = (uint8)(scaled_y / scaling);
    }
}

/* [] END OF FILE */
