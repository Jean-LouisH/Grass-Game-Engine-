/**
 * Game
 *
 * Author: Jean-Louis Haywood
 *
 * Links the Suprannua game loop to a user made game which uses the Suprannua framework functions.
 */

#pragma once

 /*| Sets up all the game assets before running the script.*/
void initGameAssets();

/*| Performs actions based on keyboard inputs in buffer.*/
void readInput();

/*| Contains game or simulation logic.*/
void runGameLogic();
