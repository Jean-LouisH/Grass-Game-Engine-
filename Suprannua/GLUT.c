#include "Suprannua.h"

void runGLUT(int argc, char **argv)
{
	int screenWidthPixels;
	int screenHeightPixels;

	glutInit(&argc, argv);

	screenWidthPixels = glutGet(GLUT_SCREEN_WIDTH) * 0.750;
	screenHeightPixels = (screenWidthPixels * 0.563);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(screenWidthPixels, screenHeightPixels);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - screenWidthPixels) / 2,
							((glutGet(GLUT_SCREEN_HEIGHT) - screenHeightPixels) / 2) - 20);
	glutCreateWindow(gameTitle);

	//Run GLUT callback registration
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(keySpecial);
	glutSpecialUpFunc(keyUpSpecial);
	glutReshapeFunc(resize);

	glutDisplayFunc(runKernel);
	glutTimerFunc(FRAME_DELAY_MILLISECS, timer, FRAME_DELAY_MILLISECS);
	glutMainLoop();
}

void timer(int milliseconds)
{
    glutTimerFunc(milliseconds, timer, milliseconds);
    glutPostRedisplay();
}

void keyPressed(unsigned char key, int x, int y)
{
    keyStates[key] = true; //registers a button press in the input buffer.

    if (keyStates[27]) //Escape key
        exit(EXIT_SUCCESS);

    if(keyStates[9]) //Tab key to centre entire window.
        glutPositionWindow(((glutGet(GLUT_SCREEN_WIDTH) * 0.250)/ 2) + 1,
                           ((glutGet(GLUT_SCREEN_HEIGHT) * 0.250 * 0.563) / 2) + 22);
}

void keyUp(unsigned char key, int x, int y)
{
    if((keyStates['p'] || keyStates['P']) && (!isGamePaused))
    {
        isGamePaused = true;
        gameState = MENU; //Goes into menu immediately after pausing.
    }
    else if((keyStates['p'] || keyStates['P'] ) && (isGamePaused))
    {
        isGamePaused = false;
        gameState = GAMEPLAY;
    }

    keyStates[key] = false;
}

void keySpecial(unsigned char key, int x, int y)
{
    specialKeyStates[key] = true;
}

void keyUpSpecial(unsigned char key, int x, int y)
{
    specialKeyStates[key] = false;
}

void resize(int width, int height)
{
	//Prevent the window from being resized and aspect ratio from being distorted.
    glutReshapeWindow(glutGet(GLUT_SCREEN_WIDTH) * 0.750, (glutGet(GLUT_SCREEN_WIDTH) * 0.750) * 0.563);
}

