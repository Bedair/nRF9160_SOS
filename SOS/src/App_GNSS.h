/**********************************************************************
* File Name : App_GNSS.h
* 
* Description : Header file for the component responsible to use GNSS
*
* Author : Mohamed Bedair
*
* Date : 22 Nov 2023
*
**********************************************************************/


#ifndef APP_GNSS_H
#define APP_GNSS_H


#include <zephyr/kernel.h>


typedef struct
{
    double latitude;
    double longitude;
    float altitude;
}GNSS_Position_Type;


/*
* Funcation Name : App_GNSS_Init
* Description    : Used to initialize and start the GNSS
* Parameters     : NA
* Return         : initialization state
*/
int App_GNSS_Init(void);


/*
* Funcation Name : App_GNSS_Data_Valid
* Description    : Used to get check if there is valid GNSS data
* Parameters     : Pointer to hold the position data
* Return         : NA
*/
uint8_t App_GNSS_Data_Valid(void);


/*
* Funcation Name : App_GNSS_Get_Position_Data
* Description    : Used to get the last read position data
* Parameters     : Pointer to hold the position data
* Return         : NA
*/
void App_GNSS_Get_Position_Data(GNSS_Position_Type *pos);

#endif