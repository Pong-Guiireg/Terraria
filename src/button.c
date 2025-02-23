/*
** EPITECH PROJECT, 2025
** button
** File description:
** Button management functions
*/

#include "../include/button.h"
#include "../include/menu.h"

button_t create_button(float y, const char *text)
{
    button_t button;
    float x_center = (float)WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2;

    button.rect = (Rectangle){x_center, y, BUTTON_WIDTH, BUTTON_HEIGHT};
    button.text = text;
    button.color = GRAY;
    button.hover_color = DARKGRAY;
    return button;
}

void draw_button(button_t button)
{
    Vector2 mouse = GetMousePosition();
    Color current_color = button.color;

    if (CheckCollisionPointRec(mouse, button.rect)) {
        current_color = button.hover_color;
    }
    DrawRectangleRec(button.rect, current_color);
    DrawText(button.text,
        (int)(button.rect.x + BUTTON_WIDTH / 2 -
        MeasureText(button.text, 20) / 2),
        (int)(button.rect.y + BUTTON_HEIGHT / 2 - 10),
        20,
        BLACK);
}

void draw_buttons(button_t play_button, button_t options_button,
    button_t quit_button)
{
    draw_button(play_button);
    draw_button(options_button);
    draw_button(quit_button);
}
