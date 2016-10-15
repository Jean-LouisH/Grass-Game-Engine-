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
		glColor4ub(polygon[i].properties.colour[RED], polygon[i].properties.colour[GREEN], polygon[i].properties.colour[BLUE], 255);

		for (j = 0; j < polygon[i].properties.sides; j++)//renders plotted points.
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
        glColor4ub(box[i].properties.colour[RED], box[i].properties.colour[GREEN], box[i].properties.colour[BLUE], 255);

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
void render_HUD()
{

}
