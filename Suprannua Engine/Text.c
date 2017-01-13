#include "SuprannuaEngine.h"

void text_adjust(int textCell, double xScroll, double yScroll)
{
	textCache[textCell].textPin.xPosition += xScroll / FRAME_RATE;
	textCache[textCell].textPin.yPosition += yScroll / FRAME_RATE;
}

void text_append(int textCell, char *newText)
{
	char *oldText = textCache[textCell].textContent;
	sprintf(textCache[textCell].textContent, "%s %s", oldText, newText);
}

void text_colour(int textCell, unsigned char colour)
{
	switch (colour)
	{
		case BLACK: textCache[textCell].colour[RED] = black[RED];
					textCache[textCell].colour[GREEN] = black[GREEN];
					textCache[textCell].colour[BLUE] = black[BLUE];
					textCache[textCell].colour[ALPHA] = FULL;
		break;
		case WHITE: textCache[textCell].colour[RED] = white[RED];
					textCache[textCell].colour[GREEN] = white[GREEN];
					textCache[textCell].colour[BLUE] = white[BLUE];
					textCache[textCell].colour[ALPHA] = FULL;
		break;
		case RED:   textCache[textCell].colour[RED] = red[RED];
					textCache[textCell].colour[GREEN] = red[GREEN];
					textCache[textCell].colour[BLUE] = red[BLUE];
					textCache[textCell].colour[ALPHA] = FULL;
		break;
		case GREEN: textCache[textCell].colour[RED] = green[RED];
					textCache[textCell].colour[GREEN] = green[GREEN];
					textCache[textCell].colour[BLUE] = green[BLUE];
					textCache[textCell].colour[ALPHA] = FULL;
		break;
		case BLUE:  textCache[textCell].colour[RED] = blue[RED];
					textCache[textCell].colour[GREEN] = blue[GREEN];
					textCache[textCell].colour[BLUE] = blue[BLUE];
					textCache[textCell].colour[ALPHA] = FULL;
		break;
		case ORANGE: textCache[textCell].colour[RED] = orange[RED];
					textCache[textCell].colour[GREEN] = orange[GREEN];
					textCache[textCell].colour[BLUE] = orange[BLUE];
					textCache[textCell].colour[ALPHA] = FULL;
		break;
		case YELLOW: textCache[textCell].colour[RED] = yellow[RED];
					textCache[textCell].colour[GREEN] = yellow[GREEN];
					textCache[textCell].colour[BLUE] = yellow[BLUE];
					textCache[textCell].colour[ALPHA] = FULL;
		break;
		case VIOLET: textCache[textCell].colour[RED] = violet[RED];
					textCache[textCell].colour[GREEN] = violet[GREEN];
					textCache[textCell].colour[BLUE] = violet[BLUE];
					textCache[textCell].colour[ALPHA] = FULL;
		break;
		case PURPLE: textCache[textCell].colour[RED] = purple[RED];
					textCache[textCell].colour[GREEN] = purple[GREEN];
					textCache[textCell].colour[BLUE] = purple[BLUE];
					textCache[textCell].colour[ALPHA] = FULL;
		break;
		case BROWN: textCache[textCell].colour[RED] = brown[RED];
					textCache[textCell].colour[GREEN] = brown[GREEN];
					textCache[textCell].colour[BLUE] = brown[BLUE];
					textCache[textCell].colour[ALPHA] = FULL;
		break;
		case SKY_BLUE: textCache[textCell].colour[RED] = skyBlue[RED];
						textCache[textCell].colour[GREEN] = skyBlue[GREEN];
						textCache[textCell].colour[BLUE] = skyBlue[BLUE];
						textCache[textCell].colour[ALPHA] = FULL;
		break;
		case GOLD:	textCache[textCell].colour[RED] = gold[RED];
					textCache[textCell].colour[GREEN] = gold[GREEN];
					textCache[textCell].colour[BLUE] = gold[BLUE];
					textCache[textCell].colour[ALPHA] = FULL;
		break;
		case SEA_GREEN: textCache[textCell].colour[RED] = seaGreen[RED];
						textCache[textCell].colour[GREEN] = seaGreen[GREEN];
						textCache[textCell].colour[BLUE] = seaGreen[BLUE];
						textCache[textCell].colour[ALPHA] = FULL;
		break;
		case PINK: textCache[textCell].colour[RED] = pink[RED];
					textCache[textCell].colour[GREEN] = pink[GREEN];
					textCache[textCell].colour[BLUE] = pink[BLUE];
					textCache[textCell].colour[ALPHA] = FULL;
		break;
		case GREY:  textCache[textCell].colour[RED] = grey[RED];
					textCache[textCell].colour[GREEN] = grey[GREEN];
					textCache[textCell].colour[BLUE] = grey[BLUE];
					textCache[textCell].colour[ALPHA] = FULL;
		break;
		case DARK_RED:  textCache[textCell].colour[RED] = darkRed[RED];
						textCache[textCell].colour[GREEN] = darkRed[GREEN];
						textCache[textCell].colour[BLUE] = darkRed[BLUE];
						textCache[textCell].colour[ALPHA] = FULL;
		break;
		case DARK_GREEN:	textCache[textCell].colour[RED] = darkGreen[RED];
							textCache[textCell].colour[GREEN] = darkGreen[GREEN];
							textCache[textCell].colour[BLUE] = darkGreen[BLUE];
							textCache[textCell].colour[ALPHA] = FULL;
		break;
		case DARK_BLUE:		textCache[textCell].colour[RED] = darkBlue[RED];
							textCache[textCell].colour[GREEN] = darkBlue[GREEN];
							textCache[textCell].colour[BLUE] = darkBlue[BLUE];
							textCache[textCell].colour[ALPHA] = FULL;
		break;
		case DARK_BROWN:	textCache[textCell].colour[RED] = darkBrown[RED];
							textCache[textCell].colour[GREEN] = darkBrown[GREEN];
							textCache[textCell].colour[BLUE] = darkBrown[BLUE];
							textCache[textCell].colour[ALPHA] = FULL;
		break;
		case MAGENTA:		textCache[textCell].colour[RED] = magenta[RED];
							textCache[textCell].colour[GREEN] = magenta[GREEN];
							textCache[textCell].colour[BLUE] = magenta[BLUE];
							textCache[textCell].colour[ALPHA] = FULL;
		break;
		default:    textCache[textCell].colour[RED] = FULL;
					textCache[textCell].colour[GREEN] = FULL;
					textCache[textCell].colour[BLUE] = FULL;
					textCache[textCell].colour[ALPHA] = FULL;
	}
}

void text_colourToAlpha(int textCell, double alpha)
{
	textCache[textCell].colour[ALPHA] = alpha * FULL;
}

void text_data(int textCell, double value)
{
	char *oldText = textCache[textCell].textContent;
	sprintf(textCache[textCell].textContent, "%s: %.1f", oldText, value);
}

void text_move(int textCell, double xText, double yText)
{
	textCache[textCell].textPin.xPosition = xText;
	textCache[textCell].textPin.yPosition = yText;
}

void text_remove(int textCell)
{
	textCache[textCell].classification = NOTHING;
	sprintf(textCache[textCell].textContent, '/0');
}

void text_set(unsigned char textType, double xText, double yText, char *newText, unsigned char colour)
{
	int i;

	for (i = 0; i < MAX_TEXTS; i++)
	{
		if (textCache[i].classification == NOTHING)
			break;
	}

	if (i > storedTexts)
		storedTexts = i;

	textCache[i].classification = textType;
	textCache[i].textPin.xPosition = xText;
	textCache[i].textPin.yPosition = yText;
	text_colour(i, colour);

	sprintf(textCache[i].textContent, "%s", newText);
}

void text_update(int textCell, char *newText)
{
	sprintf(textCache[textCell].textContent, "%s", newText);
}

void text_updateKernelStats()
{
    sprintf(textCache[1].textContent, SOFTWARE VERSION "Kernel time: %.0fs, Runtime: %.2fs, Frame count: %d, FPS: %.2f",
            kernelTime, timeCount, frameCount, framesPerSecond);
}
