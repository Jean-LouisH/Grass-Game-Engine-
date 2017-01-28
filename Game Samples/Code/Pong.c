#include "../../Suprannua Engine/SuprannuaEngine.h" 

/*Custom code for Initialisation, Scripting and Controls*/

/*Global variables*/

char gameTitle[64]			= "Pong";
Rect worldSizeMetres		= { 55,31 }; // m
double dpadSensitivity		= 50.0; // m/s
double cameraScrollSpeed	= 50.0; // m/s
double platformGravity		= 9.8; // m/s^2
double gravityConstant		= 6.674E-11; // m/s^2
bool isGamePaused			= false;

#define BALL_SPEED	30

void initGame()
{
	camera_setViewportWidth(edit_get(GAME, 0, WIDTH));
	camera_setTarget(edit_get(CAMERA, 0, XCENTRE), edit_get(CAMERA, 0, YCENTRE));
	edit_createRectangle(BACKGROUND, 0, edit_get(GAME, 0, WIDTH), 0, edit_get(GAME, 0, HEIGHT), GREY);

	/*Insert Game Initialisation code.*/

	/*Paddles and ball*/
	edit_createRectangle(PLATFORM, 5, 6, 5, 10, WHITE);
	edit_createRectangle(PLATFORM, edit_get(GAME, 0, WIDTH) - 6, edit_get(GAME, 0, WIDTH) - 5, 5, 10, WHITE);
	edit_createPolygon(ENTITY, 16, 0.5, edit_get(GAME, 0, XCENTRE), edit_get(GAME, 0, YCENTRE), WHITE);

	/*Initial ball velocity*/
	srand(time(NULL));
	edit_change(POLYGON, 0, BOUNCE, 1.0);
	edit_change(POLYGON, 0, XVELOCITY, (((rand() % 2) * 2) - 1) * BALL_SPEED);
	edit_change(POLYGON, 0, YVELOCITY, rand() % BALL_SPEED + (BALL_SPEED / 2));

	/*Text interface*/
	text_set(ENTITY, 10, edit_get(GAME, 0, HEIGHT) - 5, "", WHITE);
	text_set(ENTITY, edit_get(GAME, 0, WIDTH) - 10, edit_get(GAME, 0, HEIGHT) - 5, "", WHITE);
	text_set(ENTITY, edit_get(GAME, 0, XCENTRE) - 3.5, edit_get(GAME, 0, YCENTRE) + 12.5, "PONG IN SUPRANNUA", WHITE);
}

/*Controls*/
void readInput()
{
	if (gameState == GAMEPLAY)
	{
		edit_change(BLOCK, 1, YVELOCITY, 0);
		if (input_isPressed('w'))
			edit_change(BLOCK, 1, YVELOCITY, dpadSensitivity);

		if(input_isPressed('s'))
			edit_change(BLOCK, 1, YVELOCITY, -1 * dpadSensitivity);
	}
	else if (gameState == MENU)
	{
		;
	}
}

void runGame()
{
	physics_limitBoundary();
	//physics_detectPolygonCollision();
	physics_detectPlatformCollision();

	/*Insert Game Script code.*/

	double positionAngle;
	static int playerWins = 0;
	static int AIWins = 0;

	text_update(2, "HUMAN");
	text_data(2, playerWins);
	text_update(3, "AI");
	text_data(3, AIWins);

	srand(time(NULL));

	/*Moves text with players*/
	text_move(2, edit_get(BLOCK, 1, XPOSITION) - 5, edit_get(BLOCK, 1, YPOSITION));
	text_move(3, edit_get(BLOCK, 2, XPOSITION) + 1, edit_get(BLOCK, 2, YPOSITION));

	edit_change(BLOCK, 2, YVELOCITY, 0); //Keeps AI still when idle.

	/*AI logic to determine where to move as ball approaches*/
	positionAngle = atan2(polygon[0].centre.yPosition - block[2].centre.yPosition,
		polygon[0].centre.xPosition - block[2].centre.xPosition + block[2].dimensions.width);

	if (!event_hasPolygonPastXLocation(0, block[2].centre.xPosition + block[2].dimensions.width) &&
			polygon[0].properties.xVelocity > 0)
	{
		block[2].properties.yVelocity = dpadSensitivity * sin(positionAngle);
	}

	/*Wins and ball reset whenever the ball passes each side.*/
	if (polygon[0].centre.xPosition < block[1].centre.xPosition - (block[1].dimensions.width * 2))
	{
		AIWins++;
		edit_move(POLYGON, 0, edit_get(GAME, 0, XCENTRE), edit_get(GAME, 0, YCENTRE));
		edit_change(POLYGON, 0, XVELOCITY, (((rand() % 2) * 2) - 1) * BALL_SPEED);
		edit_change(POLYGON, 0, YVELOCITY, rand() % BALL_SPEED + (BALL_SPEED / 2));
	}
	else if (polygon[0].centre.xPosition > block[2].centre.xPosition + (block[2].dimensions.width * 2))
	{
		playerWins++;
		edit_move(POLYGON, 0, edit_get(GAME, 0, XCENTRE), edit_get(GAME, 0, YCENTRE));
		edit_change(POLYGON, 0, XVELOCITY, (((rand() % 2) * 2) - 1) * BALL_SPEED);
		edit_change(POLYGON, 0, YVELOCITY, rand() % BALL_SPEED + (BALL_SPEED / 2));
	}
}