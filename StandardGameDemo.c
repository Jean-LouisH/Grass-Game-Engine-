#include "SuprannuaEngine\SuprannuaEngine.h" 

/*Custom code for Initialisation, Scripting and Controls*/

/*Global variables*/

char gameTitle[64] = SOFTWARE VERSION" Standard Game Demo ";
Rect worldSizeMetres = { 200,50 }; // m
double dpadSensitivity = 10.0; // m/s
double cameraScrollSpeed = 50.0; // m/s
double platformGravity = 9.8; // m/s^2
double gravityConstant = 6.674E-11; // m/s^2

void initGameAssets()
{
	int i;
	double topSoilLevel = 1.0;

	int trees = 5;
	int treeLayer;
	double treeBase = 10;
	double treeWidth = 2;
	double treeSeparation = 10;
	double treeHeight = 7;

	camera_setViewportWidth(40);
	camera_setTarget(edit_get(CAMERA, 0, XCENTRE), edit_get(CAMERA, 0, YCENTRE));
	edit_createRectangle(BACKGROUND, 0, edit_get(GAME, 0, WIDTH), 0, edit_get(GAME, 0, HEIGHT), SKY_BLUE);

	/*Insert Game Initialisation code.*/
	edit_createRectangle(ENTITY, 0, 90, 0.0, topSoilLevel, BROWN);
	edit_createRectangle(PLATFORM, 0, 90, topSoilLevel, topSoilLevel + 0.25, DARK_GREEN);

	edit_createPolygon(ENTITY, 6, 1.0, 4.0, 10.0, RED); //Player
	edit_createPolygon(BACKGROUND, 6, 3.0, 5.0, 17.0, YELLOW); //Sun

	edit_createPolygon(BACKGROUND, 6, 5.0, 10.0, 0.1, DARK_GREEN);
	edit_colourFromRGBA(POLYGON, 2, 0, 90, 0, FULL);

	edit_createPolygon(BACKGROUND, 6, 20.0, 35.0, 0.1, DARK_GREEN);
	edit_colourFromRGBA(POLYGON, 3, 0, 90, 0, FULL);

	for (i = 0; i < trees; i++)
	{
		if (i % 2 == 0)
			treeLayer = BACKGROUND;
		else
			treeLayer = FOREGROUND;

		edit_createRectangle(treeLayer, treeBase + (i * treeSeparation),
			(treeBase + treeWidth) + (i * treeSeparation), topSoilLevel, topSoilLevel + treeHeight, BROWN);
		edit_createPolygon(treeLayer, 8, 5.0, ((treeBase + treeBase + treeWidth) / 2) + (i * treeSeparation), 
			topSoilLevel + treeHeight, DARK_GREEN);
	}

	edit_createRectangle(BACKGROUND, 60, 85, 0, 20, BROWN);
	edit_createRectangle(BACKGROUND, 60, 85, 20, 21, DARK_GREEN);
	edit_createRectangle(FOREGROUND, 65, 75, 1.25, 5, DARK_BROWN);
	edit_colourToAlpha(BLOCK, 10, 0.3);
	edit_createRectangle(PLATFORM, 65, 75, 5, 6, DARK_GREEN);
	edit_createRectangle(FOREGROUND, 76, 81, 1.25, 10, DARK_BROWN);
	edit_colourToAlpha(BLOCK, 12, 0.3);
	edit_createRectangle(PLATFORM, 76, 81, 10, 11, DARK_GREEN);

	edit_createRectangle(BACKGROUND, 90, 120, -20, 1, BLUE);
	edit_createRectangle(PLATFORM, 89, 90, -20, 0, BROWN);
	edit_createRectangle(PLATFORM, 90, 95, -20, -1, DARK_BROWN);
	edit_createRectangle(PLATFORM, 95, 100, -20, -7, DARK_BROWN);
	edit_createRectangle(PLATFORM, 100, 105, -20, -13, DARK_BROWN);
	edit_createRectangle(PLATFORM, 105, 120, -20, -13, DARK_BROWN);
	edit_createRectangle(FOREGROUND, 90, 120, -20, 1, BLUE);
	edit_colourToAlpha(BLOCK, 20, 0.5);
	edit_createRectangle(PLATFORM, 120, 121, -20, 1, BROWN);
	edit_createRectangle(PLATFORM, 120, edit_get(GAME, 0, WIDTH), 0.0, topSoilLevel, BROWN);
	edit_createRectangle(PLATFORM, 120, edit_get(GAME, 0, WIDTH), topSoilLevel, topSoilLevel + 0.25, DARK_GREEN);

	edit_createRectangle(BACKGROUND, 135, 150, 0, 15, BROWN);
	edit_createRectangle(BACKGROUND, 135, 150, 15, 16, DARK_GREEN);

	edit_createRectangle(BACKGROUND, 155, 175, 0, 10, BROWN);
	edit_createRectangle(BACKGROUND, 155, 175, 10, 11, DARK_GREEN);

	edit_createRectangle(PLATFORM, 155, 160, 1.25, 6, DARK_BROWN);
	edit_createRectangle(PLATFORM, 155, 160, 6, 6.25, DARK_GREEN);;
	edit_createRectangle(PLATFORM, 160, edit_get(GAME, 0, WIDTH), 1.25, 11, DARK_BROWN);
	edit_createRectangle(PLATFORM, 160, edit_get(GAME, 0, WIDTH), 11, 11.25, WHITE);

	edit_createRectangle(FOREGROUND, 149, 151, 1.25, 7.0, DARK_BROWN);
	edit_createPolygon(FOREGROUND, 8, 5.0, 150, 9, DARK_GREEN);

	edit_createPolygon(ENTITY, 6, 1.0, 4.0, -5.0, RED); //Player reflection
	edit_createRectangle(FOREGROUND, 0, 15, 0.0, 1.00, BROWN);
	edit_createRectangle(FOREGROUND, 19, 75, 0.0, 1.00, BROWN);
	edit_createRectangle(FOREGROUND, 15, 19, 0.0, 0.4, BROWN);
	edit_createRectangle(FOREGROUND, 15, 19, 0.4, 1.05, SKY_BLUE);
	edit_colourToAlpha(BLOCK, storedBlocks, 0.15);

	edit_createPolygon(ENTITY, 8, 5.0, 180, 15, WHITE);
	edit_change(POLYGON, storedPolygons, BOUNCE, 0.99);
	edit_change(POLYGON, storedPolygons, MASS, 10);

	edit_createRectangle(PLATFORM, -0.5, 0.0, 0.0, edit_get(GAME, 0, HEIGHT), SKY_BLUE);
	edit_createRectangle(PLATFORM, edit_get(GAME, 0, WIDTH), edit_get(GAME, 0, WIDTH) + 
		0.5, 0.0, edit_get(GAME, 0, HEIGHT), SKY_BLUE);

	edit_createRectangle(PLATFORM, 90.0, 100.0, 15.0, 16.0, VIOLET);
	edit_createRectangle(PLATFORM, 120.0, 130.0, 14.0, 15.0, MAGENTA);

	text_set(ENTITY, 5, 11 + 6,
		"The " SOFTWARE " Standard Game Template", WHITE);
	text_set(ENTITY, 5, 11 + 4,
		"Edit the game code 'Standard Game Demo.c' as you see fit.", WHITE);
	text_set(ENTITY, 5, 11 + 3,
		"Use the WASD keys to move the polygon, or 'p' for pausing and camera.", WHITE);
	text_set(HUD, -0.35, -0.1, "Test", WHITE);

	audio_set(SOUND, "../EngineAssets/Kabuki Yooo.ogg");
	audio_set(SOUND, "../EngineAssets/Freezing sfx.ogg");
	audio_set(MUSIC, "../EngineAssets/Bay Breeze - FortyThr33.ogg");
	audio_set(MUSIC, "../EngineAssets/Jingle Bells.ogg");
}

/*Controls*/
void readInput()
{
	if (gameState == GAMEPLAY)
	{
		text_update(5, "");
		physics_resistMovement(POLYGON, 0, LEFT_RIGHT, dpadSensitivity * 2);

		if (input_isPressed('w'))
		{
			AI_jump(POLYGON, 0, 10.0);
			AI_jump(POLYGON, storedPolygons - 1, 10.0);
		}

		if (input_isPressed('a'))
		{
			edit_change(POLYGON, 0, XVELOCITY, -1 * dpadSensitivity);
		}

		if (input_isDoublePressed('a', 98))
		{
			edit_change(POLYGON, 0, XVELOCITY, dpadSensitivity * -2);
		}

		if (input_isPressed('s'))
		{
			;
		}

		if (input_isPressed('d'))
		{
			edit_change(POLYGON, 0, XVELOCITY, dpadSensitivity);
		}

		if (input_isDoublePressed('d', 99))
		{
			edit_change(POLYGON, 0, XVELOCITY, dpadSensitivity * 2);
		}

		if (input_isPressed('g'))
		{
			edit_enableGrid(true);
			edit_enableKernelStats(true);
		}

		if (input_isPressed('h'))
		{
			edit_enableGrid(false);
			edit_enableKernelStats(false);
		}

		if (input_isPressed('i'))
		{
			if (event_isOnInstant(1))
				camera_invert(true, true);
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
			camera_setTarget(edit_get(POLYGON, 0, XPOSITION), 0);
			camera_setViewportWidth(40);
		}
	}
}

void runGameLogic()
{
	int i;

	//physics_limitBoundary();
	physics_detectPolygonCollision();
	physics_detectPlatformCollision();

	/*Insert Game Script code.*/
	physics_gravitate(POLYGON, 0, DOWN);
	physics_gravitate(POLYGON, storedPolygons, DOWN);
	physics_roll(POLYGON, 0);
	physics_roll(POLYGON, storedPolygons - 1);
	physics_roll(POLYGON, storedPolygons);

	if (edit_get(POLYGON, 0, YPOSITION) < 0)
	{
		if (event_isOnInstant(96))
			edit_change(POLYGON, 0, YVELOCITY, 0.0);
		camera_follow(POLYGON, 0, true, true);
	}
	else
	{
		camera_follow(POLYGON, 0, true, false);
		camera_limitTo(0, edit_get(GAME, 0, WIDTH), 0, edit_get(GAME, 0, HEIGHT));
	}

	if (edit_get(POLYGON, storedPolygons, YPOSITION) < 0)
	{
		if (event_isOnInstant(95))
			edit_change(POLYGON, storedPolygons, YVELOCITY, 0.0);
	}

	if (event_hasPolygonPastXLocation(0, 90) && !event_hasPolygonPastXLocation(0, 120) &&
		!event_hasPolygonPastYLocation(0, -0.1))
		edit_adjust(POLYGON, 0, YVELOCITY, 7.0);

	if (event_hasPolygonPastXLocation(storedPolygons, 90) &&
		!event_hasPolygonPastXLocation(storedPolygons, 120) &&
		!event_hasPolygonPastYLocation(storedPolygons, -0.1))
	{
		edit_adjust(POLYGON, storedPolygons, YVELOCITY, 5.0);
		edit_change(POLYGON, storedPolygons, BOUNCE, 0.1);
		edit_change(POLYGON, storedPolygons, MASS, 100);
	}


	edit_move(POLYGON, 1, edit_get(CAMERA, 0, XPOSITION) + 2.5, 18);

	AI_spin(POLYGON, 1, CLOCKWISE, sin(2 * PI * 0.435 * timeCount) * 180);

	for (i = 4; i < 9; i++)
	{
		AI_spin(POLYGON, i, ANTICLOCKWISE, sin(2 * PI * 0.435 * timeCount) * 30);
	}

	/*Sun animation timing*/
	if (timeCount < 18.375)
		edit_adjust(POLYGON, 1, RADIUS, sin(2 * PI * 0.871 * timeCount) * 4);
	else if (timeCount < 36.75)
		edit_adjust(POLYGON, 1, RADIUS, sin(2 * PI * 1.742 * timeCount) * 8);
	else if (timeCount > 46.856 && timeCount < 55.125)
		edit_adjust(POLYGON, 1, RADIUS, sin(2 * PI * 0.871 * timeCount) * 4);
	else if (timeCount > 56.043)
		edit_adjust(POLYGON, 1, RADIUS, sin(2 * PI * 1.742 * timeCount) * -8);

	if (event_hasPolygonPastXLocation(0, 3.0) && !event_hasPolygonPastXLocation(0, 70))
	{
		if (abs(edit_get(POLYGON, 0, XPOSITION) - edit_get(POLYGON, storedPolygons - 1, XPOSITION)) < 0.01)
			edit_change(POLYGON, storedPolygons - 1, XVELOCITY, edit_get(POLYGON, 0, XVELOCITY));
		else
			AI_travel(POLYGON, storedPolygons - 1, edit_get(POLYGON, 0, XPOSITION), -1.0, 3 * dpadSensitivity);
	}
	else
		AI_travel(POLYGON, storedPolygons - 1, 5.0, 0.0, 3 * dpadSensitivity);

	physics_gravitate(POLYGON, storedPolygons - 1, UP);

	if (!event_isPolygonHigher(0, 4) && event_isPolygonWithinRadius(0, 7.0, 4) || 
		!event_isPolygonHigher(0, 5) && event_isPolygonWithinRadius(0, 7.0, 5) ||
		!event_isPolygonHigher(0, 6) && event_isPolygonWithinRadius(0, 7.0, 6) || 
		!event_isPolygonHigher(0, 7) && event_isPolygonWithinRadius(0, 7.0, 7) || 
		!event_isPolygonHigher(0, 8) && event_isPolygonWithinRadius(0, 7.0, 8))
	{
		edit_colourFromRGBA(POLYGON, 0, 225, 0, 0, FULL);
		edit_colourFromRGBA(POLYGON, storedPolygons - 1, 225, 0, 0, FULL);
	}
	else
	{
		edit_colourFromRGBA(POLYGON, 0, FULL, 0, 0, FULL);
		edit_colourFromRGBA(POLYGON, storedPolygons - 1, FULL, 0, 0, FULL);
	}

	if (event_isOnInstant(2))
		audio_play(MUSIC, 0, INFINITE);

	edit_scrollPlatform(storedBlocks - 1, LEFT_RIGHT, 96, 115, 5.0);
	edit_scrollPlatform(storedBlocks, UP_DOWN, 13, 5, 5.0);
}