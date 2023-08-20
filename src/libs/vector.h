#ifndef H_VECTOR
#define H_VECTOR

#include <math.h>

typedef struct
{
    float x, y;
} s_vector;

s_vector v_plus(s_vector a, s_vector b);
s_vector v_minus(s_vector a, s_vector b);
s_vector v_mul(s_vector a, float f);
float v_dot(s_vector a, s_vector b);
float v_len(s_vector a);


#endif
