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

    /*
     * Continuos wall collision check
    */
    // Check if collision will appear on next frame
    // on X axis
    float next_x = c->pos.x + c->vel.x;
    if ( next_x - c->radius <= -WIDTH/2 )
    {
        // Place back on wall
        c->pos.x = -WIDTH/2 + c->radius;

        // Invert velocity
        c->vel.x = -c->vel.x;
    } else if ( next_x + c->radius >= WIDTH/2  )
    {
        c->pos.x = WIDTH/2 - c->radius;
        c->vel.x = -c->vel.x;
    } else c->pos.x += c->vel.x;

    // on Y axis
    float next_y = c->pos.y + c->vel.y;
    if ( next_y - c->radius <= -HEIGHT/2 )
    {
        c->pos.y = -HEIGHT/2 + c->radius;
        c->vel.y = -c->vel.y;
    } else if ( next_y + c->radius >= HEIGHT/2  )
    {
        c->pos.y = HEIGHT/2 - c->radius;
        c->vel.y = -c->vel.y;
    } else c->pos.y += c->vel.y;

    // Simple circles' collisions check
    for ( int i = c->id+1; i < AMOUNT; i++ )
    {
        s_circle* c2 = &circles[i];
        
        // Circles collide if
        // (x2-x1)^2 + (y2-y1)^2 <= (r1+r2)^2
        float distsqr = pow(c2->pos.x - c->pos.x, 2) + 
                        pow(c2->pos.y - c->pos.y, 2);
        if ( distsqr <= pow(c->radius + c2->radius, 2) )
        {
            printf(" [i] Collision between %d and %d\n", c->id, c2->id);
            // Save previous c velocity
            s_vector v0 = c->vel;

            // Update c velocity
            c->vel.x = (2*c2->radius*c2->vel.x + (c->radius-c2->radius)*v0.x) / (c->radius + c2->radius);
            c->vel.y = (2*c2->radius*c2->vel.y + (c->radius-c2->radius)*v0.y) / (c->radius + c2->radius);
            
            // Update c2 velocity
            c2->vel.x = (2*c->radius*v0.x + (c2->radius-c->radius)*c2->vel.x) / (c->radius + c2->radius);
            c2->vel.y = (2*c->radius*v0.y + (c2->radius-c->radius)*c2->vel.y) / (c->radius + c2->radius);
        }
    }
}
