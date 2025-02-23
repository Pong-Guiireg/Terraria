/*
** EPITECH PROJECT, 2025
** options
** File description:
** Options management header
*/

#ifndef OPTIONS_H_
    #define OPTIONS_H_

    #include "raylib.h"
    #include "button.h"
    #include "types.h"

void handle_options_menu(options_t *options);
void draw_volume_controls(options_t *options);
void draw_key_bindings(options_t *options);

#endif
