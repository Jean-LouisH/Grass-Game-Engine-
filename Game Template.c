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
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        //Temporary Test code for loading a simple polygon and box
        /////////////////////////////////////////////////////////////////////////////////////////////////////////

    	srand((unsigned)time(NULL));

        polygon[0].radius = 2.0;
        polygon[0].properties.mass = polygon[0].radius;
		polygon[0].centre.xPosition = rand() % (int)(xMapSize - (2 * polygon[0].radius)) + (polygon[0].radius);
		polygon[0].centre.yPosition = rand() % (int)(yMapSize - (2 * polygon[0].radius)) + (polygon[0].radius);
		//polygon[0].properties.xVelocity = rand() % OCTAGON_MAX_VELOCITY - (OCTAGON_MAX_VELOCITY / 2);
		//polygon[0].properties.yVelocity = rand() % OCTAGON_MAX_VELOCITY - (OCTAGON_MAX_VELOCITY / 2);
		polygon[0].properties.colour[RED] = 255;
		polygon[0].properties.colour[GREEN] = 255;
		polygon[0].properties.colour[BLUE] = 255;

		for (j = 0; j < MAX_POLYGON_SIDES; j++)
		{
			polygon[0].vertices[j].xPosition = polygon[0].centre.xPosition +
				(polygon[0].radius * cos(((360 / MAX_POLYGON_SIDES) * (j)) * (PI / 180)));
			polygon[0].vertices[j].yPosition = polygon[0].centre.yPosition +
				(polygon[0].radius * sin(((360 / MAX_POLYGON_SIDES) * (j)) * (PI / 180)));
		}


		//box[0].centre.xPosition = rand() % (int)(xMapSize - (2 * box[0].radius)) + (box[0].radius);
		//box[0].centre.yPosition = rand() % (int)(yMapSize - (2 * box[0].radius)) + (box[0].radius);
		//box[0].properties.xVelocity = rand() % OCTAGON_MAX_VELOCITY - (OCTAGON_MAX_VELOCITY / 2);
		//box[0].properties.yVelocity = rand() % OCTAGON_MAX_VELOCITY - (OCTAGON_MAX_VELOCITY / 2);
		box[0].properties.colour[RED] = 255;
		box[0].properties.colour[GREEN] = 255;
		box[0].properties.colour[BLUE] = 255;
		/////////////////////////////////////////////////////////////////////////////////////////////////////
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

