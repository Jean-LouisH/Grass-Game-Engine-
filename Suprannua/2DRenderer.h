/**
* 2D Renderer
*
* Displays all polygons and blocks within the 2D Camera's viewport. The order of rendering is organised from BACKGROUND to FOREGROUND.
*/

void render_displayPolygonList(); //Draws polygons by classification.
void render_drawPolygon(int objectNumber); //Renders polygons from camera viewport.
void render_displayBlockList(); //Draws blocks by classification.
void render_drawBlock(int objectNumber); //Renders blocks from camera viewport.
void render_drawGrid(); //Divides world map visually.
void render_postHUD(); //Renders text to viewport or world from strings.
