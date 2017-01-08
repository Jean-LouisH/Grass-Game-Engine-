#include "Suprannua.h"

void runSuprannuaKernel()
{
    currentTime = time(NULL);

    if(frameCount == 0)
    {
		text_set(HUD, -0.075, 0.0, "PAUSED", WHITE);
		text_set(HUD, -1.0, 0.95, "", WHITE);
        startTime = currentTime;
        firstTimeSample = currentTime;
        initGame();
    }

    kernelTime = currentTime - startTime;

    readInput();

    if(!isGamePaused)
    {
        physics_incrementTime();
        geometry_transform();
        frameCount++;
        passedFrames++;
        runGame();
    }

    if(currentTime - firstTimeSample >= 1)
    {
        framesPerSecond = passedFrames / (currentTime - firstTimeSample);
        firstTimeSample = time(NULL);
        passedFrames = 0;
    }

	text_updateKernelStats();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //enables alpha blending.

    render_displayStoredBlocks();
    render_displayStoredPolygons();

	if(isGridEnabled)
		render_drawGrid();

    render_displayText();

    glutSwapBuffers(); //freeglut buffer swap for animation.
}
