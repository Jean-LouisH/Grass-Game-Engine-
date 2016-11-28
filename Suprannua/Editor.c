#include "Suprannua.h"

void edit_createRectangle(unsigned char type, double left, double right,
                         double down, double up, unsigned char colour)
{
    int i;

    for(i = 0; i < MAX_BLOCKS; i++)
    {
        if(block[i].properties.classification == NOTHING)
            break;
    }

	if (i > occupiedBlocks)
		occupiedBlocks = i;

    switch(type)
    {
        case PLATFORM:      block[i].properties.classification = PLATFORM;      break;
        case ENTITY:        block[i].properties.classification = ENTITY;        break;
        case FOREGROUND:    block[i].properties.classification = FOREGROUND;    break;
        case BACKGROUND:
        default:            block[i].properties.classification = BACKGROUND;
    }
    block[i].dimensions.width = (right - left);
    block[i].dimensions.height = (up - down);
    block[i].centre.xPosition = (left + right) / 2;
    block[i].centre.yPosition = (down + up) / 2;
    block[i].properties.mass = 1.0;

    edit_colourBlock(i, colour);
    geometry_plotBlock(i);
}

void edit_createSquare(unsigned char type, double diagonalLength, double newXPosition,
						double newYPosition, unsigned char colour)
{
	int i;

	for (i = 0; i < MAX_BLOCKS; i++)
	{
		if (block[i].properties.classification == NOTHING)
			break;
	}

	if (i > occupiedBlocks)
		occupiedBlocks = i;

	switch (type)
	{
		case PLATFORM:      block[i].properties.classification = PLATFORM;      break;
		case ENTITY:        block[i].properties.classification = ENTITY;        break;
		case FOREGROUND:    block[i].properties.classification = FOREGROUND;    break;
		case BACKGROUND:
		default:            block[i].properties.classification = BACKGROUND;
	}

	block[i].dimensions.width = (diagonalLength / sqrt(2));
	block[i].dimensions.height = block[i].dimensions.width;
	block[i].centre.xPosition = newXPosition;
	block[i].centre.yPosition = newYPosition;
	block[i].properties.mass = 1.0;

	edit_colourBlock(i, colour);
	geometry_plotBlock(i);
}

void edit_createPolygon(unsigned char type, int numberOfSides, double newRadius, double newXPosition,
                         double newYPosition, unsigned char colour)
{
    int i;
	srand(time(NULL));

    for(i = 0; i < MAX_POLYGONS; i++)
    {
        if(polygon[i].properties.classification == NOTHING)
            break;
    }

	if (i > occupiedPolygons)
		occupiedPolygons = i;

    switch(type)
    {
        case PLATFORM:      polygon[i].properties.classification = PLATFORM;      break;
        case ENTITY:        polygon[i].properties.classification = ENTITY;        break;
        case FOREGROUND:    polygon[i].properties.classification = FOREGROUND;    break;
        case BACKGROUND:
        default:            polygon[i].properties.classification = BACKGROUND;
    }
    polygon[i].properties.edges = numberOfSides;
    polygon[i].radius = newRadius;
    polygon[i].properties.mass = 1.0;
	polygon[i].properties.bouncePercentage = 0.3;

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

    edit_colourPolygon(i, colour);
    geometry_plotPolygon(i);
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

                        geometry_plotBlock(objectNumber);
        break;
    }
}
void edit_resize(unsigned char object, int objectNumber, double scale)
{
    switch(object)
    {
        case POLYGON:   polygon[objectNumber].radius = polygon[objectNumber].radius * scale;

                        geometry_plotPolygon(objectNumber);
        break;
        case BLOCK:
                        block[objectNumber].dimensions.width = block[objectNumber].dimensions.width * scale;
                        block[objectNumber].dimensions.height = block[objectNumber].dimensions.height * scale;

                        geometry_plotBlock(objectNumber);
        break;
    }
}

void edit_change(unsigned char object, int objectNumber, unsigned char attribute, double amount)
{
    switch(attribute)
    {
        case PLATFORM_GRAVITY:   if(object == GAME)
                            platformGravity = amount;
        break;
		case GRAVITY_CONSTANT:   if (object == GAME)
							gravityConstant = amount;
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
        case PLATFORM_GRAVITY:   if(object == GAME)
                            platformGravity += amount;
        break;
		case GRAVITY_CONSTANT:   if (object == GAME)
							gravityConstant += amount;
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

void edit_colourFromRGBA(unsigned char object, int objectNumber, unsigned char red,
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

void edit_colourFromText(unsigned char object, int objectNumber, unsigned char colour)
{
    if(object == POLYGON)
        edit_colourPolygon(objectNumber, colour);
    else if (object == BLOCK)
        edit_colourBlock(objectNumber, colour);
}

void edit_colourPolygon(int objectNumber, unsigned char colour)
{
    switch(colour)
    {
        case BLACK: polygon[objectNumber].properties.colour[RED]     = black[RED];
                    polygon[objectNumber].properties.colour[GREEN]   = black[GREEN];
                    polygon[objectNumber].properties.colour[BLUE]    = black[BLUE];
                    polygon[objectNumber].properties.colour[ALPHA]   = FULL;
        break;
        case WHITE: polygon[objectNumber].properties.colour[RED]     = white[RED];
                    polygon[objectNumber].properties.colour[GREEN]   = white[GREEN];
                    polygon[objectNumber].properties.colour[BLUE]    = white[BLUE];
                    polygon[objectNumber].properties.colour[ALPHA]   = FULL;
        break;
        case RED:   polygon[objectNumber].properties.colour[RED]     = red[RED];
                    polygon[objectNumber].properties.colour[GREEN]   = red[GREEN];
                    polygon[objectNumber].properties.colour[BLUE]    = red[BLUE];
                    polygon[objectNumber].properties.colour[ALPHA]   = FULL;
        break;
        case GREEN: polygon[objectNumber].properties.colour[RED]     = green[RED];
                    polygon[objectNumber].properties.colour[GREEN]   = green[GREEN];
                    polygon[objectNumber].properties.colour[BLUE]    = green[BLUE];
                    polygon[objectNumber].properties.colour[ALPHA]   = FULL;
        break;
        case BLUE:  polygon[objectNumber].properties.colour[RED]     = blue[RED];
                    polygon[objectNumber].properties.colour[GREEN]   = blue[GREEN];
                    polygon[objectNumber].properties.colour[BLUE]    = blue[BLUE];
                    polygon[objectNumber].properties.colour[ALPHA]   = FULL;
        break;
        case ORANGE: polygon[objectNumber].properties.colour[RED]    = orange[RED];
                    polygon[objectNumber].properties.colour[GREEN]   = orange[GREEN];
                    polygon[objectNumber].properties.colour[BLUE]    = orange[BLUE];
                    polygon[objectNumber].properties.colour[ALPHA]   = FULL;
        break;
        case YELLOW: polygon[objectNumber].properties.colour[RED]    = yellow[RED];
                    polygon[objectNumber].properties.colour[GREEN]   = yellow[GREEN];
                    polygon[objectNumber].properties.colour[BLUE]    = yellow[BLUE];
                    polygon[objectNumber].properties.colour[ALPHA]   = FULL;
        break;
        case VIOLET: polygon[objectNumber].properties.colour[RED]    = violet[RED];
                    polygon[objectNumber].properties.colour[GREEN]   = violet[GREEN];
                    polygon[objectNumber].properties.colour[BLUE]    = violet[BLUE];
                    polygon[objectNumber].properties.colour[ALPHA]   = FULL;
        break;
        case PURPLE: polygon[objectNumber].properties.colour[RED]    = purple[RED];
                    polygon[objectNumber].properties.colour[GREEN]   = purple[GREEN];
                    polygon[objectNumber].properties.colour[BLUE]    = purple[BLUE];
                    polygon[objectNumber].properties.colour[ALPHA]   = FULL;
        break;
        case BROWN: polygon[objectNumber].properties.colour[RED]     = brown[RED];
                    polygon[objectNumber].properties.colour[GREEN]   = brown[GREEN];
                    polygon[objectNumber].properties.colour[BLUE]    = brown[BLUE];
                    polygon[objectNumber].properties.colour[ALPHA]   = FULL;
        break;
        case SKY_BLUE: polygon[objectNumber].properties.colour[RED]  = skyBlue[RED];
                    polygon[objectNumber].properties.colour[GREEN]   = skyBlue[GREEN];
                    polygon[objectNumber].properties.colour[BLUE]    = skyBlue[BLUE];
                    polygon[objectNumber].properties.colour[ALPHA]   = FULL;
        break;
        case GOLD: polygon[objectNumber].properties.colour[RED]      = gold[RED];
                    polygon[objectNumber].properties.colour[GREEN]   = gold[GREEN];
                    polygon[objectNumber].properties.colour[BLUE]    = gold[BLUE];
                    polygon[objectNumber].properties.colour[ALPHA]   = FULL;
        break;
        case SEA_GREEN: polygon[objectNumber].properties.colour[RED] = seaGreen[RED];
                    polygon[objectNumber].properties.colour[GREEN]   = seaGreen[GREEN];
                    polygon[objectNumber].properties.colour[BLUE]    = seaGreen[BLUE];
                    polygon[objectNumber].properties.colour[ALPHA]   = FULL;
        break;
        case PINK: polygon[objectNumber].properties.colour[RED]      = pink[RED];
                    polygon[objectNumber].properties.colour[GREEN]   = pink[GREEN];
                    polygon[objectNumber].properties.colour[BLUE]    = pink[BLUE];
                    polygon[objectNumber].properties.colour[ALPHA]   = FULL;
        break;
        case GREY:  polygon[objectNumber].properties.colour[RED]     = grey[RED];
                    polygon[objectNumber].properties.colour[GREEN]   = grey[GREEN];
                    polygon[objectNumber].properties.colour[BLUE]    = grey[BLUE];
                    polygon[objectNumber].properties.colour[ALPHA]   = FULL;
        break;
        default:    polygon[objectNumber].properties.colour[RED]     = 0;
                    polygon[objectNumber].properties.colour[GREEN]   = 0;
                    polygon[objectNumber].properties.colour[BLUE]    = 0;
                    polygon[objectNumber].properties.colour[ALPHA]   = FULL;
    }
}
void edit_colourBlock(int objectNumber, unsigned char colour)
{
    switch(colour)
    {
        case BLACK: block[objectNumber].properties.colour[RED]     = black[RED];
                    block[objectNumber].properties.colour[GREEN]   = black[GREEN];
                    block[objectNumber].properties.colour[BLUE]    = black[BLUE];
                    block[objectNumber].properties.colour[ALPHA]   = FULL;
        break;
        case WHITE: block[objectNumber].properties.colour[RED]     = white[RED];
                    block[objectNumber].properties.colour[GREEN]   = white[GREEN];
                    block[objectNumber].properties.colour[BLUE]    = white[BLUE];
                    block[objectNumber].properties.colour[ALPHA]   = FULL;
        break;
        case RED:   block[objectNumber].properties.colour[RED]     = red[RED];
                    block[objectNumber].properties.colour[GREEN]   = red[GREEN];
                    block[objectNumber].properties.colour[BLUE]    = red[BLUE];
                    block[objectNumber].properties.colour[ALPHA]   = FULL;
        break;
        case GREEN: block[objectNumber].properties.colour[RED]     = green[RED];
                    block[objectNumber].properties.colour[GREEN]   = green[GREEN];
                    block[objectNumber].properties.colour[BLUE]    = green[BLUE];
                    block[objectNumber].properties.colour[ALPHA]   = FULL;
        break;
        case BLUE:  block[objectNumber].properties.colour[RED]     = blue[RED];
                    block[objectNumber].properties.colour[GREEN]   = blue[GREEN];
                    block[objectNumber].properties.colour[BLUE]    = blue[BLUE];
                    block[objectNumber].properties.colour[ALPHA]   = FULL;
        break;
        case ORANGE: block[objectNumber].properties.colour[RED]    = orange[RED];
                    block[objectNumber].properties.colour[GREEN]   = orange[GREEN];
                    block[objectNumber].properties.colour[BLUE]    = orange[BLUE];
                    block[objectNumber].properties.colour[ALPHA]   = FULL;
        break;
        case YELLOW: block[objectNumber].properties.colour[RED]    = yellow[RED];
                    block[objectNumber].properties.colour[GREEN]   = yellow[GREEN];
                    block[objectNumber].properties.colour[BLUE]    = yellow[BLUE];
                    block[objectNumber].properties.colour[ALPHA]   = FULL;
        break;
        case VIOLET: block[objectNumber].properties.colour[RED]    = violet[RED];
                    block[objectNumber].properties.colour[GREEN]   = violet[GREEN];
                    block[objectNumber].properties.colour[BLUE]    = violet[BLUE];
                    block[objectNumber].properties.colour[ALPHA]   = FULL;
        break;
        case PURPLE: block[objectNumber].properties.colour[RED]    = purple[RED];
                    block[objectNumber].properties.colour[GREEN]   = purple[GREEN];
                    block[objectNumber].properties.colour[BLUE]    = purple[BLUE];
                    block[objectNumber].properties.colour[ALPHA]   = FULL;
        break;
        case BROWN: block[objectNumber].properties.colour[RED]     = brown[RED];
                    block[objectNumber].properties.colour[GREEN]   = brown[GREEN];
                    block[objectNumber].properties.colour[BLUE]    = brown[BLUE];
                    block[objectNumber].properties.colour[ALPHA]   = FULL;
        break;
        case SKY_BLUE: block[objectNumber].properties.colour[RED]  = skyBlue[RED];
                    block[objectNumber].properties.colour[GREEN]   = skyBlue[GREEN];
                    block[objectNumber].properties.colour[BLUE]    = skyBlue[BLUE];
                    block[objectNumber].properties.colour[ALPHA]   = FULL;
        break;
        case GOLD: block[objectNumber].properties.colour[RED]      = gold[RED];
                    block[objectNumber].properties.colour[GREEN]   = gold[GREEN];
                    block[objectNumber].properties.colour[BLUE]    = gold[BLUE];
                    block[objectNumber].properties.colour[ALPHA]   = FULL;
        break;
        case SEA_GREEN: block[objectNumber].properties.colour[RED] = seaGreen[RED];
                    block[objectNumber].properties.colour[GREEN]   = seaGreen[GREEN];
                    block[objectNumber].properties.colour[BLUE]    = seaGreen[BLUE];
                    block[objectNumber].properties.colour[ALPHA]   = FULL;
        break;
        case PINK: block[objectNumber].properties.colour[RED]      = pink[RED];
                    block[objectNumber].properties.colour[GREEN]   = pink[GREEN];
                    block[objectNumber].properties.colour[BLUE]    = pink[BLUE];
                    block[objectNumber].properties.colour[ALPHA]   = FULL;
        break;
        case GREY:  block[objectNumber].properties.colour[RED]     = grey[RED];
                    block[objectNumber].properties.colour[GREEN]   = grey[GREEN];
                    block[objectNumber].properties.colour[BLUE]    = grey[BLUE];
                    block[objectNumber].properties.colour[ALPHA]   = FULL;
        break;
        default:    block[objectNumber].properties.colour[RED]     = 0;
                    block[objectNumber].properties.colour[GREEN]   = 0;
                    block[objectNumber].properties.colour[BLUE]    = 0;
                    block[objectNumber].properties.colour[ALPHA]   = FULL;
    }
}

void edit_colourToAlpha(unsigned char object, int objectNumber, double alpha)
{
    if(object == POLYGON)
        polygon[objectNumber].properties.colour[3] = alpha * FULL;
    else if(object == BLOCK)
        block[objectNumber].properties.colour[3] = alpha * FULL;
}

double edit_get(unsigned char object, int objectNumber, unsigned char attribute)
{
	switch (object)
	{
		case POLYGON:	switch (attribute)
						{
							case ALPHA:     return (polygon[objectNumber].properties.colour[3] / FULL); break;
							case ANGLE:     return polygon[objectNumber].properties.angle;              break;
							case MASS:      return polygon[objectNumber].properties.mass;               break;
							case XVELOCITY: return polygon[objectNumber].properties.xVelocity;          break;
							case YVELOCITY: return polygon[objectNumber].properties.yVelocity;          break;
							case BOUNCE:    return polygon[objectNumber].properties.bouncePercentage;   break;
							case XPOSITION: return polygon[objectNumber].centre.xPosition;              break;
							case YPOSITION: return polygon[objectNumber].centre.yPosition;              break;
							case RADIUS:    return polygon[objectNumber].radius;                        break;
						}
		break;
		case BLOCK:		switch (attribute)
						{
							case ALPHA:     return (block[objectNumber].properties.colour[3] / 255);    break;
							case MASS:      return block[objectNumber].properties.mass;                 break;
							case XVELOCITY: return block[objectNumber].properties.xVelocity;            break;
							case YVELOCITY: return block[objectNumber].properties.yVelocity;            break;
							case BOUNCE:    return block[objectNumber].properties.bouncePercentage;     break;
							case XPOSITION: return block[objectNumber].centre.xPosition;                break;
							case YPOSITION: return block[objectNumber].centre.yPosition;                break;
							case WIDTH:     return block[objectNumber].dimensions.width;                break;
							case HEIGHT:    return block[objectNumber].dimensions.height;               break;
						}
		break;
		case GAME:		switch (attribute)
						{
							case XCENTRE:   return (worldSizeMetres.width / 2);							break;
							case YCENTRE:   return (worldSizeMetres.height / 2);						break;
							case WIDTH:     return worldSizeMetres.width;								break;
							case HEIGHT:    return worldSizeMetres.height;								break;
						}
		break;
		case CAMERA:	switch (attribute)
						{
							case XPOSITION: return camera2D.target.xPosition;							break;
							case YPOSITION: return camera2D.target.yPosition;							break;
							case WIDTH:     return camera2D.viewport.width;								break;
							case HEIGHT:    return camera2D.viewport.height;				            break;
						}
		break;
	}
}

void edit_grid(bool state)
{
	if (state)
		gridState = true;
	else
		gridState = false;
}
