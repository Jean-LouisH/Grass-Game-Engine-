#include "Suprannua\Definitions.h" //All the enums, structs and variables the framework and script needs to know.
#include "Suprannua\GameScript.h" //Script and asset functions.
#include "Suprannua\2DCamera.h" //Camera functions.
#include "Suprannua\AI.h" //Artificial Intelligence of agents.
#include "Suprannua\Compute.h" //All algorithms and physics calculations.
#include "Suprannua\Editor.h" //Functions used for data manipulation in game script.

//////////////////////////////////////////////////////////////////////
//Custom code for Game Data, Logic, AI, Inputs
//////////////////////////////////////////////////////////////////////

//Global variables
char gameTitle[64]          =  "";
double dpadSensitivity      = 30;
double cameraScrollSpeed    = 0.5;

Rect worldMap               = {100,100};

double friction             = 0.4;
double platformGravity      = 50.0;

bool isGamePaused              = false;


void initGameData()
{

}

void runGameScript()
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

        if (keyStates['s'] || keyStates['D'])
            ;

        if (keyStates['d'] || keyStates['D'])
            ;
    }
}

