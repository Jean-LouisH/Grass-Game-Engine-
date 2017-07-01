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

void render_addRenderingLayer(unsigned char objectType, 
	unsigned char classification, 
	int objectNumber)
{
	int i;

	switch (classification)
	{
	case BACKGROUND:

		for (i = 0; i < MAX_DEFAULT_OBJECTS; i++)
		{
			if (backgrounds[i].objectType == 0)
				break;
		}

		if (i > storedBackgrounds)
			storedBackgrounds = i;

		backgrounds[i].objectNumber = objectNumber;
		backgrounds[i].objectType = objectType;
		break;

	case PLATFORM:

		for (i = 0; i < MAX_DEFAULT_OBJECTS; i++)
		{
			if (platforms[i].objectType == 0)
				break;
		}

		if (i > storedPlatforms)
			storedPlatforms = i;

		platforms[i].objectNumber = objectNumber;
		platforms[i].objectType = objectType;
		break;

	case ENTITY:
	case FLOATING:

		for (i = 0; i < MAX_DEFAULT_OBJECTS; i++)
		{
			if (entities[i].objectType == 0)
				break;
		}

		if (i > storedEntities)
			storedEntities = i;

		entities[i].objectNumber = objectNumber;
		entities[i].objectType = objectType;
		break;

	case FOREGROUND:

		for (i = 0; i < MAX_DEFAULT_OBJECTS; i++)
		{
			if (foregrounds[i].objectType == 0)
				break;
		}

		if (i > storedForegrounds)
			storedForegrounds = i;

		foregrounds[i].objectNumber = objectNumber;
		foregrounds[i].objectType = objectType;
		break;
	}
}

void render_displayBackgrounds()
{
	int i;

	for (i = 0; i <= storedBackgrounds; i++)
		render_drawByObjectType(backgrounds[i].objectNumber, backgrounds[i].objectType);
}

void render_displayPlatforms()
{
	int i;

	for (i = 0; i <= storedPlatforms; i++)
		render_drawByObjectType(platforms[i].objectNumber, platforms[i].objectType);
}

void render_displayEntities()
{
	int i;

	for (i = 0; i <= storedEntities; i++)
		render_drawByObjectType(entities[i].objectNumber, entities[i].objectType);
}

void render_displayForegrounds()
{
	int i;

	for (i = 0; i <= storedForegrounds; i++)
		render_drawByObjectType(foregrounds[i].objectNumber, foregrounds[i].objectType);
}

void render_drawByObjectType(int objectNumber, unsigned char objectType)
{
	switch (objectType)
	{
	case POLYGON: render_drawPolygon(objectNumber); break;
	case BLOCK: render_drawBlock(objectNumber); break;
	}
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
			/*Render to camera layout*/
			glRasterPos2f(textCache[j].textPin.xPosition,
				textCache[j].textPin.yPosition);
		}
		else if (textCache[j].classification == ENTITY)
		{
			/*Render to map*/
			glRasterPos2f((textCache[j].textPin.xPosition -
				(camera2D.target.xPosition)) / (camera2D.viewport.width / 2),
				(textCache[j].textPin.yPosition -
				(camera2D.target.yPosition)) / (camera2D.viewport.height / 2));
		}

		/*For the paused text cache*/
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
