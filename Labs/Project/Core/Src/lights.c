/**
******************************************************************************
* @file           : lights.c
* @brief          : Source file containing the functions prototyped in
* 					lights.h. The purpose of the functions in this file is to
* 					handle the state switching logic alongside the
* 					Change_Light thread.
* Author: 		  : Quinn Maloney
* SID:			  : 200431628
******************************************************************************
* The Pin out for the lights is as follows:
*
*		Red N/S			: GPIOA_PIN_0
*		Yellow N/S		: GPIOA_PIN_1
*		Green N/S		: GPIOA_PIN_4
*		Turn N/S		: GPIOB_PIN_0
*		Turn E/W		: GPIOA_PIN_10
*		Green E/W		: GPIOB_PIN_5
*		Yellow E/W		: GPIOB_PIN_4
*		Red E/W			: GPIOB_PIN_10
*
* These values can also be found labeled inside Project.ioc.
*
******************************************************************************
*/

#include "lights.h"

/**
* @brief  lightStateChange returns the appropriate state either the next or
* 		  same state that it is currently in depending on multiple factors.
* @param  state: the current state of the system.
* 		  counter: the current state of the state counter. used for timing
* 		  pedestrianNS: either 0 for no or 1 for yes indicating a pedestrian
* 		  crossing the N/S street.
* 		  pedestrianEW: either 0 for no or 1 for yes indicating a pedestrian
* 		  crossing the E/W street.
* 		  emergencyNS: either 0 for no or 1 for yes indicating an emergency
* 		  vehicle moving on the N/S street.
* 		  emergencyEW: either 0 for no or 1 for yes indicating an emergency
* 		  vehicle moving on the E/W street.
* @retval state: the updated correct state.
*/
uint8_t lightStateChange(uint8_t state, uint16_t counter, uint8_t pedestrianNS, uint8_t pedestrianEW, uint8_t emergencyNS, uint8_t emergencyEW)
{
	if(emergencyNS == 1)
		return (state = 2);
	if(emergencyEW == 1)
		return (state = 6);
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

/**
* @brief  lightPhysicalChange changes the pins of the breadboard LED lights
* 		  according to the state that the system is in.
* @param  state: the current state of the system.
* @retval None
*/
void lightPhysicalChange(uint8_t state)
{
	if (state == 0 || state == 4)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
	}
	else if (state == 1)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
	}
	else if (state == 2)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
	}
	else if (state == 3)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
	}
	else if (state == 5)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_10);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
	}
	else if (state == 6)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
	}
	else if (state == 7)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
	}
}

/**
* @brief  maintenanceMode toggles the red LED lights on the breadboard
* 		  used when in maintenance mode.
* @param  None
* @retval None
*/
void maintenanceMode()
{
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_10);
}

/**
* @brief  startMaintenanceMode preps the system for maintenance mode by
* 		  setting all the lights to off except for the red lights.
* @param  None
* @retval None
*/
void startMaintenanceMode()
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
}
