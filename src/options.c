/*
** EPITECH PROJECT, 2025
** options
** File description:
** Options menu management
*/

#include "../include/menu.h"

static void draw_volume_controls(options_t *options)
{
    Rectangle sound_slider = {WINDOW_WIDTH / 2 - 100, 300, 200, 20};
    Rectangle music_slider = {WINDOW_WIDTH / 2 - 100, 400, 200, 20};

    draw_slider(sound_slider, &options->sound_volume, "Son");
    draw_slider(music_slider, &options->music_volume, "Musique");
}

static void draw_key_bindings(options_t *options)
{
    Rectangle left_rect = {WINDOW_WIDTH / 2 - 100, 500, 200, 40};
    Rectangle right_rect = {WINDOW_WIDTH / 2 - 100, 550, 200, 40};
    Rectangle jump_rect = {WINDOW_WIDTH / 2 - 100, 600, 200, 40};

    draw_key_binding(left_rect, &options->move_left, "Gauche");
    draw_key_binding(right_rect, &options->move_right, "Droite");
    draw_key_binding(jump_rect, &options->jump, "Saut");
}

void draw_slider(Rectangle slider, float *value, const char *text)
{
    DrawText(text, slider.x, slider.y - 20, 20, BLACK);
    DrawRectangleRec(slider, LIGHTGRAY);
    DrawRectangle(slider.x, slider.y,
        (int)(slider.width * (*value)), slider.height, BLUE);

    if (CheckCollisionPointRec(GetMousePosition(), slider) &&
        IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        *value = (GetMousePosition().x - slider.x) / slider.width;
        if (*value < 0.0f) *value = 0.0f;
        if (*value > 1.0f) *value = 1.0f;
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

void handle_options_menu(options_t *options)
{
    button_t back_button = create_button(700, "Retour");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("OPTIONS", WINDOW_WIDTH / 2 - 100, 100, 40, BLACK);
        draw_volume_controls(options);
        draw_key_bindings(options);
        draw_button(back_button);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mouse = GetMousePosition();
            if (CheckCollisionPointRec(mouse, back_button.rect))
                break;
        }
        EndDrawing();
    }
}
