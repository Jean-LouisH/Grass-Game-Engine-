#include "Framework Src\GrassRoots_Framework.h"

///////////////////////////////////
//Custom code for Game Data, Logic, AI, Inputs
///////////////////////////////////

//Global variables
char keyStates[256];
char gameTitle[64]          = "GrassRoots Framework";
int screenWidth             = 600;
int screenHeight            = 600;
double dpadSensitivity      = 30;
double cameraScrollSpeed    = 0.5;
double xMapSize             = 100;
double yMapSize             = 60;
bool gamePause              = false;

double friction             = 0.7;
double objectGravity        = 0.0;
double platformGravity      = 0.98;
double pointGravity[8];

void runGameScript()
{
    compute_gravitate(POLYGON, 0);
    compute_gravitate(POLYGON, 1);
    translatePosition();
    translateRotation();
    compute_detectPlatformCollision();
    compute_roll(POLYGON, 0);
    AI_spin(POLYGON, 1, ANTICLOCKWISE, 3);
    if(polygon[0].centre.xPosition > camera2D.target.xPosition)
        if(camera2D.target.xPosition < (xMapSize - 25))
            compute_scrollCamera(cameraScrollSpeed, 0);
    if(polygon[0].centre.xPosition < camera2D.target.xPosition - 5)
        if(camera2D.target.xPosition > 25)
            compute_scrollCamera(-1 * cameraScrollSpeed, 0 );
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
    {
        if(box[3].properties.colour[GREEN] > 0)
            edit_colour(BOX, 3, 255, 0, 0);
    }
    if(box[7].centre.yPosition <= 30)
        box[7].properties.yVelocity += 5;
    if(box[7].centre.yPosition >= 45)
        box[7].properties.yVelocity -= 5;
    if(polygon[0].centre.yPosition < -5)
        exit(EXIT_SUCCESS);
}

void initGameData()
{
        edit_camera(25, yMapSize/2);
        edit_create(BOX, BACKGROUND, 0, 0, xMapSize - 0.01, yMapSize - 0.01, xMapSize/2, yMapSize/2, 135, 206, 250);
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

//Controller
void readInput()
{
    //////////////
    //1P movement
    //////////////
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
                            //if(polygon[0].centre.yPosition - polygon[0].radius < 1)
                            polygon[0].properties.yVelocity = 40;
                        }
                    }
                }
            }
        }

        if (keyStates['a'] || keyStates['A'])
            polygon[0].properties.xVelocity = -1 * dpadSensitivity;;

        if (keyStates['s'] || keyStates['S'])
            ;

        if (keyStates['d'] || keyStates['D'])
            polygon[0].properties.xVelocity = dpadSensitivity;;
        //Rotation
        if (keyStates['q'] || keyStates['Q'])
            ;

        if (keyStates['e'] || keyStates['E'])
            ;

        ////////////////
        //2P movement
        ////////////////
        if (keyStates['i'] || keyStates['I'])
            compute_scrollCamera(0.0, cameraScrollSpeed);

        if (keyStates['j'] || keyStates['J'])
            compute_scrollCamera(-1 * cameraScrollSpeed, 0.0);

        if (keyStates['k'] || keyStates['K'])
            compute_scrollCamera(0.0, - 1 * cameraScrollSpeed);

        if (keyStates['l'] || keyStates['L'])
            compute_scrollCamera(cameraScrollSpeed, 0.0);

        //Rotation
        if (keyStates['u'] || keyStates['U'])
            ;

        if (keyStates['o'] || keyStates['O'])
            ;
    }

    /////////////
    //Game states
    /////////////

    if (keyStates[27])
        exit(EXIT_SUCCESS);

}

