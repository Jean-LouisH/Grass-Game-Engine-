#include "GrassRoots_Framework.h"

///////////////////////////////////
//Custom code for Game Data, Logic, AI, Inputs
///////////////////////////////////

//Global vairables
char keyStates[256];
char gameTitle[64]          = "GrassRoots Framework";
int screenWidth             = 800;
int screenHeight            = 600;
double dpadSensitivity      = 0.5;
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
        grass_create(POLYGON, ENTITY, 3.0, 0, 0, 0, 0, 255, 255, 255);
        grass_create(BOX, ENTITY, 0, 6.0, 4.0, 0, 0, 255, 255, 255);
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
            ;

        if (keyStates['a'] || keyStates['A'])
            ;

        if (keyStates['s'] || keyStates['S'])
            ;

        if (keyStates['d'] || keyStates['D'])
            ;
        //Rotation
        if (keyStates['q'] || keyStates['Q'])
            ;

        if (keyStates['e'] || keyStates['E'])
            ;

        ////////////////
        //2P movement
        ////////////////
        if (keyStates['i'] || keyStates['I'])
            ;

        if (keyStates['j'] || keyStates['J'])
            ;

        if (keyStates['k'] || keyStates['K'])
            ;

        if (keyStates['l'] || keyStates['L'])
            ;

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

