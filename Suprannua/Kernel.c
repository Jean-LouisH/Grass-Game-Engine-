#include "Suprannua.h"

void runKernel()
{
    currentTime = time(NULL);

    if(frameCount < 1)
    {
        startTime = currentTime;
        firstTimeSample = currentTime;
        initGameData();
    }

    kernelTime = currentTime - startTime;

    readInput();

    if(!isGamePaused)
    {
        physics_incrementTime();
        geometry_transform();
        frameCount++;
        passedFrames++;
        runGameScript();
    }

    if(currentTime - firstTimeSample >= 1)
    {
        framesPerSecond = passedFrames / (currentTime - firstTimeSample);
        firstTimeSample = time(NULL);
        passedFrames = 0;
    }

    //HUD_updateKernelStats();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //enables alpha blending with glColor4ub().

    render_displayBlockList();
    render_displayPolygonList();

	if(gridState)
		render_drawGrid();

    //render_postHUD();

    glutSwapBuffers(); //freeglut buffer swap for animation.
}
