/*
 * lights.h
 *
 *  Created on: Nov 22, 2024
 *      Author: qkmal
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
