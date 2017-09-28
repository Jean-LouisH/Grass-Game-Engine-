/**
 * FreeGLUT_Access
 *
 * Author: Jean-Louis Haywood
 *
 * Defines all the freeglut functions to handle the OpenGL window context, timing and inputs.
 */

#pragma once

void keyPressed(unsigned char key, int x, int y);	//During key press.
void keyUp(unsigned char key, int x, int y);		//After key press.
void resize(int width, int height);					//Maintains the window size.
void timer(int milliseconds);						//For frame rate.
