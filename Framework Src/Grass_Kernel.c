/**

File:           Grass_Kernel.c
Description:    A superannuated 2D platformer game framework
                developed in C and legacy OpenGL. For Academic Purposes.

Author:         Jean-Louis Haywood (Haywood.JeanLouis@gmail.com)
Created:        01/09/2016
Updated:        28/09/2016
Version:        1.0

To do;
1. Grass_Compute:   Add day/night cycle effect using the colour values.
2. Grass_Editor:    Allow the editor to manually change the day/night cycle effect.
3. Grass_Compute:   Add Rigid Body calculations.

*/

#include "Grass.h"

//Loop iterations
int i;
int j;
int k;

int frameCount = 0;
double timeCount;
double smallerMapDimension;
char headsUpDisplay[8][32];
char keyStates[256];

RadialPolygon polygon[MAX_POLYGONS] = {0};
Box box[MAX_BOXES]                  = {0};
Camera camera2D;


int main(int argc, char **argv)
{
    runGLUT(argc, argv);
    return 0;
}

void runGLUT(int argc, char **argv)
{
    //GLUT initialisation
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(screenWidth, screenHeight);
    glutCreateWindow(gameTitle);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - screenWidth) / 2,
                           (glutGet(GLUT_SCREEN_HEIGHT) - screenHeight) / 2);

    //Run GLUT callback registration
    glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyUp);
    glutDisplayFunc(runGrassKernel);
    glutReshapeFunc(reshape);
    glutTimerFunc(FRAME_DELAY_MILLISECS, timer, FRAME_DELAY_MILLISECS);
    glutMainLoop();
}

void runGrassKernel()
{
    compute_findSmallerMapDimension();
    compute_incrementTime();
    frameCount++;

    if(frameCount == 1)
        initGameData();

    readInput();

    if(!gamePause)
        runGameScript();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //render_drawBoxBackgrounds();
    render_drawBox();
    render_drawPolygon();
    //render_drawBoxPlatforms();
    //drawGrid();
    render_HUD();

    glutSwapBuffers();
}
