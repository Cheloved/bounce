#include "libs/circle.h"

s_circle randomizeCircle(int id, int xlim, int ylim,
                         float vlim, float alim,
                         float rmin, float rmax)
{
    s_circle c;
    c.id = id;

    c.radius = randfloat(rmin, rmax);

    // Generate new position until no
    // circles are intersected
    int intersected = 0;
    do{
        c.pos.x = randfloat(-xlim, xlim);
        c.pos.y = randfloat(-ylim, ylim);

        // Iterate over already generated
        for ( int i = 0; i < id; i++ )
        {
            s_circle* c2 = &circles[i];

            // Check distance
            float distsqr = pow(c2->pos.x - c.pos.x, 2) + 
                            pow(c2->pos.y - c.pos.y, 2);
            if ( distsqr <= pow(c.radius + c2->radius, 2) )
            {
                intersected = 1;
                break;
            }
            intersected = 0;
        }
    } while ( intersected );

    c.vel.x = randfloat(-vlim, vlim);
    c.vel.y = randfloat(-vlim, vlim);

    c.acc.x = randfloat(-alim, alim);
    c.acc.y = randfloat(-alim, alim);

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
            // Save previous c velocity
            s_vector v0 = c->vel;

            // Update c velocity
            float m1 = 2*c2->radius / (c->radius + c2->radius);
            float m2nom = v_dot( v_minus(c->vel, c2->vel), v_minus(c->pos, c2->pos) );
            float m2den = pow( v_len( v_minus(c->pos, c2->pos) ), 2 );
            s_vector m3 = v_minus(c->pos, c2->pos);
            c->vel = v_minus(c->vel, v_mul(m3, m1*m2nom/m2den));
            
            // Update c2 velocity
            m1 = 2*c->radius / (c->radius + c2->radius);
            m2nom = v_dot( v_minus(c2->vel, v0), v_minus(c2->pos, c->pos) );
            m2den = pow( v_len( v_minus(c2->pos, c->pos) ), 2 );
            m3 = v_minus(c2->pos, c->pos);
            c2->vel = v_minus(c2->vel, v_mul(m3, m1*m2nom/m2den));

            printf(" [i] Collision between %d and %d\n", c->id, c2->id);
        }
    }
}
