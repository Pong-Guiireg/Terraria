#include "../include/math_utils.h"

/**
 * Constrain a value between minimum and maximum bounds
 * Returns min if value < min, max if value > max, or value otherwise
 */
float clamp(float value, float min, float max)
{
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}

/**
 * Add two vectors together
 * Returns a new vector with the sum of the components
 */
Vector2 vector2Add(Vector2 v1, Vector2 v2)
{
    return (Vector2){ v1.x + v2.x, v1.y + v2.y };
}

/**
 * Scale a vector by a scalar value
 * Returns a new vector with all components multiplied by the scale
 */
Vector2 vector2Scale(Vector2 v, float scale)
{
    return (Vector2){ v.x * scale, v.y * scale };
}

/**
 * Calculate the length (magnitude) of a vector
 * Uses the Pythagorean theorem to find the vector's length
 */
float vector2Length(Vector2 v)
{
    return sqrtf(v.x * v.x + v.y * v.y);
}
