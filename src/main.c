#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#include <GL/glut.h>

#include "libs/defines.h"
#include "libs/circle.h"
#include "libs/vector.h"

s_circle circles[AMOUNT];
unsigned int frame_count = 0;

void initCircles(void)
{
    for ( int i = 0; i < AMOUNT; i++ )
    {
        circles[i] = randomizeCircle(i, WIDTH/2 - RMAX, HEIGHT/2 - RMAX,
                                     VMAX, AMAX,
                                     RMIN, RMAX);
        printCircle(&circles[i]);
    }
}

void drawCircle(s_circle* c, float delta)
{
    float x, y;
      
    // Set draw color
    glColor3f((RMAX-c->radius+RMIN)/(RMAX-RMIN),
              0.0,
              (c->radius-RMIN)/(RMAX-RMIN));
      
    glBegin(GL_POINTS);
    for ( float i = 0; i < (2 * pi); i += delta)
    {
        x = c->radius * cos(i) + c->pos.x;
        y = c->radius * sin(i) + c->pos.y;
          
        glVertex2f(x, y);
    }
    glEnd();
}

void display (void) 
{
    // Clear everything
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw circles
    for ( int i = 0; i < AMOUNT; i++ )
        drawCircle(&circles[i], ANGLE_DELTA);

    // Update
    glutSwapBuffers();

    // Recalculate data
    for ( int i = 0; i < AMOUNT; i++ )
        updateCircle(&circles[i]);

    frame_count++;
}

void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(1000/MAX_FPS, timer, 0);
}

int main(int argc, char** argv)
{
    // Initialize OpenGL 
    glutInit(&argc, argv);
    /* glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); */
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);

    // Set window size and position
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0, 0);

    // Set window name
    glutCreateWindow("Bouncy");

    // Set background color
    glClearColor(0.1, 0.1, 0.1, 1.0);
      
    // Set size of a drawing point
    glPointSize(1.0);

    // Prepare matrix
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
      
    // Center the coordinates
    gluOrtho2D(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2);

    // Set random seed
    time_t t;
    srand((unsigned) time(&t));

    initCircles();

    glutDisplayFunc(display);
    timer(0);

    glutMainLoop();

    return 0;
}
