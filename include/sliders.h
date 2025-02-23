/*
** EPITECH PROJECT, 2025
** sliders
** File description:
** Header file for slider management
*/

#ifndef SLIDERS_H_
    #define SLIDERS_H_

    #include "raylib.h"
    #include "types.h"
    #include "menu.h"

void draw_slider(Rectangle slider, float *value, const char *text);
void draw_key_binding(Rectangle rect, KeyboardKey *key, const char *text,
    float label_x, options_t *options);

#endif
