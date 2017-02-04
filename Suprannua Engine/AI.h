/**
 * Artificial Intelligence
 *
 * Author: Jean-Louis Haywood
 *
 * Manipulates polygon or block velocity or position data based on problem solving algorithms to simulate game AI.
 */

#pragma once

void AI_avoid(unsigned char agent, int agentNumber, unsigned char object, int objectNumber, double range);	
void AI_catch(unsigned char agent, int agentNumber, unsigned char object, int objectNumber, bool followX, bool followY);	//Agent moves anticipating approaching target.
void AI_fly(unsigned char agent, int agentNumber, double height);
void AI_follow(unsigned char agent, int agentNumber, unsigned char object, int objectNumber, double detectionRange, double targetRange);
void AI_jump(unsigned char agent, int agentNumber, double jumpVelocity);
void AI_mimic(unsigned char agent, int agentNumber, unsigned char object, int objectNumber);	//Copies the movement of another agent.
void AI_shoot(unsigned char agent, int agentNumber, unsigned char object, int objectNumber);	//Agent fires projectile at a specified object.
void AI_spin(unsigned char agent, int agentNumber, bool direction, double amount);				//Agent rotates.
void AI_travel(unsigned char agent, int agentNumber, double toXPosition, double toYPosition, double Velocity); //Agent moves to a point.
