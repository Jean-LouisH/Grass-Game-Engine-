#include "Grass.h"

////////////////////////////////////////
//GLUT Callback function implementations
///////////////////////////////////////
void timer(int milliseconds)
{
    glutTimerFunc(milliseconds, timer, milliseconds);
    glutPostRedisplay();
}

void reshape(int width, int height)
{
    //Courtesy of Swiftless OpenGL tutorials.
   glViewport (0, 0, (GLsizei) width, (GLsizei) height);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(60.0, (GLfloat) width/(GLfloat) height, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (0.0, 0.0, 1.74, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyPressed(unsigned char key, int x, int y)
{
    keyStates[key] = true; //registers a button press in the input buffer.
}

void keyUp(unsigned char key, int x, int y)
{
    if((keyStates['p'] || keyStates['P']) && (!gamePause))
        gamePause = true;

    else if((keyStates['p'] || keyStates['P'] ) && (gamePause))
        gamePause = false;

    keyStates[key] = false;
    polygon[0].properties.xVelocity = 0; //stops player movement immediately after releasing.
}

