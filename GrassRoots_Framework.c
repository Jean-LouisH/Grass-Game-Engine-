/**

File:           GrassRoots_Framework.c
Description:    A superannuated 2D platformer game framework developed in C and legacy OpenGL. For Academic Purposes.

Author:         Jean-Louis Haywood (Haywood.JeanLouis@gmail.com)
Created:        01/09/2016
Updated:        16/09/2016
Version:        1.0

*/

#include "GrassRoots_Framework.h"

//Loop iterations
int i;
int j;
int k;

//Runtime frame count
int frameCount = 0;
float timeCount;

RadialPolygon polygon[MAX_POLYGONS] = {0};
Box box[MAX_BOXES] = {0};
Camera camera2D;

char headsUpDisplay[8][32];

int main(int argc, char **argv)
{
    runGLUT(argc, argv);
    return 0;
}

void runGLUT(int argc, char **argv)
{
    //GLUT initialisation
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(screenWidth, screenHeight);
    glutCreateWindow(gameTitle);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - screenWidth) / 2,
                           (glutGet(GLUT_SCREEN_HEIGHT) - screenHeight) / 2);

    //Run GLUT callback registration
    glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyUp);
    glutDisplayFunc(runGrassKernel);
    glutReshapeFunc(reshape);
    glutTimerFunc(FRAME_DELAY_MILLISECS, timer, FRAME_DELAY_MILLISECS);
    glutMainLoop();
}

////////////////////////////////////////
//GLUT Callback function implementations
///////////////////////////////////////
void runGrassKernel()
{
    compute_incrementTime();
    frameCount++;

    if(frameCount == 1)
        initGameData();

    readInput();

    if(!gamePause)
        runGameScript();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    render_drawBoxBackgrounds();
    render_drawPolygonEntities();
    render_drawBoxPlatforms();
    //drawGrid();
    render_HUD();

    glutSwapBuffers();
}
void timer(int milliseconds)
{
    glutTimerFunc(milliseconds, timer, milliseconds);
    glutPostRedisplay();
}
void reshape(int width, int height)
{
    //Courtesy of Swiftless OpenGL tutorials.
   glViewport (0, 0, (GLsizei) width, (GLsizei) height);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(60.0, (GLfloat) width/(GLfloat) height, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (0.0, 0.0, 1.75, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void keyPressed(unsigned char key, int x, int y)
{
    keyStates[key] = true;
}
void keyUp(unsigned char key, int x, int y)
{
    if((keyStates['p'] || keyStates['P']) && (!gamePause))
        gamePause = true;

    else if((keyStates['p'] || keyStates['P'] ) && (gamePause))
        gamePause = false;

    keyStates[key] = false;
    polygon[0].properties.xVelocity = 0;
}

//////////////////////////////////
//GrassKernel Functions
//////////////////////////////////

//Compute

void compute_plotPolygon(int objectNumber)
{
    for (j = 0; j < polygon[k].properties.sides; j++)
    {
        polygon[k].vertices[j].xPosition = polygon[k].centre.xPosition +
                (polygon[k].radius * cos(((360 / polygon[k].properties.sides) * (j)) * (PI / 180)));
        polygon[k].vertices[j].yPosition = polygon[k].centre.yPosition +
                (polygon[k].radius * sin(((360 / polygon[k].properties.sides) * (j)) * (PI / 180)));
    }
}

void compute_plotBox(int objectNumber)
{
    for (j = 0; j < 4; j++)
    {
        box[k].vertices[j].xPosition = box[k].centre.xPosition + ((box[k].boxWidth / 2)
                    * sqrt(2) * (cos((45 + (j * 90)) * (PI / 180))));
        box[k].vertices[j].yPosition = box[k].centre.yPosition + ((box[k].boxHeight / 2)
                    * sqrt(2) * (sin((45 + (j * 90)) * (PI / 180))));
    }
}
void compute_detectPlatformCollision()
{
    for(i = 0; i < MAX_POLYGONS; i++)
    {
        //if((polygon[i].centre.yPosition) - (polygon[i].radius) <= 0)
        for(j = 0; j < MAX_BOXES; j++)
        {
            if(box[j].properties.classification == PLATFORM)
            {
                if(polygon[i].centre.yPosition - polygon[i].radius <=
                        box[j].centre.yPosition + (box[j].boxHeight / 2) &&
                    polygon[i].centre.yPosition - polygon[i].radius >
                        box[j].centre.yPosition - (box[j].boxHeight / 2))
                {
                    if(polygon[i].centre.xPosition >
                            box[j].centre.xPosition - (box[j].boxWidth / 2) &&
                       polygon[i].centre.xPosition <
                            box[j].centre.xPosition + (box[j].boxWidth / 2))
                    {
                        polygon[i].properties.yVelocity = polygon[i].properties.yVelocity * -1 * friction;
                        if(polygon[i].properties.yVelocity < 0.01)
                        //    polygon[i].properties.yVelocity = platformGravity;
                            polygon[i].properties.yVelocity = box[j].properties.yVelocity + platformGravity;
                    }
                }
            }
        }

    }
    for(i = 0; i < MAX_BOXES; i++)
    {
        if((box[i].centre.yPosition) - (box[i].boxHeight/2) <= 0)
        {
            box[i].properties.yVelocity = box[i].properties.yVelocity * -1 * friction;
            if(box[i].properties.yVelocity < 0.01)
                box[i].properties.yVelocity = 0.98;
        }
    }
}
void translateRotation()
{
    for (i = 0; i < MAX_POLYGONS; i++)
	{
		while (polygon[i].properties.angle >= 360)
		{
			polygon[i].properties.angle -= 360;
		}

		for (j = 0; j < polygon[i].properties.sides; j++)
		{
			polygon[i].vertices[j].xPosition = polygon[i].centre.xPosition +
				(polygon[i].radius * cos(((360 / polygon[i].properties.sides) *
                (j) - polygon[i].properties.angle) * (PI / 180)));
                polygon[i].vertices[j].yPosition = polygon[i].centre.yPosition +
				(polygon[i].radius * sin(((360 / polygon[i].properties.sides) *
                (j) - polygon[i].properties.angle) * (PI / 180)));
		}
	}
}
void translatePosition()
{
    for (i = 0; i < MAX_POLYGONS; i++)
	{
		//X Axis
		polygon[i].centre.xPosition += (polygon[i].properties.xVelocity * FRAME_DELAY_MILLISECS * 0.001);
		for (j = 0; j < polygon[i].properties.sides; j++)
		{
			polygon[i].vertices[j].xPosition +=
				(polygon[i].properties.xVelocity * FRAME_DELAY_MILLISECS * 0.001);
		}
		//Y Axis
		polygon[i].centre.yPosition += (polygon[i].properties.yVelocity * FRAME_DELAY_MILLISECS * 0.001);
		for (j = 0; j < polygon[i].properties.sides; j++)
		{
			polygon[i].vertices[j].yPosition +=
				(polygon[i].properties.yVelocity * FRAME_DELAY_MILLISECS * 0.001);
		}
	}

	for (i = 0; i < MAX_BOXES; i++)
	{
		//X Axis
		box[i].centre.xPosition += (box[i].properties.xVelocity * FRAME_DELAY_MILLISECS * 0.001);
		for (j = 0; j < 4; j++)
		{
			box[i].vertices[j].xPosition +=
				(box[i].properties.xVelocity * FRAME_DELAY_MILLISECS * 0.001);
		}
		//Y Axis
		box[i].centre.yPosition += (box[i].properties.yVelocity * FRAME_DELAY_MILLISECS * 0.001);
		for (j = 0; j < 4; j++)
		{
			box[i].vertices[j].yPosition +=
				(box[i].properties.yVelocity * FRAME_DELAY_MILLISECS * 0.001);
		}
	}
}
void compute_incrementTime()
{
    timeCount = (frameCount * FRAME_DELAY_MILLISECS)/1000;
}

//Rendering
void render_drawPolygonEntities()
{
    double mapScale;

    if(xMapSize <= yMapSize)
        mapScale = xMapSize;
    else
        mapScale = yMapSize;

    for (i = 0; i < MAX_POLYGONS; i++)
	{
		glBegin(GL_POLYGON);
		glColor3f(polygon[i].properties.colour[RED] / PEAK_COLOUR_LEVEL,
                    polygon[i].properties.colour[GREEN] / PEAK_COLOUR_LEVEL,
                    polygon[i].properties.colour[BLUE] / PEAK_COLOUR_LEVEL);

		for (j = 0; j < polygon[i].properties.sides; j++)
		{
			glVertex2f(((polygon[i].vertices[j].xPosition) - (mapScale / 2)
                            + ((mapScale/2) - (camera2D.target.xPosition))) / (mapScale / 2),
                    ((polygon[i].vertices[j].yPosition) - (mapScale / 2)
                            + ((mapScale/2) - (camera2D.target.yPosition))) / (mapScale / 2));
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

void compute_scrollCamera(double xScroll, double yScroll)
{
    camera2D.target.xPosition += xScroll;
    camera2D.target.yPosition += yScroll;
}
void compute_gravitate(unsigned char object, int objectNumber)
{
    switch(object)
    {
        case POLYGON:   polygon[objectNumber].properties.yVelocity -= platformGravity;
        break;
        case BOX:       box[objectNumber].properties.yVelocity -= platformGravity;
        break;
    }
}
void compute_roll(unsigned char object, int objectNumber)
{
    switch(object)
    {
    case POLYGON:      //if(polygon[objectNumber].centre.yPosition - polygon[objectNumber].radius < 1)
                    if(polygon[objectNumber].properties.xVelocity < 0)
                        AI_spin(POLYGON, objectNumber, ANTICLOCKWISE, (dpadSensitivity / polygon[objectNumber].radius));
                    else if(polygon[objectNumber].properties.xVelocity > 0)
                        AI_spin(POLYGON, objectNumber, CLOCKWISE, (dpadSensitivity / polygon[objectNumber].radius));
    break;
    /*case BOX:          if(box[objectNumber].properties.xVelocity < 0)
                            box[objectNumber].properties.angle -= dpadSensitivity / 1;
                        else if(box[objectNumber].properties.xVelocity > 0)
                            box[objectNumber].properties.angle += dpadSensitivity / 1;
    break;*/
    }
}

//Instructions
void grass_camera(double newXPosition, double newYPosition)
{
    camera2D.target.xPosition = newXPosition;
    camera2D.target.yPosition = newYPosition;
}
void grass_create(unsigned char object, unsigned char type, int numberOfSides,
                  double newRadius, double newWidth, double newHeight, double newXPosition,
                  double newYPosition,unsigned char red, unsigned char green, unsigned char blue)
{
    srand((unsigned)time(NULL));
    switch(object)
    {
        case POLYGON:   k = 0;
                        while(polygon[k].properties.classification != NOTHING) //searches for a non-empty cell.
                        {
                            k++;
                        }

                        polygon[k].properties.classification = type;
                        polygon[k].properties.sides = numberOfSides;
                        polygon[k].radius = newRadius;

                        if(newXPosition == 0 || newYPosition == 0) //provides a random position if non is specified.
                        {
                            polygon[k].centre.xPosition = rand() %
                            (int)(xMapSize - (2 * polygon[k].radius) * (k + 1))+ (polygon[k].radius);
                            polygon[k].centre.yPosition = rand() %
                            (int)(yMapSize - (2 * polygon[k].radius) * (k + 1)) + (polygon[k].radius);
                        }
                        else
                        {
                            polygon[k].centre.xPosition = newXPosition;
                            polygon[k].centre.yPosition = newYPosition;
                        }

                        polygon[k].properties.colour[RED] = red;
                        polygon[k].properties.colour[GREEN] = green;
                        polygon[k].properties.colour[BLUE] = blue;

                        compute_plotPolygon(k);
        break;
        case BOX:       k = 0;
                        while(box[k].properties.classification != NOTHING) //searches for a non-empty cell.
                        {
                            k++;
                        }

                        box[k].properties.classification = type;
                        box[k].boxWidth = newWidth;
                        box[k].boxHeight = newHeight;
                        if(newXPosition == 0 || newYPosition == 0)
                        {
                            box[k].centre.xPosition = rand() %
                            (int)(xMapSize - (box[k].boxWidth) * (k + 1)) + (box[k].boxWidth);
                            box[k].centre.yPosition = rand() %
                            (int)(yMapSize - (box[k].boxHeight) * (k + 1)) + (box[k].boxHeight);
                        }
                        else
                        {
                            box[k].centre.xPosition = newXPosition;
                            box[k].centre.yPosition = newYPosition;
                        }
                        box[k].properties.colour[RED] = red;
                        box[k].properties.colour[GREEN] = green;
                        box[k].properties.colour[BLUE] = blue;

                        compute_plotBox(k);
        break;
    }
}
void grass_remove(unsigned char object, int objectNumber)
{
    switch(object)
    {
        case POLYGON:
                        polygon[objectNumber].radius = 0.0;
                        polygon[objectNumber].properties.acceleration = 0.0;
                        polygon[objectNumber].properties.angle = 0.0;
                        polygon[objectNumber].properties.classification = NOTHING;
                        for(i  = 0; i < 3; i++)
                            polygon[objectNumber].properties.colour[i] = 0;
                        polygon[objectNumber].properties.mass = 0.0;
                        polygon[objectNumber].properties.xVelocity = 0.0;
                        polygon[objectNumber].properties.yVelocity = 0.0;
                        polygon[objectNumber].centre.xPosition = 0.0;
                        polygon[objectNumber].centre.yPosition = 0.0;
                        for(i = 0; i < MAX_POLYGON_SIDES; i++)
                        {
                            polygon[objectNumber].vertices[i].xPosition = 0.0;
                            polygon[objectNumber].vertices[i].yPosition = 0.0;
                        }
        break;
        case BOX:
                        box[objectNumber].centre.xPosition = 0.0;
                        box[objectNumber].centre.yPosition = 0.0;
                        box[objectNumber].properties.acceleration = 0.0;
                        box[objectNumber].properties.angle = 0.0;
                        box[objectNumber].properties.classification = NOTHING;
                        for(i = 0; i < 3; i++)
                            box[objectNumber].properties.colour[i] = 0;
                        box[objectNumber].properties.mass = 0.0;
                        box[objectNumber].properties.xVelocity = 0.0;
                        box[objectNumber].properties.yVelocity = 0.0;
                        for(i = 0; i < 4; i++)
                        {
                            box[objectNumber].vertices[i].xPosition = 0.0;
                            box[objectNumber].vertices[i].yPosition = 0.0;
                        }
        break;
    }
}
void grass_move(unsigned char object, int objectNumber, double newXPosition, double newYPosition)
{
    switch(object)
    {
        case POLYGON:   polygon[objectNumber].centre.xPosition = newXPosition;
                        polygon[objectNumber].centre.yPosition = newYPosition;

                        compute_plotPolygon(k);
        break;
        case BOX:       box[objectNumber].centre.xPosition = newXPosition;
                        box[objectNumber].centre.yPosition = newYPosition;

                        compute_plotBox(k);
        break;
    }
}
void grass_resize(unsigned char object, int objectNumber, double scale)
{
    switch(object)
    {
        case POLYGON:   polygon[objectNumber].radius = polygon[objectNumber].radius * scale;

                        compute_plotPolygon(k);
        break;
        case BOX:
                        box[objectNumber].boxWidth = box[objectNumber].boxWidth * scale;
                        box[objectNumber].boxHeight = box[objectNumber].boxHeight * scale;

                        compute_plotBox(k);
        break;
    }
}

void grass_change(unsigned char object, int objectNumber, unsigned char attribute, double amount)
{
    switch(attribute)
    {
        case GRAVITY:   if(object == GAME)
                            platformGravity = amount;
        break;
        case FRICTION:  if(object == GAME)
                            friction = amount;
        break;

        case ANGLE:     if(object == POLYGON)
                            polygon[objectNumber].properties.angle = amount;
                        if(object == BOX)
                            box[objectNumber].properties.angle = amount;
        break;
        case MASS:      if(object == POLYGON)
                            polygon[objectNumber].properties.mass = amount;
                        if(object == BOX)
                            box[objectNumber].properties.mass = amount;
        break;
        case XVELOCITY: if(object == POLYGON)
                            polygon[objectNumber].properties.xVelocity = amount;
                        if(object == BOX)
                            box[objectNumber].properties.xVelocity = amount;
        break;
        case YVELOCITY: if(object == POLYGON)
                            polygon[objectNumber].properties.yVelocity = amount;
                        if(object == BOX)
                            box[objectNumber].properties.yVelocity = amount;
        break;
    }
}
void grass_colour(unsigned char object, int objectNumber, unsigned char red, unsigned char green, unsigned char blue)
{
    switch(object)
    {
        case POLYGON:   polygon[objectNumber].properties.colour[RED]    = red;
                        polygon[objectNumber].properties.colour[GREEN]  = green;
                        polygon[objectNumber].properties.colour[BLUE]   = blue;
        break;
        case BOX:       box[objectNumber].properties.colour[RED]    = red;
                        box[objectNumber].properties.colour[GREEN]  = green;
                        box[objectNumber].properties.colour[BLUE]   = blue;
        break;
    }
}
void grass_force(unsigned char firstObject, int firstObjectNumber,
                 unsigned char preposition, unsigned char secondObject, int secondobjectNumber)// preposition - "to", "from"
{

}

//Game Artificial Intelligence

void AI_spin(unsigned char object, int objectNumber, unsigned char direction, double amount)
{
    switch(object)
    {
        case POLYGON: polygon[objectNumber].properties.angle += ((direction * 2) - 1) * amount;
        break;
    }
}
