/*
** EPITECH PROJECT, 2025
** menu
** File description:
** Header file for menu management
*/

#ifndef MENU_H_
    #define MENU_H_

    #include "raylib.h"

    #define WINDOW_WIDTH 1920
    #define WINDOW_HEIGHT 1080
    #define BUTTON_WIDTH 200
    #define BUTTON_HEIGHT 50

typedef struct button_s {
    Rectangle rect;
    const char *text;
    Color color;
    Color hover_color;
} button_t;

typedef struct options_s {
    float sound_volume;
    float music_volume;
    KeyboardKey move_left;
    KeyboardKey move_right;
    KeyboardKey jump;
} options_t;

void init_window_fullscreen(void);
void handle_menu(void);
void draw_button(button_t button);
void close_window_cleanup(void);
void handle_options_menu(options_t *options);
void draw_slider(Rectangle slider, float *value, const char *text);
void draw_key_binding(Rectangle rect, KeyboardKey *key, const char *text);

#endif
