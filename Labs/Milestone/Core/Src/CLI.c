/*
 * CLI.c
 *
 *  Created on: Nov 14, 2024
 *      Author: qkmal
 */


#include "CLI.h"

uint16_t CLI_Receive()
{
	char newLineMessage[] = "Enter a command: ";
	char error[] = "Error: not a valid command. Type 'help' to see commands";
	char help[] = "'period ' followed by a 4 digit integer will change the interval of the LED. ex: period 0300 for 300";
	char newLine = '\n';
	char cr = '\r';
	if (cliRXChar != 0x7F)
		HAL_UART_Transmit(&huart2, (unsigned char *)&cliRXChar, 1, 100);

	if (cliRXChar == 0x0D)
	{
		HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
		if (cliBufferRX[0] == 'p' && cliBufferRX[1] == 'e' && cliBufferRX[2] == 'r' && cliBufferRX[3] == 'i'
				&& cliBufferRX[4] == 'o' && cliBufferRX[5] == 'd')
		{
			cliRXChar = 0;
			counter = 0;
			uint16_t newPeriod = 0;
			uint16_t newPeriodInt[4];
			int y = 0;
			for (int x = 7; x < 11; x ++)
			{
				if (cliBufferRX[x] != '/0')
				{
					newPeriodInt[y] = cliBufferRX[x] - 48;
					y++;
				}
			}
			for (int i = 0; i < 4; i++)
			{
				if(newPeriodInt[i] != 65488)
					newPeriod = 10 * newPeriod + newPeriodInt[i];
			}
			HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
			HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);
			for(int x = 0; x < sizeof newLineMessage; x++)
				HAL_UART_Transmit(&huart2, (unsigned char *)&newLineMessage[x], 1, 100);
			return newPeriod;
		}
		else if (cliBufferRX[0] == 'h' && cliBufferRX[1] == 'e' && cliBufferRX[2] == 'l' && cliBufferRX[3] == 'p')
		{

			cliRXChar = 0;
			counter = 0;
			for(int x = 0; x < sizeof help; x++)
				HAL_UART_Transmit(&huart2, (unsigned char *)&help[x], 1, 100);
			HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
			HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
			HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);
		}
		else
		{
			cliRXChar = 0;
			counter = 0;
			for(int x = 0; x < sizeof error; x++)
					HAL_UART_Transmit(&huart2, (unsigned char *)&error[x], 1, 100);
			HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
			HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
			HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);
		}
		for(int x = 0; x < sizeof newLineMessage; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&newLineMessage[x], 1, 100);
		for(size_t i = 0; i < sizeof cliBufferRX; i++)
			cliBufferRX[i] = 0;
	}
	else if (cliRXChar == 0x7F)
	{
		if (counter > 0)
		{
			HAL_UART_Transmit(&huart2, (unsigned char *)&cliRXChar, 1, 100);
			counter --;
			cliBufferRX[counter] = 0;
			cliRXChar = 0;
		}
	}
	else
	{
		cliBufferRX[counter] = cliRXChar;
		cliRXChar = 0;
		counter++;
	}
	return 0;
}

void CLI_Display(uint16_t period)
{
	char charPeriod[4];
	char topMoveCursor[] = "\x1b[0;9H";
	char saveCursor[] = "\x1b[s";
	char restoreCursor[] = "\x1b[u";
	char clearLine[] = "\33[2K\r";
	char periodMessage[] = "Period ";

	sprintf (charPeriod, "%d", period);
    for(int x = 0; x < sizeof saveCursor; x++)
    	HAL_UART_Transmit(&huart2, (unsigned char *)&saveCursor[x], 1, 100);
    for(int x = 0; x < sizeof topMoveCursor; x++)
	    HAL_UART_Transmit(&huart2, (unsigned char *)&topMoveCursor[x], 1, 100);
    for(int x = 0; x < sizeof clearLine; x++)
    	    HAL_UART_Transmit(&huart2, (unsigned char *)&clearLine[x], 1, 100);
    for(int x = 0; x < sizeof periodMessage; x++)
    	  HAL_UART_Transmit(&huart2, (unsigned char *)&periodMessage[x], 1, 100);
    for(int x = 0; x < sizeof charPeriod; x++)
	    HAL_UART_Transmit(&huart2, (unsigned char *)&charPeriod[x], 1, 100);
    for(int x = 0; x < sizeof restoreCursor; x++)
	    HAL_UART_Transmit(&huart2, (unsigned char *)&restoreCursor[x], 1, 100);

}

