/*
 * KEYPAD.C
 *
 *  Created on: Feb 5, 2023
 *      Author: aliab
 */

#include "KEYPAD.h"

int keypadRows[] = {R0,R1,R2,R3};
int keypadCols[] = {C0,C1,C2,C3};

//For configuring pins needed by diver
GPIO_pinConfig_t pinConfig;


void KEYPAD_INIT(){
	//Set the upper keypad port as as input
	pinConfig.GPIO_pinNumber = R0;
	pinConfig.GPIO_mode = GPIO_MODE_OUTPUT_PP;
	pinConfig.GPIO_output_speed = GPIO_SPEED_10M;
	MCAL_GPIO_init(keypadPORT, &pinConfig);

	pinConfig.GPIO_pinNumber = R1;
	pinConfig.GPIO_mode = GPIO_MODE_OUTPUT_PP;
	pinConfig.GPIO_output_speed = GPIO_SPEED_10M;
	MCAL_GPIO_init(keypadPORT, &pinConfig);

	pinConfig.GPIO_pinNumber = R2;
	pinConfig.GPIO_mode = GPIO_MODE_OUTPUT_PP;
	pinConfig.GPIO_output_speed = GPIO_SPEED_10M;
	MCAL_GPIO_init(keypadPORT, &pinConfig);

	pinConfig.GPIO_pinNumber = R3;
	pinConfig.GPIO_mode = GPIO_MODE_OUTPUT_PP;
	pinConfig.GPIO_output_speed = GPIO_SPEED_10M;
	MCAL_GPIO_init(keypadPORT, &pinConfig);



	//Set the lower keypad port as output
	pinConfig.GPIO_pinNumber = C0;
	pinConfig.GPIO_mode = GPIO_MODE_OUTPUT_PP;
	pinConfig.GPIO_output_speed = GPIO_SPEED_10M;
	MCAL_GPIO_init(keypadPORT, &pinConfig);

	pinConfig.GPIO_pinNumber = C1;
	pinConfig.GPIO_mode = GPIO_MODE_OUTPUT_PP;
	pinConfig.GPIO_output_speed = GPIO_SPEED_10M;
	MCAL_GPIO_init(keypadPORT, &pinConfig);

	pinConfig.GPIO_pinNumber = C2;
	pinConfig.GPIO_mode = GPIO_MODE_OUTPUT_PP;
	pinConfig.GPIO_output_speed = GPIO_SPEED_10M;
	MCAL_GPIO_init(keypadPORT, &pinConfig);

	pinConfig.GPIO_pinNumber = C3;
	pinConfig.GPIO_mode = GPIO_MODE_OUTPUT_PP;
	pinConfig.GPIO_output_speed = GPIO_SPEED_10M;
	MCAL_GPIO_init(keypadPORT, &pinConfig);

	MCAL_GPIO_writePort(keypadPORT,((MCAL_GPIO_readPort(keypadPORT) & 0xff00) | (0xff)));
	MCAL_GPIO_writePin(keypadPORT, C3, GPIO_PIN_SET);
}
char KEYPAD_GET_CHAR(){
	int i,j;
	for (i = 0; i < 4 ; i++){
		MCAL_GPIO_writePin(keypadPORT, C0, GPIO_PIN_SET);
		MCAL_GPIO_writePin(keypadPORT, C1, GPIO_PIN_SET);
		MCAL_GPIO_writePin(keypadPORT, C2, GPIO_PIN_SET);
		MCAL_GPIO_writePin(keypadPORT, C3, GPIO_PIN_SET);

		MCAL_GPIO_writePin(keypadPORT, keypadCols[i], GPIO_PIN_RESET);

		for (j = 0; j < 4 ; j++){

			if (MCAL_GPIO_readPin(keypadPORT, keypadRows[j]) == GPIO_PIN_RESET){
				while(MCAL_GPIO_readPin(keypadPORT, keypadRows[j]) == GPIO_PIN_RESET);

				switch(i){
					case (0):{
						if		(j == 0)	return '7';
						else if (j == 1)	return '4';
						else if (j == 2)	return '1';
						else if (j == 3)	return '!';
						break;
					}
					case (1):{
						if		(j == 0)	return '8';
						else if (j == 1)	return '5';
						else if (j == 2)	return '2';
						else if (j == 3)	return '0';
						break;
					}
					case (2):{
						if		(j == 0)	return '9';
						else if (j == 1)	return '6';
						else if (j == 2)	return '3';
						else if (j == 3)	return '=';
						break;
					}
					case (3):{
						if		(j == 0)	return '/';
						else if (j == 1)	return '*';
						else if (j == 2)	return '-';
						else if (j == 3)	return '+';
						break;
					}

				}
			}
		}
	}

	return 'N';
}
