#include "Definitions.h"

////////////////////////////////////////
//2D Rendering
///////////////////////////////////////
void render_displayPolygonList()
{
    int i;

    for (i = 0; i < MAX_POLYGONS; i++)
	    if(polygon[i].properties.classification == BACKGROUND)//renders backgrounds first.
            render_drawPolygon(i);

	for (i = 0; i < MAX_POLYGONS; i++)
        if(polygon[i].properties.classification == ENTITY)//renders entities last.
            render_drawPolygon(i);
}
void render_drawPolygon(int objectNumber)
{
    int i ;

    glBegin(GL_POLYGON);
    glColor4ub( polygon[objectNumber].properties.colour[RED],
                polygon[objectNumber].properties.colour[GREEN],
                polygon[objectNumber].properties.colour[BLUE],
                polygon[objectNumber].properties.colour[ALPHA]);

    for (i = 0; i < polygon[objectNumber].properties.edges; i++)//renders plotted points.
    {
        glVertex2f((polygon[objectNumber].vertices[i].xPosition -
                    (camera2D.target.xPosition)) / (camera2D.viewport.width/2),
                    (polygon[objectNumber].vertices[i].yPosition -
                     (camera2D.target.yPosition)) / (camera2D.viewport.height/2));
    }
    glEnd();
}
void render_displayBlockList()
{
    int i;

    for (i = 0; i < MAX_BLOCKS; i++)
        if(block[i].properties.classification == BACKGROUND)//renders backgrounds first.
            render_drawBlock(i);

    for(i = 0; i < MAX_BLOCKS; i++)
        if(block[i].properties.classification == PLATFORM)//renders platforms after.
            render_drawBlock(i);

    for(i = 0; i < MAX_BLOCKS; i++)
        if(block[i].properties.classification == ENTITY)//renders entities last.
            render_drawBlock(i);
}
render_drawBlock(int objectNumber)
{
    int i ;

    glBegin(GL_QUADS);
    glColor4ub( block[objectNumber].properties.colour[RED],
                block[objectNumber].properties.colour[GREEN],
                block[objectNumber].properties.colour[BLUE],
                block[objectNumber].properties.colour[ALPHA]);

    for (i = 0; i < 4; i++)
    {
        glVertex2f((block[objectNumber].vertices[i].xPosition -
                    (camera2D.target.xPosition)) / (camera2D.viewport.width/2),
                    (block[objectNumber].vertices[i].yPosition -
                     (camera2D.target.yPosition)) / (camera2D.viewport.height/2));
    }
    glEnd();
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
