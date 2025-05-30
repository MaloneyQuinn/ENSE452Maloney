/**
******************************************************************************
* @file           : CLI.c
* @brief          : Source file containing the functions prototyped in CLI.h.
* 					The functions are used to handle the terminal input and
* 					output.
* Author: 		  : Quinn Maloney
* SID:			  : 200431628
******************************************************************************
*/


#include "CLI.h"

/**
* @brief  CLI_Receive takes the user input, displays it to the terminal, and
* 		  saves it inside a buffer to be used when the user submits the enter
* 		  key.
* @param  None
* @retval returns a code based on input. If it is a pedestrian crossing N/S
* 		  1 is returned. If it is a pedestrian crossing E/W 2 is returned.
* 		  If an emergency vehicle is passing on N/S 3 is returned. If an
* 		  emergency vehicle is passing on E/W 4 is returned. Otherwise 0
* 		  is returned to indicate no change.
*/
uint16_t CLI_Receive()
{
	char newLineMessage[] = "Enter a command: ";
	char error[] = "Error: not a valid command. Type 'help' to see commands";
	char help1[] = "enter 'p#' (1-4) to initiate a pedestrian crossing button. ex: p3 .";
	char help2[] = "Enter e followed by the street directions to simulate an emergency vehicle. either ens or eew";
	char newLine = '\n';
	char cr = '\r';
	if (cliRXChar != 0x7F)
		HAL_UART_Transmit(&huart2, (unsigned char *)&cliRXChar, 1, 100);

	if (cliRXChar == 0x0D)
	{
		HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
		if (cliBufferRX[0] == 'p' && cliBufferRX[1] == '1')
		{
			cliRXChar = 0;
			counter = 0;
			HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
			HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);
			for(int x = 0; x < sizeof newLineMessage; x++)
				HAL_UART_Transmit(&huart2, (unsigned char *)&newLineMessage[x], 1, 100);
			return 1;
		}
		else if (cliBufferRX[0] == 'p' && cliBufferRX[1] == '2')
		{
			cliRXChar = 0;
			counter = 0;
			HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
			HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);
			for(int x = 0; x < sizeof newLineMessage; x++)
				HAL_UART_Transmit(&huart2, (unsigned char *)&newLineMessage[x], 1, 100);
			return 2;
		}
		else if (cliBufferRX[0] == 'p' && cliBufferRX[1] == '3')
		{
			cliRXChar = 0;
			counter = 0;
			HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
			HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);
			for(int x = 0; x < sizeof newLineMessage; x++)
				HAL_UART_Transmit(&huart2, (unsigned char *)&newLineMessage[x], 1, 100);
			return 1;
		}
		else if (cliBufferRX[0] == 'p' && cliBufferRX[1] == '4')
		{
			cliRXChar = 0;
			counter = 0;
			HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
			HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);
			for(int x = 0; x < sizeof newLineMessage; x++)
				HAL_UART_Transmit(&huart2, (unsigned char *)&newLineMessage[x], 1, 100);
			return 2;
		}
		else if (cliBufferRX[0] == 'e' && cliBufferRX[1] == 'n' && cliBufferRX[2] == 's')
		{
			cliRXChar = 0;
			counter = 0;
			HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
			HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);
			for(int x = 0; x < sizeof newLineMessage; x++)
				HAL_UART_Transmit(&huart2, (unsigned char *)&newLineMessage[x], 1, 100);
			return 3;
		}
		else if (cliBufferRX[0] == 'e' && cliBufferRX[1] == 'e' && cliBufferRX[2] == 'w')
		{
			cliRXChar = 0;
			counter = 0;
			HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
			HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);
			for(int x = 0; x < sizeof newLineMessage; x++)
				HAL_UART_Transmit(&huart2, (unsigned char *)&newLineMessage[x], 1, 100);
			return 4;
		}
		else if (cliBufferRX[0] == 'h' && cliBufferRX[1] == 'e' && cliBufferRX[2] == 'l' && cliBufferRX[3] == 'p')
		{

			cliRXChar = 0;
			counter = 0;
			for(int x = 0; x < sizeof help1; x++)
				HAL_UART_Transmit(&huart2, (unsigned char *)&help1[x], 1, 100);
			HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
			HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);
			for(int x = 0; x < sizeof help2; x++)
				HAL_UART_Transmit(&huart2, (unsigned char *)&help2[x], 1, 100);
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

/**
* @brief  CLI_Display is used to update the status portion of the display
* 		  and restore the cursor to its spot before the status is updated.
* @param  state: the current state of the system.
* @retval None
*/
void CLI_Display(uint8_t state)
{
	char topMoveCursor[] = "\x1b[0;9H";
	char saveCursor[] = "\x1b[s";
	char restoreCursor[] = "\x1b[u";
	char clearLine[] = "\33[2K\r";
	char newLine = '\n';
	char cr = '\r';
	char northSouthStatus[] = "North-South Light Status: ";
	char eastWestStatus[] = "East-West Light Status: ";
	char turn[] = "Left Turn Signal";
	char green[] = "Green Light";
	char yellow[] = "Yellow Light";
	char red[] = "Red Light";

    for(int x = 0; x < sizeof saveCursor; x++)
    	HAL_UART_Transmit(&huart2, (unsigned char *)&saveCursor[x], 1, 100);
    for(int x = 0; x < sizeof topMoveCursor; x++)
	    HAL_UART_Transmit(&huart2, (unsigned char *)&topMoveCursor[x], 1, 100);
    for(int x = 0; x < sizeof clearLine; x++)
    	    HAL_UART_Transmit(&huart2, (unsigned char *)&clearLine[x], 1, 100);

    if (state == 0 || state == 4)
    {
    	for(int x = 0; x < sizeof northSouthStatus; x++)
    		HAL_UART_Transmit(&huart2, (unsigned char *)&northSouthStatus[x], 1, 100);

    	for(int x = 0; x < sizeof red; x++)
    	    HAL_UART_Transmit(&huart2, (unsigned char *)&red[x], 1, 100);

    	HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
    	HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);
    	for(int x = 0; x < sizeof clearLine; x++)
    		HAL_UART_Transmit(&huart2, (unsigned char *)&clearLine[x], 1, 100);

    	for(int x = 0; x < sizeof eastWestStatus; x++)
    	    HAL_UART_Transmit(&huart2, (unsigned char *)&eastWestStatus[x], 1, 100);

    	for(int x = 0; x < sizeof red; x++)
    		HAL_UART_Transmit(&huart2, (unsigned char *)&red[x], 1, 100);
    }

    else if (state == 1)
        {
        	for(int x = 0; x < sizeof northSouthStatus; x++)
        		HAL_UART_Transmit(&huart2, (unsigned char *)&northSouthStatus[x], 1, 100);

        	for(int x = 0; x < sizeof turn; x++)
        	    HAL_UART_Transmit(&huart2, (unsigned char *)&turn[x], 1, 100);

        	HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
        	HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);
        	for(int x = 0; x < sizeof clearLine; x++)
        		HAL_UART_Transmit(&huart2, (unsigned char *)&clearLine[x], 1, 100);

        	for(int x = 0; x < sizeof eastWestStatus; x++)
        	    HAL_UART_Transmit(&huart2, (unsigned char *)&eastWestStatus[x], 1, 100);

        	for(int x = 0; x < sizeof red; x++)
        		HAL_UART_Transmit(&huart2, (unsigned char *)&red[x], 1, 100);
        }

    else if (state == 2)
	   {
		for(int x = 0; x < sizeof northSouthStatus; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&northSouthStatus[x], 1, 100);

		for(int x = 0; x < sizeof green; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&green[x], 1, 100);

		HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
		HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);
		for(int x = 0; x < sizeof clearLine; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&clearLine[x], 1, 100);

		for(int x = 0; x < sizeof eastWestStatus; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&eastWestStatus[x], 1, 100);

		for(int x = 0; x < sizeof red; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&red[x], 1, 100);
	   }

    else if (state == 3)
	   {
		for(int x = 0; x < sizeof northSouthStatus; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&northSouthStatus[x], 1, 100);

		for(int x = 0; x < sizeof yellow; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&yellow[x], 1, 100);

		HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
		HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);
		for(int x = 0; x < sizeof clearLine; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&clearLine[x], 1, 100);

		for(int x = 0; x < sizeof eastWestStatus; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&eastWestStatus[x], 1, 100);

		for(int x = 0; x < sizeof red; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&red[x], 1, 100);
	   }

    else if (state == 5)
	   {
		for(int x = 0; x < sizeof northSouthStatus; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&northSouthStatus[x], 1, 100);

		for(int x = 0; x < sizeof red; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&red[x], 1, 100);

		HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
		HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);
		for(int x = 0; x < sizeof clearLine; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&clearLine[x], 1, 100);

		for(int x = 0; x < sizeof eastWestStatus; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&eastWestStatus[x], 1, 100);

		for(int x = 0; x < sizeof turn; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&turn[x], 1, 100);
	   }

    else if (state == 6)
	   {
		for(int x = 0; x < sizeof northSouthStatus; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&northSouthStatus[x], 1, 100);

		for(int x = 0; x < sizeof red; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&red[x], 1, 100);

		HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
		HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);
		for(int x = 0; x < sizeof clearLine; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&clearLine[x], 1, 100);

		for(int x = 0; x < sizeof eastWestStatus; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&eastWestStatus[x], 1, 100);

		for(int x = 0; x < sizeof green; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&green[x], 1, 100);
	   }

    else if (state == 7)
	   {
		for(int x = 0; x < sizeof northSouthStatus; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&northSouthStatus[x], 1, 100);

		for(int x = 0; x < sizeof red; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&red[x], 1, 100);

		HAL_UART_Transmit(&huart2, (unsigned char *)&newLine, 1, 100);
		HAL_UART_Transmit(&huart2, (unsigned char *)&cr, 1, 100);
		for(int x = 0; x < sizeof clearLine; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&clearLine[x], 1, 100);

		for(int x = 0; x < sizeof eastWestStatus; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&eastWestStatus[x], 1, 100);

		for(int x = 0; x < sizeof yellow; x++)
			HAL_UART_Transmit(&huart2, (unsigned char *)&yellow[x], 1, 100);
	   }

    for(int x = 0; x < sizeof restoreCursor; x++)
	    HAL_UART_Transmit(&huart2, (unsigned char *)&restoreCursor[x], 1, 100);

}

