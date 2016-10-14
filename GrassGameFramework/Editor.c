#include "Definitions.h"
#include "Editor.h"

void edit_create(unsigned char object, unsigned char type, int numberOfSides,
                  double newRadius, double newWidth, double newHeight, double newXPosition,
                  double newYPosition,unsigned char red, unsigned char green, unsigned char blue)
{
    srand((unsigned)time(NULL));
    switch(object)
    {
        case POLYGON:   k = 0;
                        while(polygon[k].properties.classification != NOTHING) //searches for a non-empty cell.
                        {
                            k++;
                        }

                        polygon[k].properties.classification = type;
                        polygon[k].properties.sides = numberOfSides;
                        polygon[k].radius = newRadius;

                        if(newXPosition == 0 || newYPosition == 0) //provides a random position if non is specified.
                        {
                            polygon[k].centre.xPosition = rand() %
                            (int)(xMapSize - (2 * polygon[k].radius) * (k + 1))+ (polygon[k].radius);
                            polygon[k].centre.yPosition = rand() %
                            (int)(yMapSize - (2 * polygon[k].radius) * (k + 1)) + (polygon[k].radius);
                        }
                        else
                        {
                            polygon[k].centre.xPosition = newXPosition;
                            polygon[k].centre.yPosition = newYPosition;
                        }

                        polygon[k].properties.colour[RED] = red;
                        polygon[k].properties.colour[GREEN] = green;
                        polygon[k].properties.colour[BLUE] = blue;

                        compute_plotPolygon(k);
        break;
        case BOX:       k = 0;
                        while(box[k].properties.classification != NOTHING) //searches for a non-empty cell.
                        {
                            k++;
                        }

                        box[k].properties.classification = type;
                        box[k].boxWidth = newWidth;
                        box[k].boxHeight = newHeight;
                        if(newXPosition == 0 || newYPosition == 0)
                        {
                            box[k].centre.xPosition = rand() %
                            (int)(xMapSize - (box[k].boxWidth) * (k + 1)) + (box[k].boxWidth);
                            box[k].centre.yPosition = rand() %
                            (int)(yMapSize - (box[k].boxHeight) * (k + 1)) + (box[k].boxHeight);
                        }
                        else
                        {
                            box[k].centre.xPosition = newXPosition;
                            box[k].centre.yPosition = newYPosition;
                        }
                        box[k].properties.colour[RED] = red;
                        box[k].properties.colour[GREEN] = green;
                        box[k].properties.colour[BLUE] = blue;

                        compute_plotBox(k);
        break;
    }
}
void edit_remove(unsigned char object, int objectNumber)
{
    switch(object)
    {
        case POLYGON:   //Clears the entire cell
                        polygon[objectNumber].radius = 0.0;
                        polygon[objectNumber].properties.acceleration = 0.0;
                        polygon[objectNumber].properties.angle = 0.0;
                        polygon[objectNumber].properties.classification = NOTHING;
                        for(i  = 0; i < 3; i++)
                            polygon[objectNumber].properties.colour[i] = 0;
                        polygon[objectNumber].properties.mass = 0.0;
                        polygon[objectNumber].properties.xVelocity = 0.0;
                        polygon[objectNumber].properties.yVelocity = 0.0;
                        polygon[objectNumber].centre.xPosition = 0.0;
                        polygon[objectNumber].centre.yPosition = 0.0;
                        for(i = 0; i < MAX_POLYGON_SIDES; i++)
                        {
                            polygon[objectNumber].vertices[i].xPosition = 0.0;
                            polygon[objectNumber].vertices[i].yPosition = 0.0;
                        }
        break;
        case BOX:
                        box[objectNumber].centre.xPosition = 0.0;
                        box[objectNumber].centre.yPosition = 0.0;
                        box[objectNumber].properties.acceleration = 0.0;
                        box[objectNumber].properties.angle = 0.0;
                        box[objectNumber].properties.classification = NOTHING;
                        for(i = 0; i < 3; i++)
                            box[objectNumber].properties.colour[i] = 0;
                        box[objectNumber].properties.mass = 0.0;
                        box[objectNumber].properties.xVelocity = 0.0;
                        box[objectNumber].properties.yVelocity = 0.0;
                        for(i = 0; i < 4; i++)
                        {
                            box[objectNumber].vertices[i].xPosition = 0.0;
                            box[objectNumber].vertices[i].yPosition = 0.0;
                        }
        break;
    }
}
void edit_move(unsigned char object, int objectNumber, double newXPosition, double newYPosition)
{
    switch(object)
    {
        case POLYGON:   polygon[objectNumber].centre.xPosition = newXPosition;
                        polygon[objectNumber].centre.yPosition = newYPosition;

                        compute_plotPolygon(k);
        break;
        case BOX:       box[objectNumber].centre.xPosition = newXPosition;
                        box[objectNumber].centre.yPosition = newYPosition;

                        compute_plotBox(k);
        break;
    }
}
void edit_resize(unsigned char object, int objectNumber, double scale)
{
    switch(object)
    {
        case POLYGON:   polygon[objectNumber].radius = polygon[objectNumber].radius * scale;

                        compute_plotPolygon(k);
        break;
        case BOX:
                        box[objectNumber].boxWidth = box[objectNumber].boxWidth * scale;
                        box[objectNumber].boxHeight = box[objectNumber].boxHeight * scale;

                        compute_plotBox(k);
        break;
    }
}

void edit_change(unsigned char object, int objectNumber, unsigned char attribute, double amount)
{
    switch(attribute)
    {
        case GRAVITY:   if(object == GAME)
                            platformGravity = amount;
        break;
        case FRICTION:  if(object == GAME)
                            friction = amount;
        break;

        case ANGLE:     if(object == POLYGON)
                            polygon[objectNumber].properties.angle = amount;
                        if(object == BOX)
                            box[objectNumber].properties.angle = amount;
        break;
        case MASS:      if(object == POLYGON)
                            polygon[objectNumber].properties.mass = amount;
                        if(object == BOX)
                            box[objectNumber].properties.mass = amount;
        break;
        case XVELOCITY: if(object == POLYGON)
                            polygon[objectNumber].properties.xVelocity = amount;
                        if(object == BOX)
                            box[objectNumber].properties.xVelocity = amount;
        break;
        case YVELOCITY: if(object == POLYGON)
                            polygon[objectNumber].properties.yVelocity = amount;
                        if(object == BOX)
                            box[objectNumber].properties.yVelocity = amount;
        break;
    }
}

void edit_adjust(unsigned char object, int objectNumber, unsigned char attribute, double amount)
{
    switch(attribute)
    {
        case GRAVITY:   if(object == GAME)
                            platformGravity += amount;
        break;
        case FRICTION:  if(object == GAME)
                            friction += amount;
        break;

        case ANGLE:     if(object == POLYGON)
                            polygon[objectNumber].properties.angle += amount;
                        if(object == BOX)
                            box[objectNumber].properties.angle += amount;
        break;
        case MASS:      if(object == POLYGON)
                            polygon[objectNumber].properties.mass += amount;
                        if(object == BOX)
                            box[objectNumber].properties.mass += amount;
        break;
        case XVELOCITY: if(object == POLYGON)
                            polygon[objectNumber].properties.xVelocity += amount;
                        if(object == BOX)
                            box[objectNumber].properties.xVelocity += amount;
        break;
        case YVELOCITY: if(object == POLYGON)
                            polygon[objectNumber].properties.yVelocity += amount;
                        if(object == BOX)
                            box[objectNumber].properties.yVelocity += amount;
        break;
    }
}

void edit_colour(unsigned char object, int objectNumber, unsigned char red, unsigned char green, unsigned char blue)
{
    switch(object)
    {
        case POLYGON:   polygon[objectNumber].properties.colour[RED]    = red;
                        polygon[objectNumber].properties.colour[GREEN]  = green;
                        polygon[objectNumber].properties.colour[BLUE]   = blue;
        break;
        case BOX:       box[objectNumber].properties.colour[RED]    = red;
                        box[objectNumber].properties.colour[GREEN]  = green;
                        box[objectNumber].properties.colour[BLUE]   = blue;
        break;
    }
}
void edit_force(unsigned char firstObject, int firstObjectNumber,
                 unsigned char preposition, unsigned char secondObject, int secondobjectNumber)// preposition - "to", "from"
{

}
