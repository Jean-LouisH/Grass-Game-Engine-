#include "Definitions.h"

void edit_create(unsigned char object, unsigned char type, int numberOfSides,
                  double newRadius, double newWidth, double newHeight, double newXPosition,
                  double newYPosition,unsigned char red, unsigned char green, unsigned char blue,
                  unsigned char alpha)
{
    int i;

    srand((unsigned)time(NULL));
    switch(object)
    {
        case POLYGON:
                        for(i = 0; i < MAX_POLYGONS; i++)
                        {
                            if(polygon[i].properties.classification == NOTHING)
                                break;
                        }

                        if (i < MAX_POLYGONS)
                        {
                            polygon[i].properties.classification = type;
                            polygon[i].properties.edges = numberOfSides;
                            polygon[i].radius = newRadius;

                            if(newXPosition == 0 || newYPosition == 0) //provides a random position if non is specified.
                            {
                                polygon[i].centre.xPosition = rand() %
                                (int)(worldSizeMetres.width - (2 * polygon[i].radius) * (i + 1))+ (polygon[i].radius);
                                polygon[i].centre.yPosition = rand() %
                                (int)(worldSizeMetres.height - (2 * polygon[i].radius) * (i + 1)) + (polygon[i].radius);
                            }
                            else
                            {
                                polygon[i].centre.xPosition = newXPosition;
                                polygon[i].centre.yPosition = newYPosition;
                            }

                            polygon[i].properties.colour[RED] = red;
                            polygon[i].properties.colour[GREEN] = green;
                            polygon[i].properties.colour[BLUE] = blue;
                            polygon[i].properties.colour[ALPHA] = alpha;

                            geometry_plotPolygon(i);
                        }
        break;
        case BLOCK:       for(i = 0; i < MAX_BLOCKS; i++)
                        {
                            if(block[i].properties.classification == NOTHING)
                                break;
                        }

                        if (i < MAX_BLOCKS)
                        {
                            block[i].properties.classification = type;
                            block[i].dimensions.width = newWidth;
                            block[i].dimensions.height = newHeight;
                            if(newXPosition == 0 || newYPosition == 0)
                            {
                                block[i].centre.xPosition = rand() %
                                (int)(worldSizeMetres.width - (block[i].dimensions.width) * (i + 1)) + (block[i].dimensions.width);
                                block[i].centre.yPosition = rand() %
                                (int)(worldSizeMetres.height - (block[i].dimensions.height) * (i + 1)) + (block[i].dimensions.height);
                            }
                            else
                            {
                                block[i].centre.xPosition = newXPosition;
                                block[i].centre.yPosition = newYPosition;
                            }
                            block[i].properties.colour[RED] = red;
                            block[i].properties.colour[GREEN] = green;
                            block[i].properties.colour[BLUE] = blue;
                            block[i].properties.colour[ALPHA] = alpha;

                            geometry_plotBox(i);
                        }
        break;
    }
}
void edit_remove(unsigned char object, int objectNumber)
{

    int i;

    switch(object)
    {
        case POLYGON:   //Clears the entire cell
                        polygon[objectNumber].radius = 0.0;
                        polygon[objectNumber].properties.angle = 0.0;
                        polygon[objectNumber].properties.classification = NOTHING;
                        for(i  = 0; i < 4; i++)
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
        case BLOCK:
                        block[objectNumber].centre.xPosition = 0.0;
                        block[objectNumber].centre.yPosition = 0.0;
                        block[objectNumber].properties.angle = 0.0;
                        block[objectNumber].properties.classification = NOTHING;
                        for(i = 0; i < 4; i++)
                            block[objectNumber].properties.colour[i] = 0;
                        block[objectNumber].properties.mass = 0.0;
                        block[objectNumber].properties.xVelocity = 0.0;
                        block[objectNumber].properties.yVelocity = 0.0;
                        for(i = 0; i < 4; i++)
                        {
                            block[objectNumber].vertices[i].xPosition = 0.0;
                            block[objectNumber].vertices[i].yPosition = 0.0;
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

                        geometry_plotPolygon(objectNumber);
        break;
        case BLOCK:       block[objectNumber].centre.xPosition = newXPosition;
                        block[objectNumber].centre.yPosition = newYPosition;

                        geometry_plotBox(objectNumber);
        break;
    }
}
void edit_resize(unsigned char object, int objectNumber, double scale)
{

    int i;

    switch(object)
    {
        case POLYGON:   polygon[objectNumber].radius = polygon[objectNumber].radius * scale;

                        geometry_plotPolygon(i);
        break;
        case BLOCK:
                        block[objectNumber].dimensions.width = block[objectNumber].dimensions.width * scale;
                        block[objectNumber].dimensions.height = block[objectNumber].dimensions.height * scale;

                        geometry_plotBox(i);
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
        case ANGLE:     if(object == POLYGON)
                            polygon[objectNumber].properties.angle = amount;
                        if(object == BLOCK)
                            block[objectNumber].properties.angle = amount;
        break;
        case MASS:      if(object == POLYGON)
                            polygon[objectNumber].properties.mass = amount;
                        if(object == BLOCK)
                            block[objectNumber].properties.mass = amount;
        break;
        case XVELOCITY: if(object == POLYGON)
                            polygon[objectNumber].properties.xVelocity = amount;
                        if(object == BLOCK)
                            block[objectNumber].properties.xVelocity = amount;
        break;
        case YVELOCITY: if(object == POLYGON)
                            polygon[objectNumber].properties.yVelocity = amount;
                        if(object == BLOCK)
                            block[objectNumber].properties.yVelocity = amount;
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

        case ANGLE:     if(object == POLYGON)
                            polygon[objectNumber].properties.angle += amount;
                        if(object == BLOCK)
                            block[objectNumber].properties.angle += amount;
        break;
        case MASS:      if(object == POLYGON)
                            polygon[objectNumber].properties.mass += amount;
                        if(object == BLOCK)
                            block[objectNumber].properties.mass += amount;
        break;
        case XVELOCITY: if(object == POLYGON)
                            polygon[objectNumber].properties.xVelocity += amount;
                        if(object == BLOCK)
                            block[objectNumber].properties.xVelocity += amount;
        break;
        case YVELOCITY: if(object == POLYGON)
                            polygon[objectNumber].properties.yVelocity += amount;
                        if(object == BLOCK)
                            block[objectNumber].properties.yVelocity += amount;
        break;
    }
}

void edit_colour(unsigned char object, int objectNumber, unsigned char red,
                 unsigned char green, unsigned char blue, unsigned char alpha)
{
    switch(object)
    {
        case POLYGON:   polygon[objectNumber].properties.colour[RED]    = red;
                        polygon[objectNumber].properties.colour[GREEN]  = green;
                        polygon[objectNumber].properties.colour[BLUE]   = blue;
                        polygon[objectNumber].properties.colour[ALPHA]  = alpha;
        break;
        case BLOCK:       block[objectNumber].properties.colour[RED]    = red;
                        block[objectNumber].properties.colour[GREEN]  = green;
                        block[objectNumber].properties.colour[BLUE]   = blue;
                        block[objectNumber].properties.colour[ALPHA]  = alpha;
        break;
    }
}
void edit_force(unsigned char firstObject, int firstObjectNumber,
                 unsigned char preposition, unsigned char secondObject, int secondobjectNumber)// preposition - "to", "from"
{

}
