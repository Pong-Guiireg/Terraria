/*
** EPITECH PROJECT, 2025
** sliders
** File description:
** Slider and key binding management
*/
#include "../../include/sliders.h"

void draw_slider(Rectangle slider, float *value, const char *text)
{
    DrawText(text, slider.x, slider.y - 20, 20, BLACK);
    DrawRectangleRec(slider, LIGHTGRAY);
    DrawRectangle(slider.x, slider.y,
        (int)(slider.width * (*value)), slider.height, BLUE);
    if (CheckCollisionPointRec(GetMousePosition(), slider) &&
        IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        *value = (GetMousePosition().x - slider.x) / slider.width;
        if (*value < 0.0f) {
            *value = 0.0f;
        }
        if (*value > 1.0f) {
            *value = 1.0f;
        }
    }
}

void draw_key_binding(Rectangle rect, KeyboardKey *key, const char *text)
{
    DrawText(text, rect.x, rect.y - 20, 20, BLACK);
    DrawRectangleRec(rect, LIGHTGRAY);
    DrawText(TextFormat("%c", (int)*key), rect.x + 10, rect.y + 10, 20, BLACK);
    if (CheckCollisionPointRec(GetMousePosition(), rect) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        *key = GetKeyPressed();
    }
}
