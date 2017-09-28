/**
 * Editor
 *
 * Author: Jean-Louis Haywood
 *
 * Directly reads or writes the data of polygons and blocks to organise scenes from initialisation or in response to scripted events.
 */

#pragma once

 /*| increments data values per second to attributes.*/
void edit_adjust(unsigned char object,
	int objectNumber,
	unsigned char attribute,
	double amount);	

void edit_change(unsigned char object,
	int objectNumber,
	unsigned char attribute,
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

/*| Returns polygon objectNumber*/
int edit_createPolygon(unsigned char type,
	int numberOfSides,
	double newRadius,
	double newXPosition,
	double newYPosition,
	unsigned char colour);


/*| Takes in the x and y coordinate of the block sides for plotting.
 | Returns block objectNumber*/
int edit_createRectangle(unsigned char type,
	double left,
	double right,
	double down,
	double up,
	unsigned char colour);

/*| Returns block objectNumber*/
int edit_createSquare(unsigned char type,
	double diagonalLength,
	double newXPosition,
	double newYPosition,
	unsigned char colour);

void edit_enableGrid(bool state);
void edit_enableEngineStats(bool state);

/*| Retrieves decimal data from game objects.*/
double edit_get(unsigned char object,
	int objectNumber,
	unsigned char attribute);

void edit_hide(unsigned char object, int objectNumber);

void edit_move(unsigned char object,
	int objectNumber,
	double newXPosition,
	double newYPosition);

void edit_remove(unsigned char object, int objectNumber);

/*| Clears all Engine runtime data. All in game variables must be manually cleared.*/
void edit_reset();
void edit_resize(unsigned char object, int objectNumber, double scale);
void edit_scrollPlatform(int objectNumber,
	bool direction,
	double startPosition,
	double endPosition,
	double velocity);