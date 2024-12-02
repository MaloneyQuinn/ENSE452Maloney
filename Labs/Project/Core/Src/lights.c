/*
 * lights.c
 *
 *  Created on: Nov 22, 2024
 *      Author: qkmal
 */

#include "lights.h"

uint8_t lightStateChange(uint8_t state, uint16_t counter, uint8_t pedestrianNS, uint8_t pedestrianEW)
{
	if (state == 0 && counter >= 3)
		return (state + 1);
	else if (state == 1 && counter >= 5)
		return (state + 1);
	else if (state == 2 && counter >= 10)
		return (state + 1);
	else if (state == 2 && counter >= 5 && pedestrianNS == 1)
		return (state + 1);
	else if (state == 3 && counter >= 3)
		return (state + 1);
	else if (state == 4 && counter >= 3)
		return (state + 1);
	else if (state == 5 && counter >= 5)
		return (state + 1);
	else if (state == 6 && counter >= 10)
		return (state + 1);
	else if (state == 6 && counter >= 5 && pedestrianEW == 1)
		return (state + 1);
	else if (state == 7 && counter >= 3)
		return 0;
	else
		return state;
}
