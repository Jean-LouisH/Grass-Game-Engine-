/**
 * Geometry
 *
 * Author: Jean-Louis Haywood
 *
 * Handles the mathematics behind 2D polygon and rectangle plotting, spatial data and transforms.
 */

#pragma once

/*| Calculates the angle between the two objects against the x and y grid.*/
double geometry_findAngleBetween(unsigned char firstObject,
	int firstObjectNumber,
	unsigned char secondObject,
	int secondObjectNumber);

/*| Finds the hypotenuse between object centres as a right angled triangle*/
double geometry_findDistance(unsigned char firstObject,
	int firstObjectNumber,
	unsigned char secondObject,
	int secondObjectNumber);

/*| Plot block points based on centre, height and width.*/
void geometry_plotBlock(int objectNumber);

/*| Plot polygon points based on number of sides, and radius.*/
void geometry_plotPolygon(int objectNumber);

/*| Update points based on velocity and angular displacement.*/
void geometry_transform();
