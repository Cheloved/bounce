#ifndef H_CIRCLE 
#define H_CIRCLE 

#include "vector.h"
#include "defines.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * Circle struct holds
 * position, velocity, acceleration,
 * radius and mass of the circle
*/
typedef struct
{
    int id;

    s_vector pos;
    s_vector vel;
    s_vector acc;

    /* float radius; */
    float radius;
} s_circle;

extern s_circle circles[AMOUNT];

/*
 * Generates random circle constrained
 * by limits in arguments
*/
s_circle randomizeCircle(int id, int xlim, int ylim,
                         float vlim, float alim,
                         float rmin, float rmax);

// Prints all circle data
void printCircle(s_circle* c);

// Updates circle position and velocity
void updateCircle(s_circle* c);

void checkWallCollision(s_circle* c);

#endif
