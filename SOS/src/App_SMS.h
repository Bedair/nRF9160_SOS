/**********************************************************************
* File Name : App_SMS.h
* 
* Description : Header file for the component responsible for send SMS
*
* Author : Mohamed Bedair
*
* Date : 22 Nov 2023
*
**********************************************************************/


#ifndef APP_SMS_H
#define APP_SMS_H

#include <zephyr/kernel.h>



/*
* Funcation Name : App_SMS_Init
* Description    : Used to initialize the SMS driver
* Parameters     : NA
* Return         : NA
*/
void App_SMS_Init(void);


/*
* Funcation Name : App_SMS_Send
* Description    : Used to send SMS
* Parameters     : number to send to , and sms text
* Return         : return state
*/
int App_SMS_Send(char *number, char *text);


#endif