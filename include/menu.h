/*
** EPITECH PROJECT, 2025
** menu
** File description:
** Header file for menu management
*/

#ifndef MENU_H_
    #define MENU_H_

    #include "raylib.h"
    #include "button.h"
    #include "types.h"

    #define WINDOW_WIDTH 1920
    #define WINDOW_HEIGHT 1080
    #define BUTTON_WIDTH 200
    #define BUTTON_HEIGHT 50

void init_window_fullscreen(void);
void handle_menu(void);
void close_window_cleanup(void);
void handle_mouse_input(button_t quit_button, button_t options_button,
    options_t *options);

#endif
