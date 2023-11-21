/**********************************************************************
* File Name : IoHwAbs_LED.h
* 
* Description : Header file for the component responsible for reading
*               the state of the On-Board Switches state
*
* Author : Mohamed Bedair
*
* Date : 21 Nov 2023
*
**********************************************************************/


#ifndef IOHWABS_SWITCH_H
#define IOHWABS_SWITCH_H

typedef enum{
    SWITCH_0 = 0,
    SWITCH_1,
    SWITCH_2,
    SWITCH_3,
    TOTAL_SWITCHS_COUNT
}Switch_Type;


typedef enum{
    SWITCH_NOT_PRESSED = 0,
    SWITCH_PRESSED  = 1
}Switch_State_Type;


/*
* Funcation Name : IoHwAbs_Switch_Init
* Description    : Used to initialize all the Switches on the Board
* Parameters     : NA
* Return         : NA
*/
void IoHwAbs_Switch_Init(void);


/*
* Funcation Name : IoHwAbs_Switch_Get_State
* Description    : Used to read the State of the Board LED
* Parameters     : Switch ID
* Return         : Switch state
*/
Switch_State_Type IoHwAbs_Switch_Get_State(Switch_Type sw);

#endif