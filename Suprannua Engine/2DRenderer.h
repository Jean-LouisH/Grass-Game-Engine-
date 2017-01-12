/**
 * 2D Renderer
 *
 * Author: Jean-Louis Haywood
 *
 * Displays all polygons and blocks within the 2D Camera's viewport. The order of rendering is organised from BACKGROUND to FOREGROUND.
 */

void render_displayStoredBlocks();				//Draws blocks by classification.
void render_displayStoredPolygons();			//Draws polygons by classification.
void render_displayText();						//Renders text to viewport or world from strings.
void render_drawBlock(int objectNumber);		//Renders a selected block.
void render_drawGrid();							//Divides world map into a grid for every metre.
void render_drawPolygon(int objectNumber);		//Renders a selected polygon.
