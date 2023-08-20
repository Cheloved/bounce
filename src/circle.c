#include "libs/circle.h"

s_circle randomizeCircle(int id, int xlim, int ylim,
                         float vlim, float alim,
                         float rmin, float rmax)
{
    s_circle c;
    c.id = id;

    c.pos.x = randfloat(-xlim, xlim);
    c.pos.y = randfloat(-ylim, ylim);

    c.vel.x = randfloat(-vlim, vlim);
    c.vel.y = randfloat(-vlim, vlim);

    c.acc.x = randfloat(-alim, alim);
    c.acc.y = randfloat(-alim, alim);

    c.radius = randfloat(rmin, rmax);

    return c;
}

void printCircle(s_circle* c)
{
    printf("# === Circle %d === #\n", c->id);
    printf("Position: (%f, %f)\n", c->pos.x, c->pos.y);
    printf("Velocity: (%f, %f)\n", c->vel.x, c->vel.y);
    printf("Acceleration: (%f, %f)\n", c->acc.x, c->acc.y);
    printf("Radius: %f\n", c->radius);
    printf("# ================= #\n\n");
}

void updateCircle(s_circle* c)
{
    /* c->vel.x += c->acc.x; */
    /* c->vel.y += c->acc.y; */

    checkWallCollision(c);

    c->pos.x += c->vel.x;
    c->pos.y += c->vel.y;
}

void checkWallCollision(s_circle* c)
{
    // Left
    if ( c->pos.x - c->radius <= -WIDTH/2 )
        c->vel.x = -c->vel.x;

    // Right
    if ( c->pos.x + c->radius >= WIDTH/2 )
        c->vel.x = -c->vel.x;
    
    // Up 
    if ( c->pos.y + c->radius >= HEIGHT/2 )
        c->vel.y = -c->vel.y;
    
    // Down
    if ( c->pos.y - c->radius <= -HEIGHT/2 )
        c->vel.y = -c->vel.y;
}
