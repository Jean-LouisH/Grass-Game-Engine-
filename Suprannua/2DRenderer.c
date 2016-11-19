#include "Definitions.h"

////////////////////////////////////////
//2D Rendering
///////////////////////////////////////
void render_drawPolygon()
{
    int i;
    int j;

    for (i = 0; i < MAX_POLYGONS; i++)
	{
	    if(polygon[i].properties.classification != NOTHING)
        {
            glBegin(GL_POLYGON);
            glColor4ub(polygon[i].properties.colour[RED], polygon[i].properties.colour[GREEN],
                        polygon[i].properties.colour[BLUE], polygon[i].properties.colour[ALPHA]);

            for (j = 0; j < polygon[i].properties.edges; j++)//renders plotted points.
            {
                glVertex2f((polygon[i].vertices[j].xPosition - (camera2D.target.xPosition))/
                            (camera2D.viewport.width/2),
                           (polygon[i].vertices[j].yPosition - (camera2D.target.yPosition))/
                            (camera2D.viewport.height/2));
            }
            glEnd();
        }
	}
}
void render_drawBlock()
{
    int i;
    int j;

    for (i = 0; i < MAX_BLOCKS; i++)
	{
        if(block[i].properties.classification != NOTHING)
        {
            glBegin(GL_QUADS);
            glColor4ub(block[i].properties.colour[RED], block[i].properties.colour[GREEN],
                       block[i].properties.colour[BLUE], block[i].properties.colour[ALPHA]);

            if(block[i].properties.classification == BACKGROUND)//renders backgrounds first.
            {
                for (j = 0; j < 4; j++)
                {
                    glVertex2f((block[i].vertices[j].xPosition - (camera2D.target.xPosition))/
                                (camera2D.viewport.width/2),
                               (block[i].vertices[j].yPosition - (camera2D.target.yPosition))/
                                (camera2D.viewport.height/2));
                }
            }
            if(block[i].properties.classification == PLATFORM)//renders platforms after.
            {
                for (j = 0; j < 4; j++)
                {
                    glVertex2f((block[i].vertices[j].xPosition - (camera2D.target.xPosition))/
                                (camera2D.viewport.width/2),
                               (block[i].vertices[j].yPosition - (camera2D.target.yPosition))/
                                (camera2D.viewport.height/2));
                }
            }
            glEnd();
        }
	}
}
void render_drawGrid()
{
    int i;
    int j;

}
void render_postHUD()
{
    int i;

    //For now testing HUD rendering and storage for data.
    char pauseText[7] = "PAUSED";

    i = 0;

    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(-1.0, 0.95);

    while(textCache[0].text[i] != NULL)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *(textCache[0].text+i));
        i++;
    }
    i = 0;

    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(-0.075, 0.0);
    if(isGamePaused)
    {
        while(textCache[1].text[i] != NULL)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *(textCache[1].text+i));
            i++;
        }
    }
}
