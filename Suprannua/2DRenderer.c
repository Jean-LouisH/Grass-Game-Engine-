#include "Definitions.h"
#include "2DRenderer.h"

////////////////////////////////////////
//2D Rendering
///////////////////////////////////////
void render_drawPolygon()
{
    for (i = 0; i < MAX_POLYGONS; i++)
	{
		glBegin(GL_POLYGON);
		glColor4ub(polygon[i].properties.colour[RED], polygon[i].properties.colour[GREEN],
                    polygon[i].properties.colour[BLUE], polygon[i].properties.colour[ALPHA]);

		for (j = 0; j < polygon[i].properties.edges; j++)//renders plotted points.
		{
            glVertex2f((polygon[i].vertices[j].xPosition - (camera2D.target.xPosition))/ (camera2D.viewport.width/2),
                       (polygon[i].vertices[j].yPosition - (camera2D.target.yPosition))/ (camera2D.viewport.height/2));
		}
		glEnd();
	}
}
void render_drawBox()
{
    for (i = 0; i < MAX_BOXES; i++)
	{

        glBegin(GL_QUADS);
        glColor4ub(box[i].properties.colour[RED], box[i].properties.colour[GREEN],
                   box[i].properties.colour[BLUE], box[i].properties.colour[ALPHA]);

        if(box[i].properties.classification == BACKGROUND)//renders backgrounds first.
        {
            for (j = 0; j < 4; j++)
            {
                glVertex2f((box[i].vertices[j].xPosition - (camera2D.target.xPosition))/ (camera2D.viewport.width/2),
                           (box[i].vertices[j].yPosition - (camera2D.target.yPosition))/ (camera2D.viewport.height/2));
            }
        }
        if(box[i].properties.classification == PLATFORM)//renders platforms after.
        {
            for (j = 0; j < 4; j++)
            {
                glVertex2f((box[i].vertices[j].xPosition - (camera2D.target.xPosition))/ (camera2D.viewport.width/2),
                           (box[i].vertices[j].yPosition - (camera2D.target.yPosition))/ (camera2D.viewport.height/2));
            }
        }
        glEnd();
	}
}
void render_drawGrid()
{

}
void render_postHUD()
{

    //For now testing HUD rendering and storage for data.
    char testText[128];
    char pauseText[7] = "PAUSED";
    static double fps;

    static double startTime;
    static double runTime;
    static double passedFrames;

    i = 0;
    //double a = 1.0;

    runTime = time(NULL);

    if(frameCount == 1)
        startTime = runTime;

    if(!isGamePaused)
        passedFrames++;

    if(runTime - startTime > 0.50)
    {
        fps = passedFrames / (runTime - startTime);
        startTime = runTime;
        passedFrames = 0;
    }

    sprintf(testText, SOFTWARE VERSION "Kernel time: %.0fs, Runtime: %.2fs, Frame count: %d, FPS: %.2f", kernelTime, timeCount, frameCount, fps);

    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(-1.0, 0.95);

    while(testText[i] != NULL)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *(testText+i));
        i++;
    }
    i = 0;

    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(-0.075, 0.0);
    if(isGamePaused)
    {
        while(pauseText[i] != NULL)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *(pauseText+i));
            i++;
        }
    }
}
