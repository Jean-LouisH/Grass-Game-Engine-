#include "SuprannuaEngine.h"

/* Backgrounds, platforms, entities and foregrounds are rendered in order
 * for both stored polygons and blocks.
 */

 /* The drawPolygon and drawBlock functions contain the vertex calculations in the form of:
  *
  *			glVertex2f(	(x - x_camera)) / (camera width / 2),
  *						(y - y_camera)) / (camera height / 2));
  *
  *   e.g.	glVertex2f(	(polygon[objectNumber].vertices[i].xPosition -
  *						(camera2D.target.xPosition)) / (camera2D.viewport.width/2),
  *						(polygon[objectNumber].vertices[i].yPosition -
  *						(camera2D.target.yPosition)) / (camera2D.viewport.height/2));
  *
  * To display the relative positions and scale of a collection of points to the camera.
  */

void render_displayStoredBlocks()
{
	int i;

	for (i = 0; i <= storedBlocks; i++)
		if (block[i].properties.classification == BACKGROUND)
			render_drawBlock(i);

	if (isGridEnabled)
		render_drawGrid();

	for (i = 0; i <= storedBlocks; i++)
		if (block[i].properties.classification == PLATFORM)
			render_drawBlock(i);

	for (i = 0; i <= storedBlocks; i++)
		if (block[i].properties.classification == ENTITY || block[i].properties.classification == AIRBOURNE)
			render_drawBlock(i);

	for (i = 0; i <= storedBlocks; i++)
		if (block[i].properties.classification == FOREGROUND)
			render_drawBlock(i);
}

void render_displayStoredPolygons()
{
	int i;

	for (i = 0; i <= storedPolygons; i++)
		if (polygon[i].properties.classification == BACKGROUND)
			render_drawPolygon(i);

	for (i = 0; i <= storedPolygons; i++)
		if (polygon[i].properties.classification == PLATFORM)
			render_drawPolygon(i);

	for (i = 0; i <= storedPolygons; i++)
		if (polygon[i].properties.classification == ENTITY || polygon[i].properties.classification == AIRBOURNE)
			render_drawPolygon(i);

	for (i = 0; i <= storedPolygons; i++)
		if (polygon[i].properties.classification == FOREGROUND)
			render_drawPolygon(i);
}

void render_displayText()
{
	int i;
	int j;

	for (j = 0; j <= storedTexts; j++)
	{
		i = 0;
		glColor4ub(textCache[j].colour[RED],
			textCache[j].colour[GREEN],
			textCache[j].colour[BLUE],
			textCache[j].colour[ALPHA]);

		if (textCache[j].classification == HUD)
		{
			glRasterPos2f(textCache[j].textPin.xPosition,
				textCache[j].textPin.yPosition);
		}
		else if (textCache[j].classification == ENTITY)
		{
			glRasterPos2f((textCache[j].textPin.xPosition -
				(camera2D.target.xPosition)) / (camera2D.viewport.width / 2),
				(textCache[j].textPin.yPosition -
				(camera2D.target.yPosition)) / (camera2D.viewport.height / 2));
		}

		if (j == 0)
		{
			if (isGamePaused)
			{
				while (textCache[j].textContent[i] != NULL)
				{
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *(textCache[j].textContent + i));
					i++;
				}
			}
		}
		else if (j != 1 || ((j == 1) && isKernelStatsEnabled))
		{
			while (textCache[j].textContent[i] != NULL)
			{
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *(textCache[j].textContent + i));
				i++;
			}
		}
	}
}

void render_drawBlock(int objectNumber)
{
	int i;

	glBegin(GL_QUADS);
	glColor4ub(block[objectNumber].properties.colour[RED],
		block[objectNumber].properties.colour[GREEN],
		block[objectNumber].properties.colour[BLUE],
		block[objectNumber].properties.colour[ALPHA]);

	for (i = 0; i < 4; i++) //All blocks have 4 sides.
	{
		glVertex2f((block[objectNumber].vertices[i].xPosition -
			(camera2D.target.xPosition)) / (camera2D.viewport.width / 2),
			(block[objectNumber].vertices[i].yPosition -
			(camera2D.target.yPosition)) / (camera2D.viewport.height / 2));
	}
	glEnd();
}

void render_drawGrid()
{
	int i;

	glBegin(GL_LINES);
	glColor4ub(255, 255, 255, 127); //Makes them 50% transparent white lines.

	//Renders all vertical lines across the world width from bottom to top.
	for (i = 0; i < worldSizeMetres.width; i++)
	{
		glVertex2f((i - (camera2D.target.xPosition)) / (camera2D.viewport.width / 2),
			(0 - (camera2D.target.yPosition)) / (camera2D.viewport.height / 2));
		glVertex2f((i - (camera2D.target.xPosition)) / (camera2D.viewport.width / 2),
			(worldSizeMetres.height - (camera2D.target.yPosition)) / (camera2D.viewport.height / 2));
	}

	//Renders all horizontal lines across the world height from left to right.
	for (i = 0; i < worldSizeMetres.height; i++)
	{
		glVertex2f((0 - (camera2D.target.xPosition)) / (camera2D.viewport.width / 2),
			(i - (camera2D.target.yPosition)) / (camera2D.viewport.height / 2));
		glVertex2f((worldSizeMetres.width - (camera2D.target.xPosition)) / (camera2D.viewport.width / 2),
			(i - (camera2D.target.yPosition)) / (camera2D.viewport.height / 2));
	}
	glEnd();
}

void render_drawPolygon(int objectNumber)
{
	int i;

	glBegin(GL_POLYGON);
	glColor4ub(polygon[objectNumber].properties.colour[RED],
		polygon[objectNumber].properties.colour[GREEN],
		polygon[objectNumber].properties.colour[BLUE],
		polygon[objectNumber].properties.colour[ALPHA]);

	for (i = 0; i < polygon[objectNumber].properties.edges; i++) //renders plotted points.
	{
		glVertex2f((polygon[objectNumber].vertices[i].xPosition -
			(camera2D.target.xPosition)) / (camera2D.viewport.width / 2),
			(polygon[objectNumber].vertices[i].yPosition -
			(camera2D.target.yPosition)) / (camera2D.viewport.height / 2));
	}
	glEnd();
}
