#include "../../Suprannua Engine/SuprannuaEngine.h" 

/*The aim is to collect as many smaller polygons until you burst to gain win points. If you are
eaten, your losses are also scored. */

/*Global variables*/

char gameTitle[64] = "Agar.io in Suprannua";
Rect worldSizeMetres = { 100,100 }; // m
double dpadSensitivity = 17.5; // m/s
double cameraScrollSpeed = 50.0; // m/s
double platformGravity = 9.8; // m/s^2
double gravityConstant = 6.674E-11; // m/s^2

void initGame()
{
	int i;
	int randomColour = 2;

	srand(time(NULL));

	camera_setViewportWidth(60.0);
	camera_setTarget(edit_get(CAMERA, 0, XCENTRE), edit_get(CAMERA, 0, YCENTRE));
	edit_createRectangle(BACKGROUND, 0, edit_get(GAME, 0, WIDTH), 0, edit_get(GAME, 0, HEIGHT), DARK_GREY);

	/*Insert Game Initialisation code.*/

	edit_createPolygon(AIRBOURNE, 12, 2.0, edit_get(GAME, 0, XCENTRE) + 4, edit_get(GAME, 0, YCENTRE) + 4, DARK_GREEN);

	for (i = 1; i <= 10; i++)
		edit_createPolygon(AIRBOURNE, 12, 2.0, 0, 0, RED);

	for (i = 11; i <= 15; i++)
	{
		randomColour = rand() % 20;
		if (randomColour == 4 || randomColour == 0 || randomColour == 17 || randomColour == 3)
			randomColour = 5;

		edit_createPolygon(BACKGROUND, 16, 0.5, 0, 0, randomColour);
	}

	text_set(ENTITY, edit_get(GAME, 0, XCENTRE), edit_get(GAME, 0, YCENTRE), "AGAR.IO IN SUPRANNUA", WHITE);
	text_set(HUD, -1.0, 0.95, "", WHITE);
	text_set(HUD, -0.5, 0.95, "", WHITE);
	text_set(HUD, 0.0, 0.95, "WASD - move, P - pause. While paused: Q - Zoom out, E - Zoom in, X - Reset Camera", WHITE);
	text_set(HUD, -0.25, -0.98, "Score wins by absorbing polygons until you burst.", WHITE);
	text_set(HUD, -1.0, -0.98, "G - grey background, B - black background", WHITE);
}

/*Controls*/
void readInput()
{
	int i;

	if (gameState == GAMEPLAY)
	{
		/*physics_resistRolling to be updated for general motion on screen in Game Engine*/
		for (i = 0; i <= storedPolygons; i++)
		{
			physics_resistMovement(POLYGON, i, LEFT_RIGHT, dpadSensitivity * 2);
			physics_resistMovement(POLYGON, i, UP_DOWN, dpadSensitivity * 2);
		}

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
			edit_change(POLYGON, 0, YVELOCITY, -1 * dpadSensitivity);
		}

		if (input_isPressed('d'))
		{
			edit_change(POLYGON, 0, XVELOCITY, dpadSensitivity);
		}

		if (input_isPressed('g'))
		{
			edit_colourBlock(0, GREY);
		}

		if (input_isPressed('b'))
		{
			edit_colourBlock(0, DARK_GREY);
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
			//camera_setTarget(edit_get(GAME, 0, XCENTRE), edit_get(GAME, 0, YCENTRE));
			camera_setViewportWidth(60.0);
		}
	}
}

void runGame()
{
	int i;
	int j;
	double lowestDistance = edit_get(GAME, 0, WIDTH);
	double currentDistance;
	int target = 0;
	double positionAngle;
	double motion;
	static int wins = 0;
	static int losses = 0;
	int randomColour = 2;

	srand(time(NULL));

	physics_limitBoundary();
	//physics_detectPolygonCollision();
	//physics_detectPlatformCollision();

	/*Insert Game Script code.*/

	//locks the camera to the last position of the player.
	if (edit_get(POLYGON, 0, XPOSITION) != 0 || edit_get(POLYGON, 0, YPOSITION) != 0)
		camera_follow(POLYGON, 0, true, true);

	text_update(3, "WINS");
	text_data(3, wins);
	text_update(4, "LOSSES");
	text_data(4, losses);


	/*AI following the nearest, smaller polygon.*/
	for (i = 1; i <= storedPolygons; i++)
	{
		if (polygon[i].properties.classification == AIRBOURNE)
		{
			for (j = 0; j <= storedPolygons; j++)
			{
				if (i != j && polygon[j].properties.classification != NOTHING)
				{
					currentDistance = geometry_findDistance(POLYGON, i, POLYGON, j);
					if ((currentDistance < lowestDistance) && (edit_get(POLYGON, j, RADIUS) < edit_get(POLYGON, i, RADIUS)))
					{
						lowestDistance = currentDistance;
						target = j;
					}
				}
			}

			/*Movement AI to be added to Game Engine*/

			AI_travel(POLYGON,
				i,
				edit_get(POLYGON, target, XPOSITION),
				edit_get(POLYGON, target, YPOSITION),
				dpadSensitivity);

			lowestDistance = edit_get(GAME, 0, WIDTH);
			target = i;
		}
	}

	/*Expands winning polygon and destroys losing polygon*/
	for (i = 0; i <= storedPolygons; i++)
	{
		if (polygon[i].properties.classification == AIRBOURNE)
		{
			for (j = 0; j <= storedPolygons; j++)
			{
				if (event_arePolygonsTouching(i, j) && (edit_get(POLYGON, j, RADIUS) < edit_get(POLYGON, i, RADIUS)))
				{
					polygon[i].radius = sqrt(((pow(polygon[i].radius, 2) * 2 * PI) + (pow(polygon[j].radius, 2) * 2 * PI)) / (2 * PI));
					edit_remove(POLYGON, j);
					if (j == 0)
						losses++;
				}
			}
		}
	}

	/*Generates polygons every 1 seconds. Event to be added to Game Engine*/
	if (frameCount % (60 * 1) == (60 * 1 - 1))
	{
		for (i = 0; i < 30; i++)
		{
			randomColour = rand() % 20;
			if (randomColour == 4 || randomColour == 0 || randomColour == 17 || randomColour == 3)
				randomColour = 5;

			edit_createPolygon(BACKGROUND, 16, 0.5, 0, 0, randomColour);
		}
	}

	/*Converts tiny polygons in player memory slots into players*/
	for (i = 0; i <= 10; i++)
	{
		if (polygon[i].radius < 0.6 && polygon[i].properties.classification != NOTHING)
		{
			polygon[i].properties.classification = AIRBOURNE;
			edit_change(POLYGON, i, RADIUS, 2.0);
			if (i == 0)
				edit_colourPolygon(i, DARK_GREEN);
			else
				edit_colourPolygon(i, RED);
		}

		/*When a player achieves the radius size, they burst*/
		if (polygon[i].radius > 10)
		{
			for (j = 0; j < (10 * 2); j++)
			{
				randomColour = rand() % 20;
				if (randomColour == 4 || randomColour == 0 || randomColour == 17 || randomColour == 3)
					randomColour = 5;

				edit_createPolygon(BACKGROUND, 12, 0.5, polygon[i].centre.xPosition + (j * 0.5),
					polygon[i].centre.yPosition - (j * 0.5), randomColour);
			}
			if (i == 0)
				wins++;
			edit_remove(POLYGON, i);
		}
	}
}