#include "../SuprannuaEngine/SuprannuaEngine.h" 

/*Custom code for Initialisation, Scripting and Controls*/

/*Global variables*/

char gameTitle[64] = "[Test] Collision Detection";
Rect worldSizeMetres = { 30, 30 }; // m
double dpadSensitivity = 10.0; // m/s
double cameraScrollSpeed = 50.0; // m/s
double platformGravity = 9.8; // m/s^2
double gravityConstant = 6.674E-11; // m/s^2

void initGameAssets()
{
	int i;

	camera_setViewportHeight(edit_get(GAME, 0, HEIGHT));
	camera_setTarget(edit_get(GAME, 0, XCENTRE), edit_get(GAME, 0, YCENTRE));
	edit_createRectangle(BACKGROUND, 0, edit_get(GAME, 0, WIDTH), 0, edit_get(GAME, 0, HEIGHT), DARK_GREY);

	for (i = 0; i < 30; i++)
	{
		text_set(ENTITY, 0.0, 0.0, "Blank", GREEN);

		if (i == 0)
			edit_createPolygon(FLOATING, 30, 1.0, 0, 0, GREEN);
		else
			edit_createPolygon(FLOATING, 30, 1.0, 0, 0, WHITE);
		edit_change(POLYGON, i, BOUNCE, 0.99);
	}

	edit_enableEngineStats(true);
	edit_enableGrid(true);
}

/*Controls*/
void readInput()
{
	if (gameState == GAMEPLAY)
	{

		if (input_isPressed('w'))
		{
			edit_change(POLYGON, 0, YVELOCITY, dpadSensitivity);
		}

		if (input_isPressed('a'))
		{
			edit_change(POLYGON, 0, XVELOCITY, -1 * dpadSensitivity);
		}

		if (input_isPressed('s'))
		{
			edit_change(POLYGON, 0, YVELOCITY, -1 * dpadSensitivity);;
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
	}
}

void runGameLogic()
{
	int i = 3;

	physics_limitBoundary();
	physics_detectPolygonCollision();
	//physics_detectPlatformCollision();

	for (i = 2; i < 30 + 2; i++)
	{
		text_update(i, "");
		text_data(i, hypot(edit_get(POLYGON, i - 2, XVELOCITY), edit_get(POLYGON, i - 2, YVELOCITY)));
		text_append(i, "m/s");
		text_move(i, edit_get(POLYGON, i - 2, XPOSITION) - 0.75, edit_get(POLYGON, i - 2, YPOSITION) - 1.5);
	}
}