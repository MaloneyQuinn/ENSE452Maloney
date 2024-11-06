/*
 * timer.c
 *
 *  Created on: Nov 6, 2024
 *      Author: qkmal
 */

#include "timer.h"

int16_t timer_start()
{
	return __HAL_TIM_GET_COUNTER(&htim4);
}

uint16_t timer_stop(uint16_t initial)
{
	uint16_t end = __HAL_TIM_GET_COUNTER(&htim4);
	uint16_t result = initial - end;
	return result;
}

int32_t random_32bit()
{
	int32_t value;
	do
	{
		value = rand();
	} while(value == 0);
	return value;
}

int64_t random_64bit()
{
	int64_t value;
	do
	{
		value = rand();
	} while(value == 0);
	return value;
}

char random_byte()
{
	return rand();
}

void run_test()
{
	uint32_t value1;
	uint32_t value2;
	volatile uint16_t timerInitial = 0;
	volatile uint16_t timerFinal = 0;
	uint16_t results[100];
	uint16_t average = 0;
	char charAverage[3];

	for(int i = 0; i < 100; i++)
	{
		value1 = random_32bit();
		value2 = random_32bit();
		timerInitial = timer_start();
		value1 = value1 + value2;
		timerFinal = timer_stop(timerInitial);
		results[i] = timerFinal;
	}
	for(int i = 0; i < 100; i++)
	{
		average += results[i];
	}
	average = average / 100;
	sprintf (charAverage, "%d", average);
	for(int x = 0; x < sizeof charAverage; x++)
		HAL_UART_Transmit(&huart2, (unsigned char *)&charAverage[x], 1, 100);
}
