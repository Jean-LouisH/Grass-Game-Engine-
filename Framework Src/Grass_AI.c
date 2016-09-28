#include "GrassRoots_Framework.h"

void AI_spin(unsigned char object, int objectNumber, unsigned char direction, double amount)
{
    switch(object)
    {
        case POLYGON: polygon[objectNumber].properties.angle += ((direction * 2) - 1) * amount;
        break;
    }
}
