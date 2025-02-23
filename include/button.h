/*
** EPITECH PROJECT, 2025
** button
** File description:
** Button management header
*/

#ifndef BUTTON_H_
    #define BUTTON_H_

    #include "raylib.h"

typedef struct button_s {
    Rectangle rect;
    const char *text;
    Color color;
    Color hover_color;
} button_t;

button_t create_button(float y, const char *text);
void draw_button(button_t button);
void draw_buttons(button_t play_button, button_t options_button,
    button_t quit_button);

#endif
