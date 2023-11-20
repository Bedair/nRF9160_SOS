/**********************************************************************
* File Name : IoHwAbs_LED.h
* 
* Description : Header file for the component responsible for controlling
*               the LEDs
*
* Author : Mohamed Bedair
*
* Date : 20 Nov 2023
*
**********************************************************************/


#ifndef IOHWABS_LED_H
#define IOHWABS_LED_H


typedef enum{
    LED_0 = 0,
    LED_1,
    LED_2,
    LED_3,
    TOTAL_LEDS_COUNT
}LEDs_Type;


typedef enum{
    LED_OFF = 0,
    LED_ON  = 1
}LED_State_Type;

/*
* Funcation Name : IoHwAbs_LED_Init
* Description    : Used to initialize all the LEDs on the Board
* Parameters     : NA
* Return         : NA
*/
void IoHwAbs_LED_Init(void);


/*
* Funcation Name : IoHwAbs_LED_Set_State
* Description    : Used to update the State of the Board LED
* Parameters     : LED ID, LED State
* Return         : NA
*/
void IoHwAbs_LED_Set_State(LEDs_Type led, LED_State_Type state);



/*
* Funcation Name : IoHwAbs_LED_Toggle
* Description    : Used to toggle Board LED
* Parameters     : LED number
* Return         : NA
*/
void IoHwAbs_LED_Toggle(LEDs_Type led);

#endif