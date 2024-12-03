/**
******************************************************************************
* @file           : lights.h
* @brief          : header for the lights.c file. Contains prototypes for the
* 					functions in lights.c.
* Author: 		  : Quinn Maloney
* SID:			  : 200431628
******************************************************************************
*/

#ifndef INC_LIGHTS_H_
#define INC_LIGHTS_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include <stdio.h>

//Functions
uint8_t lightStateChange(uint8_t, uint16_t, uint8_t, uint8_t, uint8_t, uint8_t);
void lightPhysicalChange(uint8_t);
void maintenanceMode();
void startMaintenanceMode();

#endif /* INC_LIGHTS_H_ */
