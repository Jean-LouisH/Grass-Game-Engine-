#include "../Suprannua Engine/SuprannuaEngine.h" 

/**
*
*				DOCUMENTATION IN PROGRESS...
*
*/

/*Custom code for Initialisation, Scripting and Controls*/

/*Global variables*/

char gameTitle[64] = "AI Lab [Test Scene, " SOFTWARE VERSION "]";
Rect worldSizeMetres = { 50,29 }; // m
double dpadSensitivity = 10.0; // m/s
double cameraScrollSpeed = 50.0; // m/s
double platformGravity = 9.8; // m/s^2
double gravityConstant = 6.674E-11; // m/s^2
bool isGamePaused = false;


void initGame()
{
	camera_setViewportWidth(edit_get(GAME, 0, WIDTH));
	camera_setTarget(edit_get(CAMERA, 0, XCENTRE), edit_get(CAMERA, 0, YCENTRE));
	edit_createRectangle(BACKGROUND, 0, edit_get(GAME, 0, WIDTH), 0, edit_get(GAME, 0, HEIGHT), SKY_BLUE);

	/*Insert Game Initialisation code.*/
	edit_createRectangle(PLATFORM, 0, edit_get(GAME, 0, WIDTH), 0.0, 1.0, BROWN);
	edit_createRectangle(PLATFORM, 0, edit_get(GAME, 0, WIDTH), 1.0, 1.25, DARK_GREEN);
	edit_createRectangle(PLATFORM, 6.0, 12.0, 8.0, 8.25, DARK_GREEN);
	edit_createRectangle(PLATFORM, 6.0 + 5, 12.0 + 5, 8.0 - 4, 8.25 - 4, DARK_GREEN);
	edit_createPolygon(ENTITY, 8, 1.0, 3.0, 10.0, DARK_GREY);
	edit_createPolygon(AIRBOURNE, 8, 1.0, 10.0, 10.0, WHITE);
}

/*Controls*/
void readInput()
{
	if (gameState == GAMEPLAY)
	{
		physics_resistMovement(POLYGON, 0, LEFT_RIGHT, dpadSensitivity * 2);
		physics_resistMovement(POLYGON, 1, LEFT_RIGHT, dpadSensitivity * 2);

		if (input_isPressed('w'))
		{
			AI_jump(POLYGON, 0, 10.0);
		}

		if (input_isPressed('a'))
		{
			edit_change(POLYGON, 0, XVELOCITY, -1 * dpadSensitivity);
		}

		if (input_isPressed('s'))
		{
			;
		}

		if (input_isPressed('d'))
		{
			edit_change(POLYGON, 0, XVELOCITY, dpadSensitivity);
		}
	}
	else if (gameState == MENU)
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
			camera_keepZoomingBy(cameraScrollSpeed / 32);
		}

		if (input_isPressed('e'))
		{
			camera_keepZoomingBy(-cameraScrollSpeed / 32);
		}

		if (input_isPressed('x'))
		{
			camera_setTarget(edit_get(GAME, 0, XCENTRE), edit_get(GAME, 0, YCENTRE));
			camera_setViewportWidth(edit_get(GAME, 0, WIDTH));
		}
	}
}

void runGame()
{
	physics_limitBoundary();
	physics_detectPolygonCollision();
	physics_detectPlatformCollision();

	/*Insert Game Script code.*/
	physics_gravitate(POLYGON, 0, DOWN);
	physics_roll(POLYGON, 0);
	physics_gravitate(POLYGON, 1, DOWN);
	physics_roll(POLYGON, 1);

	//AI_avoid(POLYGON, 1, POLYGON, 0, 7.0);
	AI_fly(POLYGON, 1, 10.0);
}