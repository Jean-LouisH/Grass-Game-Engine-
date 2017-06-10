/**
 * 2D Renderer
 *
 * Author: Jean-Louis Haywood
 *
 * Displays all polygons and blocks within the 2D Camera's viewport. The order of rendering is organised from BACKGROUND to FOREGROUND.
 */

#pragma once

void render_addRenderingLayer(unsigned char objectType,
	unsigned char classification,
	int objectNumber);

void render_displayBackgrounds();
void render_displayPlatforms();
void render_displayEntities();
void render_displayForegrounds();

void render_drawByObjectType(int objectNumber, unsigned char objectType);

void render_displayText();						//Renders text to viewport or world from strings.
void render_drawBlock(int objectNumber);		//Renders a selected block.
void render_drawGrid();							//Divides world map into a grid for every metre.
void render_drawPolygon(int objectNumber);		//Renders a selected polygon.
