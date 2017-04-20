#include "../../Suprannua Engine\SuprannuaEngine.h" 

/*Custom code for Initialisation, Scripting and Controls*/

/*Global variables*/

char gameTitle[64] = "Spinning Tops";
Rect worldSizeMetres = { 1,1 }; // m
double dpadSensitivity = 1.0; // m/s
double cameraScrollSpeed = 1.0; // m/s
double platformGravity = 9.8; // m/s^2
double gravityConstant = 1.5E-1; // m/s^2


void initGame()
{
	camera_setViewportHeight(edit_get(GAME, 0, HEIGHT));
	camera_setTarget(edit_get(GAME, 0, XCENTRE), edit_get(GAME, 0, YCENTRE));
	edit_createRectangle(BACKGROUND, 0, edit_get(GAME, 0, WIDTH), 0, edit_get(GAME, 0, HEIGHT), SEA_GREEN);

	/*Insert Game Initialisation code.*/
	edit_createPolygon(BACKGROUND, 32, edit_get(GAME, 0, WIDTH)/2, edit_get(GAME, 0, XCENTRE), edit_get(GAME, 0, YCENTRE), BLACK);
	edit_createPolygon(BACKGROUND, 16, 0.004, edit_get(GAME, 0, XCENTRE), edit_get(GAME, 0, YCENTRE), WHITE);
	edit_createPolygon(AIRBOURNE, 6, 0.05, edit_get(GAME, 0, XCENTRE),	edit_get(GAME, 0, HEIGHT) - 0.11, GREEN);
	edit_createPolygon(AIRBOURNE, 6, 0.05, edit_get(GAME, 0, XCENTRE), 0 + 0.11, RED);
	edit_createPolygon(AIRBOURNE, 6, 0.05, 0 + 0.11, edit_get(GAME, 0, YCENTRE), BLUE);
	edit_createPolygon(AIRBOURNE, 6, 0.05, edit_get(GAME, 0, WIDTH) - 0.11, edit_get(GAME, 0, YCENTRE), YELLOW);

	edit_change(POLYGON, 2, XVELOCITY, dpadSensitivity * 0.6);
	edit_change(POLYGON, 2, YVELOCITY, -(dpadSensitivity) * 0.6);
	edit_change(POLYGON, 2, BOUNCE, 1.0);

	edit_change(POLYGON, 3, XVELOCITY, -(dpadSensitivity) * 0.6);
	edit_change(POLYGON, 3, YVELOCITY, dpadSensitivity * 0.6);
	edit_change(POLYGON, 3, BOUNCE, 1.0);

	edit_change(POLYGON, 4, XVELOCITY, dpadSensitivity * 0.6);
	edit_change(POLYGON, 4, YVELOCITY, dpadSensitivity * 0.6);
	edit_change(POLYGON, 4, BOUNCE, 1.0);

	edit_change(POLYGON, 5, XVELOCITY, -(dpadSensitivity) * 0.6);
	edit_change(POLYGON, 5, YVELOCITY, -(dpadSensitivity) * 0.6);
	edit_change(POLYGON, 5, BOUNCE, 1.0);

	text_set(HUD, -1.0, 0.95, "", WHITE);
	text_set(HUD, -0.5, 0.95, "", WHITE);
	text_set(HUD, 0.0, 0.95, "WASD - move, P - pause. While paused: Q - Zoom out, E - Zoom in, X - Reset Camera", WHITE);
	text_set(HUD, -0.25, -0.98, "SPINNING TOPS", WHITE);
}

/*Controls*/
void readInput()
{
	int i; 
	static bool redReverseTransition;
	static bool greenReverseTransition;
	static bool blueReverseTransition;

	if (redReverseTransition)
		block[0].properties.colour[0] -= 2;
	else
		block[0].properties.colour[0] += 1;

	if (greenReverseTransition)
		block[0].properties.colour[1] -= 1;
	else
		block[0].properties.colour[1] += 1;

	if (blueReverseTransition)
		block[0].properties.colour[2] -= 1;
	else
		block[0].properties.colour[2] += 1;

	if (block[0].properties.colour[0] >= 254)
		redReverseTransition = true;
	else if (block[0].properties.colour[0] <= 1)
		redReverseTransition = false;
	if (block[0].properties.colour[1] >= 254)
		greenReverseTransition = true;
	else if (block[0].properties.colour[1] <= 1)
		greenReverseTransition = false;
	if (block[0].properties.colour[2] >= 254)
		blueReverseTransition = true;
	else if (block[0].properties.colour[2] <= 1)
		blueReverseTransition = false;

	if (gameState == GAMEPLAY)
	{
		text_update(5, "");

		for (i = 2; i <= storedPolygons; i++)
		{
			physics_resistMovement(POLYGON, i, LEFT_RIGHT, dpadSensitivity * 0.3);
			physics_resistMovement(POLYGON, i, UP_DOWN, dpadSensitivity * 0.3);
		}

		if (input_isPressed('w'))
		{
			edit_adjust(POLYGON, 2, YVELOCITY, dpadSensitivity);
		}

		if (input_isPressed('a'))
		{
			edit_adjust(POLYGON, 2, XVELOCITY, -1 * dpadSensitivity);
		}

		if (input_isPressed('s'))
		{
			edit_adjust(POLYGON, 2, YVELOCITY, -1 * dpadSensitivity);
		}

		if (input_isPressed('d'))
		{
			edit_adjust(POLYGON, 2, XVELOCITY, dpadSensitivity);
		}

	}
	else if (gameState == MENU)
	{
		text_update(5, "WASD - move, Q - Zoom out, E - Zoom in, X - Reset Camera");
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
	int i;
	int j;
	int target;
	double currentDistance;

	physics_limitBoundary();
	physics_detectPolygonCollision();
	//physics_detectPlatformCollision();

	/*Insert Game Script code.*/

	for (i = 2; i <= storedPolygons; i++)
	{
		AI_spin(POLYGON, i, ANTICLOCKWISE, 360 * 2);

		if (geometry_findDistance(POLYGON, i, POLYGON, 1) > edit_get(POLYGON, 0, RADIUS))
		{
			edit_change(POLYGON, i, XVELOCITY, dpadSensitivity * 0.6);
			edit_change(POLYGON, i, YVELOCITY, -(dpadSensitivity) * 0.6);
			edit_move(POLYGON, i, edit_get(POLYGON, 1, XPOSITION), edit_get(GAME, 0, HEIGHT) - 0.11);
		}
	}

	if (timeCount < 6.0)
	{

		/*AI following the nearest, smaller polygon.*/
		for (i = 2; i <= storedPolygons; i++)
		{

			edit_adjust(POLYGON, i, XVELOCITY, 0.6 * cos(geometry_findAngleBetween(POLYGON, i, POLYGON, 1)));
			edit_adjust(POLYGON, i, YVELOCITY, 0.6 * sin(geometry_findAngleBetween(POLYGON, i, POLYGON, 1)));

			if (polygon[i].properties.classification == AIRBOURNE)
			{
				for (j = 0; j <= storedPolygons; j++)
				{
					if (i != j && polygon[j].properties.classification != NOTHING)
					{
						;
					}
				}

				/*Movement AI to be added to Game Engine*/
				/*
				AI_travel(POLYGON,
					i,
					edit_get(POLYGON, target, XPOSITION),
					edit_get(POLYGON, target, YPOSITION),
					dpadSensitivity);

				lowestDistance = edit_get(GAME, 0, WIDTH);
				target = i;*/
			}
		}
	}
}