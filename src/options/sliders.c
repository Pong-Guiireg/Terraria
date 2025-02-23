/*
** EPITECH PROJECT, 2025
** sliders
** File description:
** Slider and key binding management
*/
#include "../../include/sliders.h"
#include "../../include/menu.h"
#include "../../include/types.h"
#include <unistd.h>
#include <stdbool.h>

typedef struct key_mapping_s {
    KeyboardKey qwerty_key;
    const char *azerty_name;
    char azerty_char;
} key_mapping_t;

static const key_mapping_t KEY_MAPPINGS[] = {
    {KEY_SPACE, "ESPACE", ' '},
    {KEY_Q, "A", 'a'},
    {KEY_A, "Q", 'q'},
    {KEY_W, "Z", 'z'},
    {KEY_Z, "W", 'w'},
    {KEY_E, "E", 'e'},
    {KEY_R, "R", 'r'},
    {KEY_T, "T", 't'},
    {KEY_Y, "Y", 'y'},
    {KEY_U, "U", 'u'},
    {KEY_I, "I", 'i'},
    {KEY_O, "O", 'o'},
    {KEY_P, "P", 'p'},
    {KEY_S, "S", 's'},
    {KEY_D, "D", 'd'},
    {KEY_F, "F", 'f'},
    {KEY_G, "G", 'g'},
    {KEY_H, "H", 'h'},
    {KEY_J, "J", 'j'},
    {KEY_K, "K", 'k'},
    {KEY_L, "L", 'l'},
    {KEY_M, "M", 'm'},
    {0, NULL, 0}
};

void draw_slider(Rectangle slider, float *value, const char *text)
{
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

static const char *get_key_name(KeyboardKey key)
{
    if (key == 0)
        return "...";

    for (int i = 0; KEY_MAPPINGS[i].qwerty_key != 0; i++) {
        if (KEY_MAPPINGS[i].qwerty_key == key)
            return KEY_MAPPINGS[i].azerty_name;
    }
    return TextFormat("%c", (int)key);
}

static KeyboardKey convert_qwerty_to_azerty(int key)
{
    for (int i = 0; KEY_MAPPINGS[i].qwerty_key != 0; i++) {
        if (KEY_MAPPINGS[i].azerty_char == (char)key)
            return KEY_MAPPINGS[i].qwerty_key;
    }
    return key;
}

#define ERROR_DISPLAY_TIME 2.0f

typedef struct key_binding_state_s {
    KeyboardKey *selected_key;
    KeyboardKey previous_key;
    float error_timer;
    bool show_error;
} key_binding_state_t;

static bool is_key_already_used(KeyboardKey new_key, options_t *options,
    KeyboardKey *current_key)
{
    if (new_key == options->move_up && options->move_up != *current_key)
        return true;
    if (new_key == options->move_down && options->move_down != *current_key)
        return true;
    if (new_key == options->move_left && options->move_left != *current_key)
        return true;
    if (new_key == options->move_right && options->move_right != *current_key)
        return true;
    if (new_key == options->jump && options->jump != *current_key)
        return true;
    return false;
}

static void handle_key_selection(KeyboardKey *key, key_binding_state_t *state,
    Rectangle rect)
{
    if (!CheckCollisionPointRec(GetMousePosition(), rect) ||
        !IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        return;
    state->selected_key = key;
    state->previous_key = *key;
}

static void handle_key_input(KeyboardKey *key, key_binding_state_t *state,
    options_t *options)
{
    int new_key;

    if (state->selected_key != key)
        return;
    new_key = GetKeyPressed();
    if (new_key == 0)
        return;
    new_key = convert_qwerty_to_azerty(new_key);
    if (is_key_already_used(new_key, options, key)) {
        *key = state->previous_key;
        state->show_error = true;
        state->error_timer = ERROR_DISPLAY_TIME;
    } else {
        *key = new_key;
    }
    state->selected_key = NULL;
}

void draw_key_binding(Rectangle rect, KeyboardKey *key, const char *text,
    float label_x, options_t *options)
{
    static key_binding_state_t state = {NULL, 0, 0.0f, false};
    const char *key_text = get_key_name(*key);
    Color rect_color = LIGHTGRAY;

    handle_key_input(key, &state, options);
    handle_key_selection(key, &state, rect);

    if (state.selected_key == key) {
        rect_color = GRAY;
        key_text = "...";
    }

    DrawText(text, label_x, rect.y + 10, 20, BLACK);
    DrawRectangleRec(rect, rect_color);
    DrawText(key_text, rect.x + 10, rect.y + 10, 20, BLACK);

    if (state.show_error) {
        DrawText("Touche déjà utilisée !", WINDOW_WIDTH / 2 - 100, 150, 20, RED);
        state.error_timer -= GetFrameTime();
        if (state.error_timer <= 0) {
            state.show_error = false;
        }
    }
}
