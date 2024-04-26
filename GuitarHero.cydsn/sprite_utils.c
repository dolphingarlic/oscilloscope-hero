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
#include <stdlib.h>

/*
 * Creates a set of points to denote the boundaries of the fretboard
 */
struct Sprite* make_fretboard() {
    const int resolution = 32;
    int n = 0;
    struct Point vertices[4 * resolution + 1];

    // Bottom edge
    for (int i = 0; i < resolution; i++) {
        vertices[n++] = (struct Point) {
            .x = UINT8_MAX * i / resolution,
            .y = 0
        };
    }
    // Right edge
    for (int i = 0; i < resolution; i++) {
        vertices[n++] = (struct Point) {
            .x = UINT8_MAX,
            .y = UINT8_MAX * i / resolution
        };
    }
    // Top edge
    for (int i = 0; i < resolution; i++) {
        vertices[n++] = (struct Point) {
            .x = UINT8_MAX - UINT8_MAX * i / resolution,
            .y = UINT8_MAX
        };
    }
    // Left edge
    for (int i = 0; i < resolution; i++) {
        vertices[n++] = (struct Point) {
            .x = 0,
            .y = UINT8_MAX - UINT8_MAX * i / resolution
        };
    }
    // Complete the polygon
    vertices[n++] = (struct Point) { .x = 0, .y = 0 };

    struct Sprite *res = (struct Sprite*) malloc(sizeof(struct Sprite));
    res->position = (struct Point) { .x = 0, .y = 0 };
    res->n = n;
    res->vertices = vertices;
    return res;
}

/*
 * Converts a list of sprites into a polyline that the scope can render.
 */
void sprites_to_polyline(int n_sprites, struct Sprite **sprites, int *n_points, struct Point *points) {
    // For now, naively convert to points
    for (int i = 0; i < n_sprites; i++) {
        for (int j = 0; j < sprites[i]->n; j++) {
            // TODO: incorporate position
            points[(*n_points)++] = sprites[i]->vertices[j];
        }
    }
}

/*
 * Converts a list of points from an orthographic view to a perspective view.
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
