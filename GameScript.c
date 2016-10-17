#include "Suprannua\Definitions.h" //All the enums, structs and variables the framework and script needs to know.
#include "Suprannua\GameScript.h" //Script and asset functions.
#include "Suprannua\2DCamera.h" //Camera functions.
#include "Suprannua\AI.h" //Artificial Intelligence of agents.
#include "Suprannua\Compute.h" //All algorithms and physics calculations.
#include "Suprannua\Editor.h" //Functions used for data manipulation in game script.


///////////////////////////////////
//Custom code for Game Data, Logic, AI, Inputs
///////////////////////////////////

//Global variables
char gameTitle[64]          = SOFTWARE VERSION "[Alternation Test Script]";
double dpadSensitivity      = 30;
double cameraScrollSpeed    = 0.5;

Rect worldMap               = {100,100};

double friction             = 0.4;
double platformGravity      = 50.0;

bool gamePause              = false;


void initGameData()
{
    camera_target(worldMap.width / 2, worldMap.height / 2);
    camera_resolution(worldMap.width);

    edit_create(POLYGON, ENTITY, 5, 25.0, 0, 0, worldMap.width /2, worldMap.height / 2, 255, 255, 255);
}

void runGameScript()
{
    double maxRotation  = 3.0;
    double rotation     = 0.0;
    double duration     = 5.0;

    compute_rotate();

    rotation = maxRotation * sin((timeCount / duration) * (2 * PI));
    AI_spin(POLYGON, 0, CLOCKWISE, rotation);
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

    /////////////
    //Game states
    /////////////

    if (keyStates[27])
        exit(EXIT_SUCCESS);

}

