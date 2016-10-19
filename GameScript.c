#include "Suprannua\Definitions.h" //All the enums, structs and variables the framework and script needs to know.
#include "Suprannua\GameScript.h" //Script and asset functions.
#include "Suprannua\2DCamera.h" //Camera functions.
#include "Suprannua\AI.h" //Artificial Intelligence of agents.
#include "Suprannua\Input.h"
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

bool isGamePaused           = false;


void initGameData()
{

}

void runGameScript()
{

}

//Controller
void readInput()
{

 if(!isGamePaused)
    {
        if(input_isPressed('w'))
            ;

        if(input_isPressed('a'))
            ;

        if(input_isPressed('s'))
            ;

        if(input_isPressed('d'))
            ;
    }
}

