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

RadialPolygon polygon[MAX_POLYGONS] = {0};
Box box[MAX_BOXES] = {0};

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
    frameCount++;

    if(frameCount == 1)
        initGameData();

    readInput();

    if(!gamePause)
        runGameScript();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    adjustCamera();
    drawBackground();
    drawRadialPolygons();
    drawBoxes();
    //drawGrid();
    renderHUD();

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
}

//////////////////////////////////
//GrassKernel Functions
//////////////////////////////////

//Rendering
void drawRadialPolygons()
{
    double mapScale;

    if(xMapSize >= yMapSize)
        mapScale = xMapSize;
    else
        mapScale = yMapSize;

    for (i = 0; i < MAX_POLYGONS; i++)
	{
		glBegin(GL_POLYGON);
		glColor3f(polygon[i].properties.colour[RED] / PEAK_COLOUR_LEVEL,
                    polygon[i].properties.colour[GREEN] / PEAK_COLOUR_LEVEL,
                    polygon[i].properties.colour[BLUE] / PEAK_COLOUR_LEVEL);

		for (j = 0; j < MAX_POLYGON_SIDES; j++)
		{
			glVertex2f(((polygon[i].vertices[j].xPosition) - (mapScale / 2)) / (mapScale / 2),
				((polygon[i].vertices[j].yPosition) - (mapScale / 2)) / (mapScale / 2));
		}
		glEnd();
	}
}
void drawBoxes()
{
    double mapScale;

    if(xMapSize >= yMapSize)
        mapScale = xMapSize;
    else
        mapScale = yMapSize;

    for (i = 0; i < MAX_BOXES; i++)
	{
		glBegin(GL_QUADS);
		glColor3f(box[i].properties.colour[RED] / PEAK_COLOUR_LEVEL,
                    box[i].properties.colour[GREEN] / PEAK_COLOUR_LEVEL,
                    box[i].properties.colour[BLUE] / PEAK_COLOUR_LEVEL);

		for (j = 0; j < 4; j++)
		{
			glVertex2f(((box[i].vertices[j].xPosition) - (mapScale / 2)) / (mapScale / 2),
				((box[i].vertices[j].yPosition) - (mapScale / 2)) / (mapScale / 2));
		}

		glEnd();
	}
}
void drawBackground()
{

}
void drawGrid()
{

}
void adjustCamera()
{

}
void renderHUD()
{

}

//Instructions
void grass_create(unsigned char object, unsigned char type, double newRadius, double newWidth,
       double newHeight, double newXPosition, double newYPosition,
       unsigned char red, unsigned char green, unsigned char blue)
{
    srand((unsigned)time(NULL));

    switch(object)
    {
        case POLYGON: polygon[0].properties.classification = type;
                        polygon[0].radius = newRadius;
                        if(newXPosition == 0 || newYPosition == 0)
                        {
                            polygon[0].centre.xPosition = rand() %
                            (int)(xMapSize - (2 * polygon[0].radius)) + (polygon[0].radius);
                            polygon[0].centre.yPosition = rand() %
                            (int)(yMapSize - (2 * polygon[0].radius)) + (polygon[0].radius);
                        }
                        else
                        {
                            polygon[0].centre.xPosition = newXPosition;
                            polygon[0].centre.yPosition = newYPosition;
                        }
                        polygon[0].properties.colour[RED] = red;
                        polygon[0].properties.colour[GREEN] = green;
                        polygon[0].properties.colour[BLUE] = blue;

                        for (j = 0; j < MAX_POLYGON_SIDES; j++)
                        {
                            polygon[0].vertices[j].xPosition = polygon[0].centre.xPosition +
                                (polygon[0].radius * cos(((360 / MAX_POLYGON_SIDES) * (j)) * (PI / 180)));
                            polygon[0].vertices[j].yPosition = polygon[0].centre.yPosition +
                                (polygon[0].radius * sin(((360 / MAX_POLYGON_SIDES) * (j)) * (PI / 180)));
                        }
        break;
        case BOX:     box[0].properties.classification = type;
                        if(newXPosition == 0 || newYPosition == 0)
                        {
                            box[0].centre.xPosition = rand() % (int)(xMapSize - (newWidth)) + (newWidth);
                            box[0].centre.yPosition = rand() % (int)(yMapSize - (newHeight)) + (newHeight);
                        }
                        box[0].properties.colour[RED] = red;
                        box[0].properties.colour[GREEN] = green;
                        box[0].properties.colour[BLUE] = blue;

                        for (j = 0; j < 4; j++)
                        {
                            box[0].vertices[j].xPosition = box[0].centre.xPosition + ((newWidth / 2)
                                    * sqrt(2) * (cos((45 + (j * 90)) * (PI / 180))));
                            box[0].vertices[j].yPosition = box[0].centre.yPosition + ((newHeight / 2)
                                    * sqrt(2) * (sin((45 + (j * 90)) * (PI / 180))));
                        }
                        break;
    }
}
