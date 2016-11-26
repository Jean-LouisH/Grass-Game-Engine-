/**
 * Suprannua
 *
 * Description: A superannuated, 2D platformer, code reuse game engine developed in C and legacy OpenGL.
 *
 * Author:         Jean-Louis Haywood
 * Created:        01/09/2016
 */

#include "Suprannua.h"
#include <Windows.h>

int frameCount                          = 0;
double timeCount;
double framesPerSecond;
int passedFrames;
double startTime;
double currentTime;
double firstTimeSample;
double kernelTime;

unsigned char gameState                 = GAMEPLAY;
bool keyStates[256]						= {false};
bool specialKeyStates[21]				= {false};

HeadsUpDisplay textCache[MAX_TEXTS];
RegularPolygon polygon[MAX_POLYGONS]    = {0};
Block block[MAX_BLOCKS]                 = {0};
Camera camera2D;

int occupiedPolygons					= 0;
int occupiedBlocks						= 0;

unsigned char black[3]					= {0,0,0};
unsigned char white[3]					= {255,255,255};
unsigned char red[3]					= {255,0,0};
unsigned char green[3]					= {0,255,0};
unsigned char blue[3]					= {0,0,255};
unsigned char orange[3]					= {255,165,0};
unsigned char yellow[3]					= {255,255,0};
unsigned char violet[3]					= {191,5,247};
unsigned char purple[3]					= {128,0,128};
unsigned char brown[3]					= {150,75,0};
unsigned char skyBlue[3]				= {135,206,235};
unsigned char gold[3]					= {204,153,0};
unsigned char seaGreen[3]				= {46,139,87};
unsigned char pink[3]					= {255,192,203};
unsigned char grey[3]					= {128,128,128};


/*int main(int argc, char **argv)
{
    runGLUT(argc, argv);
    return 0;
}*/

int WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine,
	int cmdShow) //Win32 GUI based Application.
{
	runGLUT(NULL, NULL);
	return 0;
}
