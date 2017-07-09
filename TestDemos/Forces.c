#include "../../SuprannuaEngine/SuprannuaEngine.h" 

/*Custom code for Initialisation, Scripting and Controls*/

/*Global variables*/

char gameTitle[64] = "[Test] Forces";
Rect worldSizeMetres = { 30, 30 }; // m
double dpadSensitivity = 10.0; // m/s
double cameraScrollSpeed = 50.0; // m/s
double platformGravity = 9.8; // m/s^2
double gravityConstant = 6.674E1; // m/s^2

void initGameAssets()
{
	int i;

	camera_setViewportHeight(edit_get(GAME, 0, HEIGHT));
	camera_setTarget(edit_get(GAME, 0, XCENTRE), edit_get(GAME, 0, YCENTRE));
	edit_createRectangle(BACKGROUND, 0, edit_get(GAME, 0, WIDTH), 0, edit_get(GAME, 0, HEIGHT), DARK_GREY);

	for (i = 0; i < 30; i++)
	{
		edit_createPolygon(FLOATING, 30, 1.0, 0, 0, WHITE);
		edit_change(POLYGON, i, BOUNCE, 0.80);
	}

	edit_enableKernelStats(true);
	edit_enableGrid(true);
}

/*Controls*/
void readInput()
{
	if (gameState == GAMEPLAY)
	{

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
	}
}

void runGameLogic()
{
	int i;
	int j;

	physics_limitBoundary();
	physics_detectPolygonCollision();
	physics_detectPlatformCollision();

	if (event_isOnCycle(5.0))
	{
		for (i = 0; i < 30; i++)
		{
			for (j = 0; j < 30; j++)
			{
				physics_force(POLYGON, i, TO, POLYGON, j);
			}
		}
	}
	else
	{
		for (i = 0; i < 30; i++)
		{
			for (j = 0; j < 30; j++)
			{
				physics_force(POLYGON, i, FROM, POLYGON, j);
			}
		}
	}
}