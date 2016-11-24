/**
* Heads Up Display
*
* Handles string data within the TextCache array to be positioned relative to the 2D camera or world.
*/

void HUD_updateKernelStats(); //Takes frame rate and time data, and then updates TextCache[0].
void HUD_setText(double xText, double yText, char newText); //Fills an empty array cell with new text.
void HUD_removeText(int textCell); //Releases an array cell with text.
