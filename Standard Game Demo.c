#include "Suprannua Engine\SuprannuaEngine.h" 

/*Custom code for Initialisation, Scripting and Controls*/

/*Global variables*/

char gameTitle[64] = SOFTWARE VERSION" Standard Game Demo ";
Rect worldSizeMetres = { 200,150 }; // m
double dpadSensitivity = 10.0; // m/s
double cameraScrollSpeed = 50.0; // m/s
double platformGravity = 9.8; // m/s^2
double gravityConstant = 6.674E-11; // m/s^2

void initGameAssets()
{
	int i;
	double topSoilLevel = 1.0;

	int trees = 8;
	int treeLayer;
	double treeBase = 10;
	double treeWidth = 2;
	double treeSeparation = 10;
	double treeHeight = 7;

	camera_setViewportWidth(40);
	camera_setTarget(edit_get(CAMERA, 0, XCENTRE), edit_get(CAMERA, 0, YCENTRE));
	edit_createRectangle(BACKGROUND, 0, edit_get(GAME, 0, WIDTH), 0, edit_get(GAME, 0, HEIGHT), SKY_BLUE);

	/*Insert Game Initialisation code.*/
	edit_createRectangle(PLATFORM, 0, edit_get(GAME, 0, WIDTH), 0.0, topSoilLevel, BROWN);
	edit_createRectangle(PLATFORM, 0, edit_get(GAME, 0, WIDTH), topSoilLevel, topSoilLevel + 0.25, DARK_GREEN);

	edit_createPolygon(ENTITY, 6, 1.0, 4.0, 10.0, RED); //Player
	edit_createPolygon(BACKGROUND, 6, 3.0, 5.0, 17.0, YELLOW); //Sun

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

	text_set(ENTITY, 5, 11 + 6,
		"The " SOFTWARE " Standard Game Template", WHITE);
	text_set(ENTITY, 5, 11 + 4,
		"Edit the game code 'Game.c' as you see fit.", WHITE);
	text_set(ENTITY, 5, 11 + 3,
		"Use the WASD keys to move the polygon, or 'p' for pausing and camera.", WHITE);
	text_set(HUD, -0.35, -0.1, "Test", WHITE);

	audio_set(SOUND, "../Engine Assets/Kabuki Yooo.ogg");
	audio_set(MUSIC, "../Engine Assets/Bay Breeze - FortyThr33.ogg");
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

	physics_limitBoundary();
	physics_detectPolygonCollision();
	physics_detectPlatformCollision();

	/*Insert Game Script code.*/
	physics_gravitate(POLYGON, 0, DOWN);
	physics_roll(POLYGON, 0);
	camera_follow(POLYGON, 0, true, false);
	camera_limitTo(0, edit_get(GAME, 0, WIDTH), 0, edit_get(GAME, 0, HEIGHT));

	edit_move(POLYGON, 1, edit_get(CAMERA, 0, XPOSITION) + 10, 18);

	AI_spin(POLYGON, 1, CLOCKWISE, sin(2 * PI * 0.435 * timeCount) * 180);

	for (i = 2; i < 10; i++)
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

	if (event_hasFalleninAHole(POLYGON, 0))
		edit_move(POLYGON, 0, 5.0, 10.0);

	if (event_isOnInstant(2))
		audio_play(MUSIC, 0, INFINITE);
}