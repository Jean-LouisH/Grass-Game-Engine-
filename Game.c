#include "Suprannua\Suprannua.h" 

/**
 *
 *				DOCUMENTATION IN PROGRESS...
 *
 */

/*Custom code for Initialisation, Scripting and Controls*/

//Global variables

char gameTitle[64]			= SOFTWARE VERSION "[Empty Game.c Source File.]";
Rect worldSizeMetres		= { 100,57 }; // m
double dpadSensitivity		= 5.0;
double cameraScrollSpeed	= 1.0;
double platformGravity		= 9.8; // m/s^2
double gravityConstant		= 6.674E-11; // m/s^2
bool isGamePaused			= false;


void initGameData()
{
	camera_setViewportWidth(edit_get(GAME, 0, WIDTH));
	camera_setTarget(edit_get(CAMERA, 0, XCENTRE), edit_get(CAMERA, 0, YCENTRE));
	edit_createRectangle(BACKGROUND, 0, edit_get(GAME, 0, WIDTH), 0, edit_get(GAME, 0, HEIGHT), GREY);

	//Insert Game Initialisation code.
}

//Controls
void readInput()
{
	int i;

	if (gameState == GAMEPLAY)
	{
		if (input_isPressed('w'))
		{
			;
		}

		if (input_isPressed('a'))
		{
			;
		}

		if (input_isPressed('s'))
		{
			;
		}

		if (input_isPressed('d'))
		{
			;
		}
	}
	else if (gameState == MENU)
	{
		if (input_isPressed('w'))
		{
			;
		}

		if (input_isPressed('a'))
		{
			;
		}

		if (input_isPressed('s'))
		{
			;
		}

		if (input_isPressed('d'))
		{
			;
		}
	}
	else if (gameState == CUSTOM1)
	{
		if (input_isPressed('w'))
		{
			camera_scroll(0.0, cameraScrollSpeed);
		}

		if (input_isPressed('a'))
		{
			camera_scroll(-1 * cameraScrollSpeed, 0.0);
		}

		if (input_isPressed('s'))
		{
			camera_scroll(0.0, -1 * cameraScrollSpeed);
		}

		if (input_isPressed('d'))
		{
			camera_scroll(cameraScrollSpeed, 0.0);
		}

		if (input_isPressed('q'))
		{
			camera_keepZoomingBy(cameraScrollSpeed);
		}

		if (input_isPressed('e'))
		{
			camera_keepZoomingBy(-cameraScrollSpeed);
		}

		if (input_isPressed('x'))
		{
			camera_setTarget(edit_get(GAME, 0, XCENTRE), edit_get(GAME, 0, YCENTRE));
			camera_setViewportWidth(edit_get(GAME, 0, WIDTH));
		}
	}
}

void runGameScript()
{
	physics_limitBoundary();
	physics_rigidBodyDynamics();
	physics_detectPolygonCollision(); 
	physics_detectPlatformCollision();

	//Insert Game Script code.
}

