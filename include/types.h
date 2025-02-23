/*
** EPITECH PROJECT, 2025
** types
** File description:
** Common type definitions
*/

#ifndef TYPES_H_
    #define TYPES_H_

    #include "raylib.h"

typedef struct options_s {
    float sound_volume;
    float music_volume;
    KeyboardKey move_left;
    KeyboardKey move_right;
    KeyboardKey jump;
} options_t;

#endif
