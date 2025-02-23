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
    int start_y = 200;
    int spacing = 50;
    Rectangle sound_slider = {WINDOW_WIDTH / 2 - 100, start_y, 200, 20};
    Rectangle music_slider = {WINDOW_WIDTH / 2 - 100, start_y + spacing,
        200, 20};

    DrawText("Audio", WINDOW_WIDTH / 2 - 250, start_y - spacing, 30, BLACK);
    DrawText("Son", WINDOW_WIDTH / 2 - 250, start_y, 20, BLACK);
    DrawText("Musique", WINDOW_WIDTH / 2 - 250, start_y + spacing, 20, BLACK);
    draw_slider(sound_slider, &options->sound_volume, "");
    draw_slider(music_slider, &options->music_volume, "");
}

void draw_key_bindings(options_t *options)
{
    int start_y = 400;
    int spacing = 50;
    float label_x = WINDOW_WIDTH / 2 - 250;
    float binding_x = WINDOW_WIDTH / 2 + 50;

    DrawText("Contrôles", WINDOW_WIDTH / 2 - 250, start_y - spacing,
        30, BLACK);
    draw_key_binding((Rectangle){binding_x, start_y, 100, 40},
        &options->move_up, "Haut", label_x);
    draw_key_binding((Rectangle){binding_x, start_y + spacing, 100, 40},
        &options->move_down, "Bas", label_x);
    draw_key_binding((Rectangle){binding_x, start_y + spacing * 2, 100, 40},
        &options->move_left, "Gauche", label_x);
    draw_key_binding((Rectangle){binding_x, start_y + spacing * 3, 100, 40},
        &options->move_right, "Droite", label_x);
    draw_key_binding((Rectangle){binding_x, start_y + spacing * 4, 100, 40},
        &options->jump, "Saut", label_x);
}

static void handle_back_button(button_t back_button, bool *exit_menu)
{
    Vector2 mouse = GetMousePosition();
    bool is_pressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    bool is_colliding = CheckCollisionPointRec(mouse, back_button.rect);

    if (is_pressed && is_colliding) {
        *exit_menu = true;
    }
}

void handle_options_menu(options_t *options)
{
    button_t back_button = create_button(800, "Retour");
    bool exit_menu = false;

    while (!WindowShouldClose() && !exit_menu) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("OPTIONS", WINDOW_WIDTH / 2 - 100, 100, 40, BLACK);
        draw_volume_controls(options);
        draw_key_bindings(options);
        draw_button(back_button);
        handle_back_button(back_button, &exit_menu);
        EndDrawing();
    }
}
