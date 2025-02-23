/*
** EPITECH PROJECT, 2025
** menu
** File description:
** Menu management functions
*/
#include "../include/menu.h"
#include "../include/button.h"
#include "../include/options.h"

void init_window_fullscreen(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Terraria");
    SetTargetFPS(60);
    ToggleFullscreen();
}

void handle_menu(void)
{
    button_t play_button = create_button(400, "Jouer");
    button_t options_button = create_button(500, "Options");
    button_t quit_button = create_button(600, "Quitter");
    options_t options = {
        .sound_volume = 0.5f,
        .music_volume = 0.5f,
        .move_up = KEY_Z,
        .move_down = KEY_S,
        .move_left = KEY_Q,
        .move_right = KEY_D,
        .jump = KEY_SPACE
    };

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        draw_buttons(play_button, options_button, quit_button);
        handle_mouse_input(quit_button, options_button, &options);
        EndDrawing();
    }
}

void handle_mouse_input(button_t quit_button, button_t options_button,
    options_t *options)
{
    Vector2 mouse;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        mouse = GetMousePosition();
        if (CheckCollisionPointRec(mouse, quit_button.rect))
            CloseWindow();
        if (CheckCollisionPointRec(mouse, options_button.rect))
            handle_options_menu(options);
    }
}

void close_window_cleanup(void)
{
    CloseWindow();
}
