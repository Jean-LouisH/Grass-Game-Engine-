/**
 * Suprannua Engine
 *
 * Description: The Suprannua Engine is a superannuated, 2D platformer game engine codebase. Just For Fun.
 *
 * Author:         Jean-Louis Haywood
 * Created:        1st September 2016
 */

#include "SuprannuaEngine.h"

unsigned int frameCount = 0;
double timeCount;
double framesPerSecond;
int passedFrames;
double startTime;
double currentTime;
double firstTimeSample;
double kernelTime;

unsigned char gameState = GAMEPLAY;
bool keyStates[128] = { false };
bool specialKeyStates[128] = { false };

Text textCache[MAX_TEXTS];
RegularPolygon polygon[MAX_POLYGONS] = { 0 };
Block block[MAX_BLOCKS] = { 0 };
Camera camera2D;

int storedPolygons = 0;
int storedBlocks = 0;
int storedTexts = 0;

RenderingLayer backgrounds[MAX_DEFAULT_OBJECTS] = { 0 };
RenderingLayer platforms[MAX_DEFAULT_OBJECTS] = { 0 };
RenderingLayer entities[MAX_DEFAULT_OBJECTS] = { 0 };
RenderingLayer foregrounds[MAX_DEFAULT_OBJECTS] = { 0 };

int storedBackgrounds = 0;
int storedPlatforms = 0;
int storedEntities = 0;
int storedForegrounds = 0;

bool isKernelStatsEnabled = false;
bool isGridEnabled = false;
bool isGamePaused = false;

unsigned char black[3] = { 0,0,0 };
unsigned char white[3] = { 255,255,255 };
unsigned char red[3] = { 255,0,0 };
unsigned char green[3] = { 0,255,0 };
unsigned char blue[3] = { 0,0,255 };
unsigned char orange[3] = { 255,165,0 };
unsigned char yellow[3] = { 255,255,0 };
unsigned char violet[3] = { 191,5,247 };
unsigned char purple[3] = { 128,0,128 };
unsigned char brown[3] = { 150,75,0 };
unsigned char skyBlue[3] = { 135,206,235 };
unsigned char gold[3] = { 204,153,0 };
unsigned char seaGreen[3] = { 46,139,87 };
unsigned char pink[3] = { 255,192,203 };
unsigned char grey[3] = { 128,128,128 };
unsigned char darkRed[3] = { 192,0,0 };
unsigned char darkGreen[3] = { 0,128,0 };
unsigned char darkBlue[3] = { 0,0,128 };
unsigned char darkBrown[3] = { 80,40,0 };
unsigned char magenta[3] = { 255,0,228 };
unsigned char darkGrey[3] = { 32,32,32 };

#undef main main //to reverse SDL's main definition

/*For non-Windows platforms compatible with SDL and freeGLUT*/
/*
int main(int argc, char **argv)
{
	initSDLAudio();
	runGLUT(argc, argv);
	return 0;
}*/

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine,
	int cmdShow) //Win32 GUI based Application.
{
	initSDLAudio();
	runGLUT(NULL, NULL);
	return 0;
}