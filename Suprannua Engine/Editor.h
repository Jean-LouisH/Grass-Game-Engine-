/**
 * Editor
 *
 * Author: Jean-Louis Haywood
 *
 * Directly reads or writes the data of polygons and blocks to organise scenes from initialisation or in response to scripted events.
 */

#pragma once

void edit_adjust(	unsigned char object,
					int objectNumber,
					unsigned char attribute,
					double amount);

void edit_change(	unsigned char object,
					int objectNumber,
					unsigned char attribute, // from Suprannua.h "attributes" enum
					double amount);

void edit_colourBlock(int objectNumber, unsigned char colour);

void edit_colourFromRGBA(unsigned char object,
						int objectNumber,
						unsigned char red,
						unsigned char green,
						unsigned char blue,
						unsigned char alpha);

void edit_colourFromText(unsigned char object,
						int objectNumber,
						unsigned char colour);

void edit_colourPolygon(int objectNumber, unsigned char colour);

void edit_colourToAlpha(unsigned char object,
						int objectNumber,
						double alpha);

void edit_createPolygon(unsigned char type,
						int numberOfSides,
						double newRadius,
						double newXPosition,
						double newYPosition,
						unsigned char colour);

void edit_createRectangle(	unsigned char type,
							double left,
							double right,
							double down,
							double up,
							unsigned char colour);				//Takes in the x and y coordinate of the block sides for plotting.

void edit_createSquare(	unsigned char type,
						double diagonalLength,
						double newXPosition,
						double newYPosition,
						unsigned char colour);

void edit_enableGrid(bool state);
void edit_enableKernelStats(bool state);

double edit_get(unsigned char object,
				int objectNumber,
				unsigned char attribute);				//Retrieves decimal data from game objects.

void edit_move(	unsigned char object,
				int objectNumber,
				double newXPosition,
				double newYPosition);

void edit_remove(unsigned char object, int objectNumber);
void edit_resize(unsigned char object, int objectNumber, double scale);	
void edit_scrollPlatform(	int objectNumber, 
							bool direction, 
							double startPosition, 
							double endPosition,
							double velocity);