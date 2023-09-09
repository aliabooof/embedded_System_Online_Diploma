/*
 * KEYPAD.C
 *
 *  Created on: Feb 5, 2023
 *      Author: aliab
 */

#include "../inc/KEYPAD.h"



int KEYPAD_ROWS[]={R0,R1,R2,R3};

int KEYPAD_COLS[]={C0,C1,C2,C3};

void KEYPAD_INIT(){
	GPIO_PIN_Config_t* PinCfg ;
	PinCfg->GPIO_PinNumber = R0;
	PinCfg->GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	PinCfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, PinCfg);

	PinCfg->GPIO_PinNumber = R1;
	PinCfg->GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	PinCfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, PinCfg);
	PinCfg->GPIO_PinNumber = R2;
	PinCfg->GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	PinCfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, PinCfg);

	PinCfg->GPIO_PinNumber = R3;
	PinCfg->GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	PinCfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, PinCfg);

	PinCfg->GPIO_PinNumber = C0;
	PinCfg->GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	PinCfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, PinCfg);

	PinCfg->GPIO_PinNumber = C1;
	PinCfg->GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	PinCfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, PinCfg);

	PinCfg->GPIO_PinNumber = C2;
	PinCfg->GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	PinCfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, PinCfg);

	PinCfg->GPIO_PinNumber = C3;
	PinCfg->GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	PinCfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, PinCfg);



	MCAL_GPIO_WritePort(GPIOB, 0xFF);

}

char KEYPAD_GETCHAR(){

	int i,j;
	for(i=0;i<4;i++){
		MCAL_GPIO_WritePin(GPIOB, KEYPAD_COLS[0], GPIO_PIN_SET);
		MCAL_GPIO_WritePin(GPIOB, KEYPAD_COLS[1], GPIO_PIN_SET);
		MCAL_GPIO_WritePin(GPIOB, KEYPAD_COLS[2], GPIO_PIN_SET);
		MCAL_GPIO_WritePin(GPIOB, KEYPAD_COLS[3], GPIO_PIN_SET);
		MCAL_GPIO_WritePin(GPIOB, KEYPAD_COLS[i],GPIO_PIN_RESET);

		for(j=0;j<4;j++){
			if(MCAL_GPIO_ReadPin(GPIOB, KEYPAD_ROWS[j])==0){
				while(MCAL_GPIO_ReadPin(GPIOB, KEYPAD_ROWS[j]) == 0);

				switch (i) {
				case (0):{
					if (j == 0)
						return '7';
					else if (j == 1)
						return '4';
					else if (j == 2)
						return '1';
					else if (j == 3)
						return '?';
				}
				break;
				case (1):{
					if (j == 0)
						return '8';
					else if (j == 1)
						return '5';
					else if (j == 2)
						return '2';
					else if (j == 3)
						return '0';
				}
				break;
				case (2):{
					if (j == 0)
						return '9';
					else if (j == 1)
						return '6';
					else if (j == 2)
						return '3';
					else if (j == 3)
						return '=';
				}
				break;
				case (3):{
					if (j == 0)
						return '/';
					else if (j == 1)
						return '*';
					else if (j == 2)
						return '-';
					else if (j == 3)
						return '+';
				}
				break;
				}
			}
		}
	}
	return 'A';
}


