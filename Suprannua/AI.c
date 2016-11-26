#include "Suprannua.h"

void AI_spin(unsigned char agent, int agentNumber, bool direction, double amount)
{
    switch(agent)
    {
        case POLYGON:   polygon[agentNumber].properties.angle +=
                        ((direction * 2) - 1) * (amount / (FRAME_RATE));
        break;
    }
}

void AI_follow(unsigned char agent, int agentNumber, unsigned char object, int objectNumber)
{

}

void AI_avoid(unsigned char agent, int agentNumber, unsigned char object, int objectNumber)
{

}

void AI_shoot(unsigned char agent, int agentNumber, unsigned char object, int objectNumber)
{

}

void AI_mimic(unsigned char agent, int agentNumber, unsigned char object, int objectNumber)
{

}

void AI_signal(unsigned char message)
{

}

void AI_listen()
{

}

void AI_catch(unsigned char agent, int agentNumber, unsigned char object, int objectNumber)
{

}

void AI_travel(unsigned char agent, int agentNumber, double toXPosition, double toYPosition, double Velocity)
{

}