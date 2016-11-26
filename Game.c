#include "Suprannua\Suprannua.h" 

//////////////////////////////////////////////////////////////////////
//Custom code for Game Data, Logic, AI, Inputs
//////////////////////////////////////////////////////////////////////

//Global variables
char gameTitle[64]          = SOFTWARE VERSION "[Empty Game.c Source File.]";
Rect worldSizeMetres		= { 100,57 }; // m
double dpadSensitivity      = 5.0; // m/s
double cameraScrollSpeed    = 1.0; // m/s
double platformGravity      = 9.8; // m/s^2
bool isGamePaused           = false;


void initGameData()
{
	camera_setWidth(100.0);
	camera_setTarget(camera2D.viewport.width / 2, camera2D.viewport.height / 2);

	edit_createRectangle(BACKGROUND, 0, edit_get(GAME, 0, WIDTH), 0, edit_get(GAME, 0, HEIGHT), GREY);

	//Insert Game Initialisation code.
}

void runGameScript()
{
	physics_limitBoundary();
	physics_rigidBodyDynamics(); 
	physics_detectCollision(); 
	physics_detectPlatformCollision();

	//Insert Game Script code.

}

//Controls
void readInput()
{

    if(gameState == GAMEPLAY)
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

    }
}

