#include "GrassRoots_Framework.h"

////////////////////////////////////////
//2D Rendering
///////////////////////////////////////
void render_drawPolygonEntities()
{
    double smallerMapDimension;

    if(xMapSize <= yMapSize)
        smallerMapDimension = xMapSize;
    else
        smallerMapDimension = yMapSize;

    for (i = 0; i < MAX_POLYGONS; i++)
	{
		glBegin(GL_POLYGON);
		glColor3f(polygon[i].properties.colour[RED] / PEAK_COLOUR_LEVEL,
                    polygon[i].properties.colour[GREEN] / PEAK_COLOUR_LEVEL,
                    polygon[i].properties.colour[BLUE] / PEAK_COLOUR_LEVEL); //Ratios allow variable colour levels.

		for (j = 0; j < polygon[i].properties.sides; j++)
		{
			glVertex2f(((polygon[i].vertices[j].xPosition) - (smallerMapDimension / 2)
                            + ((smallerMapDimension/2) - (camera2D.target.xPosition))) / (smallerMapDimension / 2),
                    ((polygon[i].vertices[j].yPosition) - (smallerMapDimension / 2)
                            + ((smallerMapDimension/2) - (camera2D.target.yPosition))) / (smallerMapDimension / 2));
		}
		glEnd();
	}
}
void render_drawBoxPlatforms()
{
    double mapScale;

    if(xMapSize <= yMapSize)
        mapScale = xMapSize;
    else
        mapScale = yMapSize;

    for (i = 0; i < MAX_BOXES; i++)
	{
	    if(box[i].properties.classification == PLATFORM)
        {
            glBegin(GL_QUADS);
            glColor3f(box[i].properties.colour[RED] / PEAK_COLOUR_LEVEL,
                        box[i].properties.colour[GREEN] / PEAK_COLOUR_LEVEL,
                        box[i].properties.colour[BLUE] / PEAK_COLOUR_LEVEL);

            for (j = 0; j < 4; j++)
            {
                glVertex2f(((box[i].vertices[j].xPosition) - (mapScale / 2)
                                + ((mapScale/2) - (camera2D.target.xPosition))) / (mapScale / 2),
                        ((box[i].vertices[j].yPosition) - (yMapSize / 2)
                                + ((mapScale/2) - (camera2D.target.yPosition))) / (mapScale / 2));
            }

            glEnd();
        }
	}
}
void render_drawBoxBackgrounds()
{
        double mapScale;

    if(xMapSize <= yMapSize)
        mapScale = xMapSize;
    else
        mapScale = yMapSize;

    for (i = 0; i < MAX_BOXES; i++)
	{
	    if(box[i].properties.classification == BACKGROUND)
        {
            glBegin(GL_QUADS);
            glColor3f(box[i].properties.colour[RED] / PEAK_COLOUR_LEVEL,
                        box[i].properties.colour[GREEN] / PEAK_COLOUR_LEVEL,
                        box[i].properties.colour[BLUE] / PEAK_COLOUR_LEVEL);

            for (j = 0; j < 4; j++)
            {
                glVertex2f(((box[i].vertices[j].xPosition) - (mapScale / 2)
                                + ((mapScale/2) - (camera2D.target.xPosition))) / (mapScale / 2),
                        ((box[i].vertices[j].yPosition) - (mapScale / 2)
                                + ((mapScale/2) - (camera2D.target.yPosition))) / (mapScale / 2));
            }

            glEnd();
        }
	}
}
void render_drawGrid()
{

}
void render_HUD()
{

}
