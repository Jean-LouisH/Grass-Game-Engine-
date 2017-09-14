#include "SuprannuaEngine.h"

void keyPressed(unsigned char key, int x, int y)
{
	/*Limits the key presses to ASCII characters*/
	if (key < 128)
	{
		keyStates[key] = true; //registers a button press in the input buffer.
	}

	if (keyStates[27]) //Escape key
	{
		Mix_Quit();
		SDL_Quit();
		exit(EXIT_SUCCESS);
	}

	if (keyStates[9]) //Tab key to centre entire window.
		glutPositionWindow(((glutGet(GLUT_SCREEN_WIDTH) * 0.250) / 2) + 1,
		((glutGet(GLUT_SCREEN_HEIGHT) * 0.250 * 0.563) / 2) + 22);
}

void keySpecial(unsigned char key, int x, int y)
{
	specialKeyStates[key] = true;
}

void keyUp(unsigned char key, int x, int y)
{
	if (input_isPressed('p') && (!isGamePaused))
	{
		isGamePaused = true;
		gameState = MENU;			//Goes into menu immediately after pausing.
		Mix_PauseMusic();
	}
	else if (input_isPressed('p') && (isGamePaused))
	{
		isGamePaused = false;
		gameState = GAMEPLAY;
		Mix_ResumeMusic();
	}

	/*Soft resets the entire engine when these keys are pressed together. 
	User defined game variables are not affected and should be resetted manually.*/
	if (input_isPressed('z') && input_isPressed('c') &&
		input_isPressed('r') && isGamePaused)
	{
		edit_reset();
	}

	if (key < 128)
	{
		keyStates[key] = false;
	}
}

void keyUpSpecial(unsigned char key, int x, int y)
{
	specialKeyStates[key] = false;
}

void resize(int width, int height)
{
	/*Prevent the window from being resized and aspect ratio from being distorted.*/
	glutReshapeWindow(glutGet(GLUT_SCREEN_WIDTH) * 0.750, (glutGet(GLUT_SCREEN_WIDTH) * 0.750) * 0.563);
}

void timer(int milliseconds)
{
	glutTimerFunc(milliseconds, timer, milliseconds);
	glutPostRedisplay();
}

