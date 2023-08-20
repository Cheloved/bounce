#include "libs/vector.h"

s_vector v_plus(s_vector a, s_vector b)
{
    s_vector c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    return c;
}

s_vector v_minus(s_vector a, s_vector b)
{
    s_vector c;
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    return c;
}

s_vector v_mul(s_vector a, float f)
{
    s_vector c;
    c.x = a.x * f;
    c.y = a.y * f;
    return c;
}

float v_dot(s_vector a, s_vector b)
{
    return a.x * b.x + a.y * b.y;
}

float v_len(s_vector a)
{
    return sqrt( pow(a.x, 2) + pow(a.y, 2) );
}
