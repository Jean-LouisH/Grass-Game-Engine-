#include "Suprannua\Suprannua.h" 

//////////////////////////////////////////////////////////////////////
//Custom code for Game Data, Logic, AI, Inputs
//////////////////////////////////////////////////////////////////////

//Global variables
char gameTitle[64]          = SOFTWARE VERSION "[No Game Loaded.]";
double dpadSensitivity      = 30;
double cameraScrollSpeed    = 0.5;

Rect worldSizeMetres        = {100,100};

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

    if(gameState == GAMEPLAY)
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
    else if (gameState == MENU)
    {

    }

}

