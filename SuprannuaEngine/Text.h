/**
 * Text
 *
 * Author: Jean-Louis Haywood
 *
 * Handles string data within the TextCache array to be positioned relative to the 2D camera or world.
 */

#pragma once

void text_adjust(int textCell, double xScroll, double yScroll);
void text_append(int textCell, char *newText);
void text_colour(int textCell, unsigned char colour);
void text_colourToAlpha(int textCell, double alpha);
void text_data(int textCell, double value);
void text_move(int textCell, double xText, double yText);

/*| Releases an array cell with text.*/ 
void text_remove(int textCell);

/*| Fills an empty array cell with new text.*/
void text_set(unsigned char textType, double xText, double yText, char *newText, unsigned char colour);
void text_update(int textCell, char *newText);

/*| Takes frame rate and time data, and then updates TextCache[0].*/
void text_updateKernelStats();
