/*
** EPITECH PROJECT, 2025
** options
** File description:
** Options menu management
*/
#include "../../include/options.h"
#include "../../include/sliders.h"
#include "../../include/button.h"
#include "../../include/menu.h"
#include <stdbool.h>

void draw_volume_controls(options_t *options)
{
    Rectangle sound_slider = {WINDOW_WIDTH / 2 - 100, 300, 200, 20};
    Rectangle music_slider = {WINDOW_WIDTH / 2 - 100, 400, 200, 20};

    draw_slider(sound_slider, &options->sound_volume, "Son");
    draw_slider(music_slider, &options->music_volume, "Musique");
}

void draw_key_bindings(options_t *options)
{
    Rectangle left_rect = {WINDOW_WIDTH / 2 - 100, 500, 200, 40};
    Rectangle right_rect = {WINDOW_WIDTH / 2 - 100, 550, 200, 40};
    Rectangle jump_rect = {WINDOW_WIDTH / 2 - 100, 600, 200, 40};

    draw_key_binding(left_rect, &options->move_left, "Gauche");
    draw_key_binding(right_rect, &options->move_right, "Droite");
    draw_key_binding(jump_rect, &options->jump, "Saut");
}

void handle_back_button(options_t *options, button_t back_button)
{
    Vector2 mouse = GetMousePosition();
    bool is_pressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    bool is_colliding = CheckCollisionPointRec(mouse, back_button.rect);

    if (is_pressed && is_colliding) {
        return;
    }
}

void handle_options_menu(options_t *options)
{
    button_t back_button = create_button(700, "Retour");
    bool exit_menu = false;

    while (!WindowShouldClose() && !exit_menu) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("OPTIONS", WINDOW_WIDTH / 2 - 100, 100, 40, BLACK);
        draw_volume_controls(options);
        draw_key_bindings(options);
        draw_button(back_button);
        handle_back_button(options, back_button);
        EndDrawing();
    }
}
