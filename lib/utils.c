#include "../include/utils.h"

float clamp(float value, float min, float max)
{
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}

Vector2 vector2Add(Vector2 v1, Vector2 v2)
{
    return (Vector2){ v1.x + v2.x, v1.y + v2.y };
}

Vector2 vector2Scale(Vector2 v, float scale)
{
    return (Vector2){ v.x * scale, v.y * scale };
}

float vector2Length(Vector2 v)
{
    return sqrtf(v.x * v.x + v.y * v.y);
}
