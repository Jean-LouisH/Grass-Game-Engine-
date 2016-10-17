#include "..\Suprannua\Definitions.h" //All the enums, structs and variables the framework and script needs to know.
#include "..\Suprannua\GameScript.h" //Script and asset functions.
#include "..\Suprannua\2DCamera.h" //Camera functions.
#include "..\Suprannua\AI.h" //Artificial Intelligence of agents.
#include "..\Suprannua\Compute.h" //All algorithms and physics calculations.
#include "..\Suprannua\Editor.h" //Functions used for data manipulation in game script.

///////////////////////////////////
//Custom code for Game Data, Logic, AI, Inputs
///////////////////////////////////

//Global variables
char gameTitle[64]          = SOFTWARE VERSION "[Stage 1, Grassland]";
double dpadSensitivity      = 30;
double cameraScrollSpeed    = 0.5;

Rect worldMap               = {100,80};

double friction             = 0.3;
double platformGravity      = 50.0;

bool gamePause              = false;

void initGameData()
{
        camera_resolution(worldMap.width);
        camera_target(camera2D.viewport.width/2, camera2D.viewport.height/2);

        edit_create(BOX, BACKGROUND, 0, 0, worldMap.width - 0.01, worldMap.height - 0.01,
                    worldMap.width/2, worldMap.height/2, 135, 206, 250);
        edit_create(BOX, PLATFORM, 0, 0, 60, 1.0, 30, 1.0, 0, 150, 0);
        edit_create(BOX, PLATFORM, 0, 0, 60, 1.0, 30, 0.505, 165, 42, 42);
        edit_create(POLYGON, ENTITY, 6, 3.0, 0, 0, 5, 30, 255, 0, 0);
        edit_create(POLYGON, ENTITY, 3, 2.0, 0, 0, 10, 40 + 5.0, 0, 200, 0);
        edit_create(BOX, PLATFORM, 0, 0, 10.0, 1.0, 10, 40, 255, 0, 0);
        edit_create(BOX, PLATFORM, 0, 0, 12.0, 1.0, 80, 10, 0, 0, 100);
        edit_create(BOX, PLATFORM, 0, 0, 6.0, 1.0, 95, 20, 0, 0, 100);
        edit_create(BOX, PLATFORM, 0, 0, 10.0, 1.0, 85, 32, 0, 0, 100);
        edit_create(BOX, PLATFORM, 0, 0, 6.0, 1.0, 46, 30, 0, 0, 100);
}

void runGameScript()
{
    compute_gravitate(POLYGON, 0);
    compute_gravitate(POLYGON, 1);
    compute_translate();
    compute_rotate();
    compute_limitBoundary();
    compute_detectPlatformCollision();
    compute_roll(POLYGON, 0);
    AI_spin(POLYGON, 1, ANTICLOCKWISE, 3);
    //camera_zoom(100);

    if(timeCount >= 3 && timeCount < 10 && camera2D.viewport.width > 15)
    {
        camera_target(polygon[1].centre.xPosition, polygon[1].centre.yPosition);
        camera_zoom(0.4);
    }
    if(timeCount > 10 && timeCount < 11)
        camera_resolution(100);
    if(timeCount >= 10 && timeCount < 15 && camera2D.viewport.width > 15)
    {
        camera_target(polygon[0].centre.xPosition, polygon[0].centre.yPosition);
        camera_zoom(0.6);
    }
    if(timeCount > 15 && timeCount < 16)
    {
        camera_resolution(worldMap.width);
        camera_target(camera2D.viewport.width/2, camera2D.viewport.height/2);

    }

    if(hypot(polygon[0].centre.xPosition - polygon[1].centre.xPosition,
        polygon[0].centre.yPosition - polygon[1].centre.yPosition) < polygon[1].radius)
    {
        edit_remove(POLYGON, 1);
        edit_colour(POLYGON, 0, 0, 225, 0);
    }
    if(frameCount % (int)(1000/FRAME_DELAY_MILLISECS * 1) == 0)
    {
        if(polygon[0].properties.colour[GREEN] > 0)
            edit_colour(BOX, 3, 0, 225, 0);
    }
    if(frameCount % (int)(1000/FRAME_DELAY_MILLISECS * 1) == 25)
    //
    {
        if(box[3].properties.colour[GREEN] > 0)
            edit_colour(BOX, 3, 255, 0, 0);
    }
    if(box[7].centre.yPosition <= 30)
        edit_adjust(BOX, 7, YVELOCITY, 5);
    if(box[7].centre.yPosition >= 45)
        edit_adjust(BOX, 7, YVELOCITY, -5);

    if(polygon[0].centre.yPosition < -5)
    {
        edit_move(POLYGON, 0, 5, 30);
        edit_change(POLYGON, 0, YVELOCITY, 0);
    }
    if(polygon[0].properties.colour[GREEN] > 0 && camera2D.viewport.width < 200)
    {
        camera_zoom(-0.1);
    }
}

//Controller
void readInput()
{
    if(!gamePause)
    {
        if (keyStates['w'] || keyStates['W'])
        {
            //Jumping
            for(i = 0; i < MAX_BOXES; i++)
            {
                if(box[i].properties.classification == PLATFORM)
                {
                    if(polygon[0].centre.yPosition - polygon[0].radius <=
                            box[i].centre.yPosition + (box[i].boxHeight / 2) &&
                        polygon[0].centre.yPosition - polygon[0].radius >
                            box[i].centre.yPosition - (box[i].boxHeight / 2))
                    {
                        if(polygon[0].centre.xPosition >
                                box[i].centre.xPosition - (box[i].boxWidth / 2) &&
                           polygon[0].centre.xPosition <
                                box[i].centre.xPosition + (box[i].boxWidth / 2))
                        {
                            edit_change(POLYGON, 0, YVELOCITY, 40 + box[i].properties.yVelocity);
                        }
                    }
                }
            }
        }

        if (keyStates['a'] || keyStates['A'])
            edit_change(POLYGON, 0, XVELOCITY, -1 * dpadSensitivity);

        if (keyStates['d'] || keyStates['D'])
            edit_change(POLYGON, 0, XVELOCITY, dpadSensitivity);

        ////////////////
        //Camera
        ////////////////
        if (keyStates['i'] || keyStates['I'])
            camera_scroll(0.0, cameraScrollSpeed);

        if (keyStates['j'] || keyStates['J'])
            camera_scroll(-1 * cameraScrollSpeed, 0.0);

        if (keyStates['k'] || keyStates['K'])
            camera_scroll(0.0, - 1 * cameraScrollSpeed);

        if (keyStates['l'] || keyStates['L'])
            camera_scroll(cameraScrollSpeed, 0.0);
    }

    /////////////
    //Game states
    /////////////

    if (keyStates[27])
        exit(EXIT_SUCCESS);

}


