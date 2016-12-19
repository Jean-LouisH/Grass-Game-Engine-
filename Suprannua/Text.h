/**
 * Text
 *
 * Author: Jean-Louis Haywood
 *
 * Handles string data within the TextCache array to be positioned relative to the 2D camera or world.
 */

void text_remove(int textCell);								//Releases an array cell with text.
void text_set(double xText, double yText, char newText);	//Fills an empty array cell with new text.
void text_updateKernelStats();								//Takes frame rate and time data, and then updates TextCache[0].
