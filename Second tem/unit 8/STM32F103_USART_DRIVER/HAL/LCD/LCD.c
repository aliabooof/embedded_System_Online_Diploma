/*
 * LCD.c
 *
 *  Created on: Feb 5, 2023
 *      Author: aliab
 */


#include "../inc/LCD.h"

void delay_ms(uint32_t time) {
	uint32_t i, j;
	for (i = 0; i < time; i++)
		for (j = 0; j < 255; j++);
}

void LCD_GOTO_XY(unsigned char line, unsigned char position){
	if(line==0){
		if(position<16 && position>=0){
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW + position);
		}
	}
	if(line == 1){
		if(position<16 && position>=0){
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_SECOND_ROW + position);
		}
	}
}

void LCD_clearscreen(){
	LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);
}

void LCD_kick(){
	MCAL_GPIO_WritePin(LCD_PORT, E_SWITCH,GPIO_PIN_SET);
	delay_ms(50);
	MCAL_GPIO_WritePin(LCD_PORT, E_SWITCH,GPIO_PIN_RESET);

}

void  LCD_PORT_OUT(){

	GPIO_PIN_Config_t* PinCfg ;

	PinCfg->GPIO_PinNumber = GPIO_PIN_0;
	PinCfg->GPIO_PinMode= GPIO_MODE_OUTPUT_PP;
	PinCfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, PinCfg);

	PinCfg->GPIO_PinNumber = GPIO_PIN_1;
	PinCfg->GPIO_PinMode= GPIO_MODE_OUTPUT_PP;
	PinCfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, PinCfg);

	PinCfg->GPIO_PinNumber = GPIO_PIN_2;
	PinCfg->GPIO_PinMode= GPIO_MODE_OUTPUT_PP;
	PinCfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, PinCfg);

	PinCfg->GPIO_PinNumber = GPIO_PIN_3;
	PinCfg->GPIO_PinMode= GPIO_MODE_OUTPUT_PP;
	PinCfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, PinCfg);

	PinCfg->GPIO_PinNumber = GPIO_PIN_4;
	PinCfg->GPIO_PinMode= GPIO_MODE_OUTPUT_PP;
	PinCfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, PinCfg);

	PinCfg->GPIO_PinNumber = GPIO_PIN_5;
	PinCfg->GPIO_PinMode= GPIO_MODE_OUTPUT_PP;
	PinCfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, PinCfg);

	PinCfg->GPIO_PinNumber = GPIO_PIN_6;
	PinCfg->GPIO_PinMode= GPIO_MODE_OUTPUT_PP;
	PinCfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, PinCfg);

	PinCfg->GPIO_PinNumber = GPIO_PIN_7;
	PinCfg->GPIO_PinMode= GPIO_MODE_OUTPUT_PP;
	PinCfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, PinCfg);

}

void  LCD_PORT_IN(){
	GPIO_PIN_Config_t* PinCfg ;


	PinCfg->GPIO_PinNumber = GPIO_PIN_0;
	PinCfg->GPIO_PinMode= GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_PORT, PinCfg);

	PinCfg->GPIO_PinNumber = GPIO_PIN_1;
	PinCfg->GPIO_PinMode= GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_PORT, PinCfg);

	PinCfg->GPIO_PinNumber = GPIO_PIN_2;
	PinCfg->GPIO_PinMode= GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_PORT, PinCfg);

	PinCfg->GPIO_PinNumber = GPIO_PIN_3;
	PinCfg->GPIO_PinMode= GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_PORT, PinCfg);

	PinCfg->GPIO_PinNumber = GPIO_PIN_4;
	PinCfg->GPIO_PinMode= GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_PORT, PinCfg);

	PinCfg->GPIO_PinNumber = GPIO_PIN_5;
	PinCfg->GPIO_PinMode= GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_PORT, PinCfg);

	PinCfg->GPIO_PinNumber = GPIO_PIN_6;
	PinCfg->GPIO_PinMode= GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_PORT, PinCfg);

	PinCfg->GPIO_PinNumber = GPIO_PIN_7;
	PinCfg->GPIO_PinMode= GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_PORT, PinCfg);
}

/**================================================================
 * @Fn			-LCD_INIT
 * @brief 		-Initialize LCD.
 * @param [in] 	-
 * @param [in] 	-
 *
 * @param [out] - none
 * @retval	 	- none
 * Note
 *
 */
void LCD_INIT(){
	GPIO_PIN_Config_t* PinCfg ;

	delay_ms(20);
	// make RW , RS and E switches as input
	PinCfg->GPIO_PinNumber = RW_SWITCH;
	PinCfg->GPIO_PinMode= GPIO_MODE_OUTPUT_PP;
	PinCfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, PinCfg);

	PinCfg->GPIO_PinNumber = RS_SWITCH;
	PinCfg->GPIO_PinMode= GPIO_MODE_OUTPUT_PP;
	PinCfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, PinCfg);

	PinCfg->GPIO_PinNumber = E_SWITCH;
	PinCfg->GPIO_PinMode= GPIO_MODE_OUTPUT_PP;
	PinCfg->GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, PinCfg);


	LCD_PORT_OUT();

	MCAL_GPIO_WritePin(LCD_PORT, RS_SWITCH,GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_PORT, RW_SWITCH,GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_PORT, E_SWITCH,GPIO_PIN_RESET);


	delay_ms(15);
	LCD_clearscreen();

	LCD_WRITE_COMMAND(LCD_FUNCTION_8BIT_2LINES);
	LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);



}

/**================================================================
 * @Fn			-LCD_check_lcd_isbusy
 * @brief 		-Checks LCD if its busy.
 * @param [in] 	-
 * @param [in] 	-
 *
 * @param [out] - none
 * @retval	 	- none
 * Note
 *
 */
void LCD_check_lcd_isbusy(void){

	LCD_PORT_IN();

	MCAL_GPIO_WritePin(LCD_PORT, RW_SWITCH,GPIO_PIN_SET);
	MCAL_GPIO_WritePin(LCD_PORT, RS_SWITCH,GPIO_PIN_RESET);

	LCD_kick();
	MCAL_GPIO_WritePin(LCD_PORT, RW_SWITCH,GPIO_PIN_RESET);

}

/**================================================================
 * @Fn			-LCD_WRITE_COMMAND
 * @brief 		-sends commands to the lcd .
 * @param [in] 	- commands specified @ref LCD_MODES
 * @param [out] - none
 * @retval	 	- none
 * Note
 *
 */
void LCD_WRITE_COMMAND(unsigned char command){
//	LCD_check_lcd_isbusy();


	MCAL_GPIO_WritePort(LCD_PORT, command);
	MCAL_GPIO_WritePin(LCD_PORT, RW_SWITCH,GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_PORT, RS_SWITCH,GPIO_PIN_RESET);
	delay_ms(1);
	LCD_kick();
}

/**================================================================
 * @Fn			-LCD_WRITE_CHAR
 * @brief 		-sends char to the lcd .
 * @param [in] 	- character  single character
 * @param [out] - none
 * @retval	 	- none
 * Note
 *
 */
void LCD_WRITE_CHAR(unsigned char character){
	//	LCD_check_lcd_isbusy();

	LCD_PORT_OUT();
	MCAL_GPIO_WritePort(LCD_PORT, character);
	MCAL_GPIO_WritePin(LCD_PORT, RW_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_PORT, RS_SWITCH, GPIO_PIN_SET);
	delay_ms(1);
	LCD_kick();

}

/**================================================================
 * @Fn			-LCD_WRITE_STRING
 * @brief 		-sends string to the lcd .
 * @param [in] 	- string
 * @param [out] - none
 * @retval	 	- none
 * Note
 *
 */
void LCD_WRITE_STRING(char* string){

	int count =0;
	while(*string >0){

		count++;
		LCD_WRITE_CHAR(*string++);

		if(count==16){
			LCD_GOTO_XY(1, 0);
		}
		if(count==32||count==33){
			LCD_clearscreen();
			LCD_GOTO_XY(0, 0);
			count = 0 ;
		}
	}

}

