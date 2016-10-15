#include "Definitions.h"
#include "AI.h"

void AI_spin(unsigned char agent, int agentNumber, unsigned char direction, double amount)
{
    switch(agent)
    {
        case POLYGON: polygon[agentNumber].properties.angle += ((direction * 2) - 1) * amount;
        break;
    }
}
