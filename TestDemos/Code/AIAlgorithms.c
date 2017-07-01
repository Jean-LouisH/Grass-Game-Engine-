#include "../../SuprannuaEngine/SuprannuaEngine.h" 

/*Custom code for Initialisation, Scripting and Controls*/

/*Global variables*/

char gameTitle[64] = "[Test] AI Algorithms";
Rect worldSizeMetres = { 140,25 }; // m
double dpadSensitivity = 10.0; // m/s
double cameraScrollSpeed = 50.0; // m/s
double platformGravity = 9.8; // m/s^2
double gravityConstant = 6.674E-11; // m/s^2

void initGameAssets()
{
	camera_setViewportWidth(40);
	camera_setTarget(edit_get(CAMERA, 0, XCENTRE), edit_get(CAMERA, 0, YCENTRE));
	edit_createRectangle(BACKGROUND, 0, edit_get(GAME, 0, WIDTH), 0, edit_get(GAME, 0, HEIGHT), DARK_GREY);

	edit_createRectangle(PLATFORM, 0 + (20 * 0), 20 + (20 * 0), 0, 1, RED);
	edit_createRectangle(PLATFORM, 0 + (20 * 1), 20 + (20 * 1), 0, 1, ORANGE);
	edit_createRectangle(PLATFORM, 0 + (20 * 2), 20 + (20 * 2), 0, 1, YELLOW);
	edit_createRectangle(PLATFORM, 0 + (20 * 3), 20 + (20 * 3), 0, 1, GREEN);
	edit_createRectangle(PLATFORM, 0 + (20 * 4), 20 + (20 * 4), 0, 1, SKY_BLUE);
	edit_createRectangle(PLATFORM, 0 + (20 * 5), 20 + (20 * 5), 0, 1, BLUE);
	edit_createRectangle(PLATFORM, 0 + (20 * 6), 20 + (20 * 6), 0, 1, VIOLET);

	text_set(ENTITY, 10 + (20 * 0), 13.25, "AVOID", WHITE);
	text_set(ENTITY, 10 + (20 * 1), 13.25, "FOLLOW", WHITE);
	text_set(ENTITY, 10 + (20 * 2), 13.25, "JUMP", WHITE);
	text_set(ENTITY, 10 + (20 * 3), 13.25, "FLY", WHITE);
	text_set(ENTITY, 10 + (20 * 4), 13.25, "CATCH", WHITE);
	text_set(ENTITY, 10 + (20 * 5), 13.25, "SHOOT", WHITE);
	text_set(ENTITY, 10 + (20 * 6), 13.25, "MIMIC", WHITE);

	edit_createPolygon(ENTITY, 7, 1.25, 2.0, 5.0, WHITE);

	edit_createPolygon(ENTITY, 6, 1.25, 10 + (20 * 0), 5.0, RED);
	edit_createPolygon(ENTITY, 6, 1.25, 10 + (20 * 1), 5.0, ORANGE);
	edit_createPolygon(ENTITY, 6, 1.25, 10 + (20 * 2), 5.0, YELLOW);
	edit_createPolygon(FLOATING, 6, 1.25, 10 + (20 * 3), 5.0, GREEN);
	edit_createPolygon(ENTITY, 6, 1.25, 10 + (20 * 4), 5.0, SKY_BLUE);
	edit_createPolygon(ENTITY, 6, 1.25, 10 + (20 * 5), 5.0, BLUE);
	edit_createPolygon(ENTITY, 6, 1.25, 10 + (20 * 6), 5.0, VIOLET);

	edit_enableKernelStats(true);
	edit_enableGrid(true);
}

/*Controls*/
void readInput()
{
	if (gameState == GAMEPLAY)
	{

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

	for (i = 0; i < 8; i++)
	{
		physics_resistMovement(POLYGON, i, LEFT_RIGHT, dpadSensitivity * 2);
		physics_gravitate(POLYGON, i, DOWN);
		physics_roll(POLYGON, i);
	}

	camera_follow(POLYGON, 0, true, false);
	camera_limitTo(0, edit_get(GAME, 0, WIDTH), 0, edit_get(GAME, 0, HEIGHT));

	if (event_hasPolygonPastXLocation(0, 0 + (20 * 0)) && !event_hasPolygonPastXLocation(0, 20 + (20 * 0))
		&& event_hasPolygonPastXLocation(1, 0 + (20 * 0)) && !event_hasPolygonPastXLocation(1, 20 + (20 * 0)))
		AI_avoid(POLYGON, 1, POLYGON, 0, 5);
	else
		AI_travel(POLYGON, 1, 10 + (20 * 0), 2, dpadSensitivity);
	if (event_hasPolygonPastXLocation(0, 0 + (20 * 1)) && !event_hasPolygonPastXLocation(0, 20 + (20 * 1))
		&& event_hasPolygonPastXLocation(2, 0 + (20 * 1)) && !event_hasPolygonPastXLocation(2, 20 + (20 * 1)))
		AI_follow(POLYGON, 2, POLYGON, 0, 10, 1);
	else
		AI_travel(POLYGON, 2, 10 + (20 * 1), 2, dpadSensitivity);
	if (event_hasPolygonPastXLocation(0, 0 + (20 * 2)) && !event_hasPolygonPastXLocation(0, 20 + (20 * 2))
		&& event_hasPolygonPastXLocation(3, 0 + (20 * 2)) && !event_hasPolygonPastXLocation(3, 20 + (20 * 2)))
		AI_jump(POLYGON, 3, 10);
	else
		AI_travel(POLYGON, 3, 10 + (20 * 2), 2, dpadSensitivity);
	if (event_hasPolygonPastXLocation(0, 0 + (20 * 3)) && !event_hasPolygonPastXLocation(0, 20 + (20 * 3))
		&& event_hasPolygonPastXLocation(4, 0 + (20 * 3)) && !event_hasPolygonPastXLocation(4, 20 + (20 * 3)))
		AI_fly(POLYGON, 4, 10);
	else
		AI_travel(POLYGON, 4, 10 + (20 * 3), 2, dpadSensitivity);
	if (event_hasPolygonPastXLocation(0, 0 + (20 * 4)) && !event_hasPolygonPastXLocation(0, 20 + (20 * 4))
		&& event_hasPolygonPastXLocation(5, 0 + (20 * 4)) && !event_hasPolygonPastXLocation(5, 20 + (20 * 4)))
		AI_catch(POLYGON, 5, POLYGON, 0, false, true);
	else
		AI_travel(POLYGON, 5, 10 + (20 * 4), 2, dpadSensitivity);
	if (event_hasPolygonPastXLocation(0, 0 + (20 * 5)) && !event_hasPolygonPastXLocation(0, 20 + (20 * 5))
		&& event_hasPolygonPastXLocation(6, 0 + (20 * 5)) && !event_hasPolygonPastXLocation(6, 20 + (20 * 5)))
		if(event_isOnCycle(0.3))
			AI_shoot(POLYGON, 6, POLYGON, 0, 40.0);
	else
		AI_travel(POLYGON, 6, 10 + (20 * 5), 2, dpadSensitivity);
	if (event_hasPolygonPastXLocation(0, 0 + (20 * 6)) && !event_hasPolygonPastXLocation(0, 20 + (20 * 6))
		&& event_hasPolygonPastXLocation(7, 0 + (20 * 6)) && !event_hasPolygonPastXLocation(7, 20 + (20 * 6)))
		AI_mimic(POLYGON, 7, POLYGON, 0);
	else
		AI_travel(POLYGON, 7, 10 + (20 * 6), 2, dpadSensitivity);
}