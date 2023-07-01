/*
 * LCD.c
 *
 *  Created on: Feb 5, 2023
 *      Author: aliab
 */


#include "LCD.h"

//For configuring pins needed by diver
 extern GPIO_pinConfig_t pinConfig;

/*======================================================================================
* @Fn			-delay
* @brief		-Creates a small delay
* @param[in]	-The duration of the delay
* @retval		-None
* Note			-None
======================================================================================*/
void delay(uint32_t time){
	uint32_t i,j;
	for(i = 0; i <  time; i++){
		for(j = 0; j <  255; j++);
	}
}

/*======================================================================================
* @Fn			-LCD_KICK
* @brief		-Enables the LCD for commands
* @param[in]	-None
* @retval		-None
* Note			-None
======================================================================================*/
void LCD_KICK(void){
	MCAL_GPIO_writePin(LCD_CTRL, ENABLE_SWITCH, GPIO_PIN_SET);
	delay(50);
	MCAL_GPIO_writePin(LCD_CTRL, ENABLE_SWITCH, GPIO_PIN_RESET);
}

/*======================================================================================
* @Fn			-LCD_INIT
* @brief		-Initializes the LCD for writing
* @param[in]	-None
* @retval		-None
* Note			-None
======================================================================================*/
void LCD_INIT(void){
	delay(20);

//	LCD_isBusy();

	pinConfig.GPIO_pinNumber = RW_SWITCH;
	pinConfig.GPIO_mode = GPIO_MODE_OUTPUT_PP;
	pinConfig.GPIO_output_speed = GPIO_SPEED_10M;
	MCAL_GPIO_init(LCD_CTRL, &pinConfig);

	pinConfig.GPIO_pinNumber = RS_SWITCH;
	pinConfig.GPIO_mode = GPIO_MODE_OUTPUT_PP;
	pinConfig.GPIO_output_speed = GPIO_SPEED_10M;
	MCAL_GPIO_init(LCD_CTRL, &pinConfig);

	pinConfig.GPIO_pinNumber = ENABLE_SWITCH;
	pinConfig.GPIO_mode = GPIO_MODE_OUTPUT_PP;
	pinConfig.GPIO_output_speed = GPIO_SPEED_10M;
	MCAL_GPIO_init(LCD_CTRL, &pinConfig);

	delay(15);

	config_dataOUT_ports();


	LCD_Clear_Screen();

	#ifdef EIGHT_BIT_MODE
	LCD_WRITE_COMMAND(LCD_FUNCTION_8BIT_2LINES);
	#endif


	#ifdef FOUR_BIT_MODE
	LCD_WRITE_COMMAND(0x02);
	LCD_WRITE_COMMAND(LCD_FUNCTION_4BIT_2LINES);
	#endif



	LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);

}


/*======================================================================================
* @Fn			-LCD_Clear_Screen
* @brief		-Clears the LCD form the characters
* @param[in]	-None
* @retval		-None
* Note			-None
======================================================================================*/
void LCD_Clear_Screen(void){
	LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);
}

/*======================================================================================
* @Fn			-LCD_WRITE_COMMAND
* @brief		-Writes a certain command form @ref LCD Commands
* @param[in]	-The command @ref LCD Commands
* @retval		-None
* Note			-None
======================================================================================*/
void LCD_WRITE_COMMAND(unsigned char command){

//	LCD_isBusy();

	#ifdef EIGHT_BIT_MODE
	/*Writing on the port the command while preserving
	 * the other pin`s data*/
	MCAL_GPIO_writePort(LCD_CTRL,((MCAL_GPIO_readPort(LCD_CTRL) & 0xff00) | command));
//	MCAL_GPIO_writePort(LCD_CTRL,command);
	MCAL_GPIO_writePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_writePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
	delay(1);
	LCD_KICK();
	#endif

	#ifdef FOUR_BIT_MODE
	MCAL_GPIO_writePort(LCD_PORT,((MCAL_GPIO_readPort(LCD_PORT) & 0xff0f) | (command & 0xf0)));

	MCAL_GPIO_writePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_writePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
	LCD_KICK();

	delay(100);

	MCAL_GPIO_writePort(LCD_PORT,((MCAL_GPIO_readPort(LCD_PORT) & 0xff0f) | (command << DATA_SHIFT)));

	MCAL_GPIO_writePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_writePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
	LCD_KICK();

	#endif

}

/*======================================================================================
* @Fn			-LCD_WRITE_CHAR
* @brief		-Writes a character on the screen
* @param[in]	-Character to be written
* @retval		-None
* Note			-Not preferred to be used since it does not have the ability to
* 				 sync with the lines of the screen use LCD_WRITE_STRING instead
======================================================================================*/
void LCD_WRITE_CHAR(unsigned char  character){


	#ifdef EIGHT_BIT_MODE

//	LCD_isBusy();

//	MCAL_GPIO_writePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_SET);

	MCAL_GPIO_writePort(LCD_PORT,((MCAL_GPIO_readPort(LCD_PORT) & 0xff00) | character));
//	MCAL_GPIO_writePort(LCD_PORT, character);
	MCAL_GPIO_writePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_SET);

	MCAL_GPIO_writePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
	delay(1);

	LCD_KICK();
	#endif

	#ifdef FOUR_BIT_MODE
	MCAL_GPIO_writePort(LCD_PORT,((MCAL_GPIO_readPort(LCD_PORT) & 0xff0f) | (character & 0xf0)));

	MCAL_GPIO_writePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_SET);

	MCAL_GPIO_writePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);

	LCD_KICK();
	MCAL_GPIO_writePort(LCD_PORT,((MCAL_GPIO_readPort(LCD_PORT) & 0xff0f) | (character << DATA_SHIFT)));

	MCAL_GPIO_writePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_SET);

	MCAL_GPIO_writePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);

	LCD_KICK();
	#endif
}

/*======================================================================================
* @Fn			-LCD_Goto_XY
* @brief		-Moves the cursor to a certain position on the screen
* @param[in]	-The position of the row (line = 0 will be the first row on the screen)
* 				 (line = 1 will be the second row on the screen)
* @param[in]	-The position of the columns in range of 0-15 inclusive
* @retval		-None
* Note			-None
======================================================================================*/
void LCD_Goto_XY(unsigned char line, unsigned char position){

	if (line == 0){
		if ((position >= 0) && (position < 16)){
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW + position);
		}
	}else if (line == 1){
		if ((position >= 0) && (position < 16)){
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_SECOND_ROW + position);
		}
	}

}

/*======================================================================================
* @Fn			-LCD_WRITE_STRING
* @brief		-Writes a string on the screen
* @param[in]	-String to be written
* @retval		-None
* Note			-None
======================================================================================*/
void LCD_WRITE_STRING(char * string){
	static volatile int count = 0;

	while(*string > 0){
		LCD_WRITE_CHAR(*string++);
		++count;
		if (count == 16){
			LCD_Goto_XY(1,0);
		}else if (count == 32){
			LCD_Clear_Screen();
			LCD_Goto_XY(0,0);
			count = 0;
		}
	}
}

/*======================================================================================
* @Fn			-LCD_isBusy
* @brief		-Checks if the screen is busy or not
* @param[in]	-None
* @retval		-None
* Note			-None
======================================================================================*/
void LCD_isBusy(void){
	//Set the port to receive data on the micro-controller (Data direction as input).
	config_dataIN_ports();

	//Read mode
	MCAL_GPIO_writePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_SET);
	MCAL_GPIO_writePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);
	LCD_KICK();

	//Reset Ports as output again
	config_dataOUT_ports();

	MCAL_GPIO_writePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
}

/*======================================================================================
* @Fn			-config_dataIN_ports
* @brief		-Configures the data lines as inputs
* @param[in]	-None
* @retval		-None
* Note			-Helper function DO NOT ATTEMPT TO USE IT ALONE needed by
* 				 LCD_isBusy
======================================================================================*/
void config_dataIN_ports(void){
	//Enabling port A4 as input floating
	pinConfig.GPIO_pinNumber = GPIO_PIN_4;
	pinConfig.GPIO_mode = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_init(LCD_PORT, &pinConfig);

	//Enabling port A5 as input floating
	pinConfig.GPIO_pinNumber = GPIO_PIN_5;
	pinConfig.GPIO_mode = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_init(LCD_PORT, &pinConfig);

	//Enabling port A6 as input floating
	pinConfig.GPIO_pinNumber = GPIO_PIN_6;
	pinConfig.GPIO_mode = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_init(LCD_PORT, &pinConfig);

	//Enabling port A7 as input floating
	pinConfig.GPIO_pinNumber = GPIO_PIN_7;
	pinConfig.GPIO_mode = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_init(LCD_PORT, &pinConfig);

#ifdef EIGHT_BIT_MODE
	//Enabling port A3 as input floating
	pinConfig.GPIO_pinNumber = GPIO_PIN_3;
	pinConfig.GPIO_mode = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_init(LCD_PORT, &pinConfig);

	//Enabling port A2 as input floating
	pinConfig.GPIO_pinNumber = GPIO_PIN_2;
	pinConfig.GPIO_mode = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_init(LCD_PORT, &pinConfig);

	//Enabling port A1 as input floating
	pinConfig.GPIO_pinNumber = GPIO_PIN_1;
	pinConfig.GPIO_mode = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_init(LCD_PORT, &pinConfig);

	//Enabling port A0 as input floating
	pinConfig.GPIO_pinNumber = GPIO_PIN_0;
	pinConfig.GPIO_mode = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_init(LCD_PORT, &pinConfig);
#endif

}

/*======================================================================================
* @Fn			-config_dataOUT_ports
* @brief		-Configures the data lines as outputs
* @param[in]	-None
* @retval		-None
* Note			-Helper function DO NOT ATTEMPT TO USE IT ALONE
======================================================================================*/
void config_dataOUT_ports(void){

	//Enabling port A7 as output
	pinConfig.GPIO_pinNumber = GPIO_PIN_7;
	pinConfig.GPIO_mode = GPIO_MODE_OUTPUT_PP;
	pinConfig.GPIO_output_speed = GPIO_SPEED_10M;
	MCAL_GPIO_init(LCD_PORT, &pinConfig);

	//Enabling port A6 as output
	pinConfig.GPIO_pinNumber = GPIO_PIN_6;
	pinConfig.GPIO_mode = GPIO_MODE_OUTPUT_PP;
	pinConfig.GPIO_output_speed = GPIO_SPEED_10M;
	MCAL_GPIO_init(LCD_PORT, &pinConfig);

	//Enabling port A5 as output
	pinConfig.GPIO_pinNumber = GPIO_PIN_5;
	pinConfig.GPIO_mode = GPIO_MODE_OUTPUT_PP;
	pinConfig.GPIO_output_speed = GPIO_SPEED_10M;
	MCAL_GPIO_init(LCD_PORT, &pinConfig);

	//Enabling port A4 as output
	pinConfig.GPIO_pinNumber = GPIO_PIN_4;
	pinConfig.GPIO_mode = GPIO_MODE_OUTPUT_PP;
	pinConfig.GPIO_output_speed = GPIO_SPEED_10M;
	MCAL_GPIO_init(LCD_PORT, &pinConfig);

#ifdef EIGHT_BIT_MODE
	//Enabling port A3 as output
	pinConfig.GPIO_pinNumber = GPIO_PIN_3;
	pinConfig.GPIO_mode = GPIO_MODE_OUTPUT_PP;
	pinConfig.GPIO_output_speed = GPIO_SPEED_10M;
	MCAL_GPIO_init(LCD_PORT, &pinConfig);

	//Enabling port A2 as output
	pinConfig.GPIO_pinNumber = GPIO_PIN_2;
	pinConfig.GPIO_mode = GPIO_MODE_OUTPUT_PP;
	pinConfig.GPIO_output_speed = GPIO_SPEED_10M;
	MCAL_GPIO_init(LCD_PORT, &pinConfig);

	//Enabling port A1 as output
	pinConfig.GPIO_pinNumber = GPIO_PIN_1;
	pinConfig.GPIO_mode = GPIO_MODE_OUTPUT_PP;
	pinConfig.GPIO_output_speed = GPIO_SPEED_10M;
	MCAL_GPIO_init(LCD_PORT, &pinConfig);

	//Enabling port A0 as output
	pinConfig.GPIO_pinNumber = GPIO_PIN_0;
	pinConfig.GPIO_mode = GPIO_MODE_OUTPUT_PP;
	pinConfig.GPIO_output_speed = GPIO_SPEED_10M;
	MCAL_GPIO_init(LCD_PORT, &pinConfig);
#endif
}
