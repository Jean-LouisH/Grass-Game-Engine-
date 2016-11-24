#include "..\Suprannua\Suprannua.h" //All the enums, structs and variables the framework and script needs to know.

///////////////////////////////////
//Custom code for Game Data, Logic, AI, Inputs
///////////////////////////////////

//Global variables
char gameTitle[64]          = SOFTWARE VERSION "[Stage 0, Snowland]";
double dpadSensitivity      = 30;
double cameraScrollSpeed    = 0.5;

Rect worldSizeMetres        = {200,60};

double platformGravity      = 50.0;

bool isGamePaused           = false;


void initGameData()
{
        int i;

        camera_setWidth(100);
        camera_setTarget(camera2D.viewport.width/2, camera2D.viewport.height/2);

        edit_create(BLOCK, BACKGROUND, 0, 0, worldSizeMetres.width - 0.01, worldSizeMetres.height - 0.01, worldSizeMetres.width/2,
                    worldSizeMetres.height/2, 135, 206, 250, 255);
        edit_create(BLOCK, PLATFORM, 0, 0, worldSizeMetres.width - 0.01, 3.0, worldSizeMetres.width/2, 1.6, 83, 21, 21, 255);
        polygon[0].properties.bouncePercentage = 0.3;
        edit_create(BLOCK, PLATFORM, 0, 0, worldSizeMetres.width - 0.01, 3.0, worldSizeMetres.width/2, 3, 255, 255, 255, 255);
        edit_createBlock(BACKGROUND, 52, 60, 4.5, 10, BLACK);
        edit_create(POLYGON, ENTITY, 6, 3.0, 0, 0, 5, 30, 255, 0, 0, 255);
        edit_createBlock(BACKGROUND, 49, 51, 0, 40, GREY);
        edit_createPolygon(BACKGROUND, 3, 8, 50, 40, BLACK);
        for(i = 2; i < 20; i++)
        {
            edit_create(POLYGON, ENTITY, 8, 0.5, 0, 0, 0, 0, 255, 255, 255, 255);
            edit_change(POLYGON, i, YVELOCITY, -5.0);
        }
        edit_createPolygon(ENTITY, 5, 10, 100, 1, PURPLE);
        edit_colourToAlpha(POLYGON, 20, 0.8);
        edit_createPolygon(ENTITY, 6, 3, 150, 5, BLACK);
        edit_colourToAlpha(POLYGON, 21, 0.9);
        edit_createPolygon(ENTITY, 6, 3, 150, 15, BLACK);
        edit_colourToAlpha(POLYGON, 22, 0.7);
        edit_createPolygon(ENTITY, 6, 3, 150, 22, BLACK);
        edit_colourToAlpha(POLYGON, 23, 0.5);
        edit_createPolygon(ENTITY, 6, 3, 150, 29, BLACK);
        edit_colourToAlpha(POLYGON, 24, 0.3);
        edit_createPolygon(ENTITY, 6, 3, 150, 36, BLACK);
        edit_colourToAlpha(POLYGON, 25, 0.1);

}

void runGameScript()
{
    int i;

    physics_limitBoundary();
    physics_detectPlatformCollision();
    physics_detectCollision();

    physics_gravitate(POLYGON, 0, DOWN);
    physics_roll(POLYGON, 0);
    AI_spin(POLYGON, 1, ANTICLOCKWISE, 180);
    AI_spin(POLYGON, 20, CLOCKWISE, 270);
    camera_follow(POLYGON, 0, true, false);
    //camera_limitTo(0, worldSizeMetres.width, 0, worldSizeMetres.height);

    for(i = 2; i < 20; i++)
        if(polygon[i].centre.yPosition < 6)
            edit_move(POLYGON, i, polygon[i].centre.xPosition, worldSizeMetres.height - 1);
}

//Controller
void readInput()
{
    int i;

    if(gameState == GAMEPLAY)
    {
        if(input_isPressed('w'))
        {
            for(i = 0; i < MAX_BLOCKS; i++)
            {
                if(logic_isOnPlatform(POLYGON, 0, i))
                    edit_change(POLYGON, 0, YVELOCITY, 40 + block[i].properties.yVelocity); //Jumping
            }
        }

        if(input_isPressed('a'))
            edit_change(POLYGON, 0, XVELOCITY, -1 * dpadSensitivity);
        else if(polygon[0].properties.xVelocity > 0)
                edit_adjust(POLYGON, 0, XVELOCITY, -3);

        if(input_isPressed('s'))
        {
            for(i = 0; i < MAX_BLOCKS; i++)
            {
                if(logic_isTouchingUnderPlatform(POLYGON, 0, i))
                    edit_change(POLYGON, 0, YVELOCITY, -40 + block[i].properties.yVelocity);
            }
        }

        if(input_isPressed('d'))
            edit_change(POLYGON, 0, XVELOCITY, dpadSensitivity);
        else if(polygon[0].properties.xVelocity < 0)
                edit_adjust(POLYGON, 0, XVELOCITY, 3);

    }
    else if (gameState == MENU)
    {
        ////////////////
        //Camera
        ////////////////
        if(input_isPressed('w'))
            camera_scroll(0.0, cameraScrollSpeed);

        if(input_isPressed('a'))
            camera_scroll(-1 * cameraScrollSpeed, 0.0);

        if(input_isPressed('s'))
            camera_scroll(0.0, - 1 * cameraScrollSpeed);

		if (input_isPressed('d'))
		{
			camera_scroll(cameraScrollSpeed, 0.0);
		}

        if(input_isPressed('q'))
            camera_keepZoomingBy(1);

        if(input_isPressed('e'))
            camera_keepZoomingBy(-1);
    }
}

