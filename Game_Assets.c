#include "Framework Src\GrassRoots_Framework.h"
/*
///////////////////////////////////
//Custom code for Game Data, Logic, AI, Inputs
///////////////////////////////////

//Global variables
char keyStates[256];
char gameTitle[64]          = "";
int screenWidth             = 600;
int screenHeight            = 600;
double dpadSensitivity      = 30;
double cameraScrollSpeed    = 0.5;
double xMapSize             = 50;
double yMapSize             = 50;
bool gamePause              = false;

double friction             = 0.0;
double objectGravity        = 0.0;
double platformGravity      = 0.0;
double pointGravity[8];

void runGameScript()
{

}

void initGameData()
{

}

//Controller
void readInput()
{
    if(!gamePause)
    {
        if (keyStates['w'] || keyStates['W'])
            ;

        if (keyStates['a'] || keyStates['A'])
            ;

        if (keyStates['s'] || keyStates['S'])
            ;

        if (keyStates['d'] || keyStates['D'])
            ;
    }

    if (keyStates[27])
        exit(EXIT_SUCCESS);
}
*/
