/**
 * Input
 *
 * Author: Jean-Louis Haywood
 *
 * Handles special and regular key presses passed from the input callbacks.
 */

#pragma once

bool input_isPressed(unsigned char input);
bool input_isDoublePressed(unsigned char input, int eventReference);
