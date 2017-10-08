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
double engineTime;

bool isGamePaused = false;

unsigned char gameState = GAMEPLAY;
bool keyStates[128] = { false };

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

bool isEngineStatsEnabled = false;
bool isGridEnabled = false;

const unsigned char black[3] = { 0,0,0 };
const unsigned char white[3] = { 255,255,255 };
const unsigned char red[3] = { 255,0,0 };
const unsigned char green[3] = { 0,255,0 };
const unsigned char blue[3] = { 0,0,255 };
const unsigned char orange[3] = { 255,165,0 };
const unsigned char yellow[3] = { 255,255,0 };
const unsigned char violet[3] = { 191,5,247 };
const unsigned char purple[3] = { 128,0,128 };
const unsigned char brown[3] = { 150,75,0 };
const unsigned char skyBlue[3] = { 135,206,235 };
const unsigned char gold[3] = { 204,153,0 };
const unsigned char seaGreen[3] = { 46,139,87 };
const unsigned char pink[3] = { 255,192,203 };
const unsigned char grey[3] = { 128,128,128 };
const unsigned char darkRed[3] = { 192,0,0 };
const unsigned char darkGreen[3] = { 0,128,0 };
const unsigned char darkBlue[3] = { 0,0,128 };
const unsigned char darkBrown[3] = { 80,40,0 };
const unsigned char magenta[3] = { 255,0,228 };
const unsigned char darkGrey[3] = { 32,32,32 };

#undef main main //to reverse SDL's main definition

#ifdef _WIN32

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine,
	int cmdShow) //Win32 GUI based Application.
{
	initSDLAudio();

	int screenWidthPixels;
	int screenHeightPixels;
	char executableName[68];
	int argc = NULL;
	char **argv = NULL;

	glutInit(&argc, argv);

	screenWidthPixels = glutGet(GLUT_SCREEN_WIDTH) * 0.750;
	screenHeightPixels = (screenWidthPixels * 0.563);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(screenWidthPixels, screenHeightPixels);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - screenWidthPixels) / 2,
		((glutGet(GLUT_SCREEN_HEIGHT) - screenHeightPixels) / 2) - 20);
	glutCreateWindow(gameTitle);

	/*Assigns the resource icon to the executable of the same name as the game title.*/
	HWND hwnd = FindWindow(NULL, (gameTitle));
	sprintf(executableName, "%s.exe", gameTitle);
	HANDLE icon = LoadImage(GetModuleHandle((executableName)), MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, LR_COLOR);
	SendMessage(hwnd, (UINT)WM_SETICON, ICON_BIG, (LPARAM)icon);

	/*Run GLUT callback registration*/
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	glutReshapeFunc(resize);

	glutDisplayFunc(runGameLoop);
	glutTimerFunc(FRAME_TIME_MILLISECS, timer, FRAME_TIME_MILLISECS);
	glutMainLoop();
	return 0;
}

#else

/*For non-Windows platforms compatible with SDL and freeGLUT*/

int main(int argc, char **argv)
{
	initSDLAudio();

	int screenWidthPixels;
	int screenHeightPixels;

	glutInit(&argc, argv);

	screenWidthPixels = glutGet(GLUT_SCREEN_WIDTH) * 0.750;
	screenHeightPixels = (screenWidthPixels * 0.563);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(screenWidthPixels, screenHeightPixels);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - screenWidthPixels) / 2,
		((glutGet(GLUT_SCREEN_HEIGHT) - screenHeightPixels) / 2) - 20);
	glutCreateWindow(gameTitle);

	/*Run GLUT callback registration*/
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	glutReshapeFunc(resize);

	glutDisplayFunc(runGameLoop);
	glutTimerFunc(FRAME_TIME_MILLISECS, timer, FRAME_TIME_MILLISECS);
	glutMainLoop();
	return 0;
}

#endif