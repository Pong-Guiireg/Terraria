/*
** EPITECH PROJECT, 2025
** menu
** File description:
** Menu management functions
*/

#include "../include/menu.h"

static button_t create_button(float y, const char *text)
{
    button_t button;
    float x_center = (float)WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2;

    button.rect = (Rectangle){x_center, y, BUTTON_WIDTH, BUTTON_HEIGHT};
    button.text = text;
    button.color = GRAY;
    button.hover_color = DARKGRAY;
    return button;
}

void init_window_fullscreen(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "My Game");
    SetTargetFPS(60);
    ToggleFullscreen();
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
        (int)(button.rect.x + BUTTON_WIDTH / 2 - MeasureText(button.text, 20) / 2),
        (int)(button.rect.y + BUTTON_HEIGHT / 2 - 10),
        20,
        BLACK);
}

void handle_menu(void)
{
    button_t play_button = create_button(400, "Jouer");
    button_t options_button = create_button(500, "Options");
    button_t quit_button = create_button(600, "Quitter");
    options_t options = {
        .sound_volume = 0.5f,
        .music_volume = 0.5f,
        .move_left = KEY_A,
        .move_right = KEY_D,
        .jump = KEY_SPACE
    };

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        draw_button(play_button);
        draw_button(options_button);
        draw_button(quit_button);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mouse = GetMousePosition();
            if (CheckCollisionPointRec(mouse, quit_button.rect))
                break;
            if (CheckCollisionPointRec(mouse, options_button.rect))
                handle_options_menu(&options);
        }
        EndDrawing();
    }
}

void close_window_cleanup(void)
{
    CloseWindow();
}
