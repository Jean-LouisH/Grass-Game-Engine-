#include "Definitions.h"

void runKernel()
{
    compute_incrementTime();
    frameCount++;

    if(frameCount == 1)
        initGameData();

    readInput();

    if(!gamePause)
        runGameScript();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //enables alpha blending with glColor4ub().

    render_drawBox();
    render_drawPolygon();
    //drawGrid();
    render_HUD();

    glutSwapBuffers(); //freeglut buffer swap for animation.
}
