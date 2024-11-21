/*
 * CLI.h
 *
 *  Created on: Nov 14, 2024
 *      Author: qkmal
 */

#ifndef INC_CLI_H_
#define INC_CLI_H_


/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include <stdio.h>

//Global Variables
extern UART_HandleTypeDef huart2;
extern uint8_t cliRXChar;
extern uint8_t cliBufferRX[30];
extern int counter;


//Functions
uint16_t CLI_Receive();

void CLI_Display(uint16_t);


#endif /* INC_CLI_H_ */

