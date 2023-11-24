/**********************************************************************
* File Name : App_GNSS.c
* 
* Description : Source file for the component responsible to use GNSS
*
* Author : Mohamed Bedair
*
* Date : 22 Nov 2023
*
**********************************************************************/

/**********************************************************************
*                            Macro Section                            *
**********************************************************************/

#include <zephyr/kernel.h>
#include <nrf_modem_gnss.h>

#include "App_GNSS.h"


#define VALID_GNSS_DATA     (0xAA)
#define INVALID_GNSS_DATA   (0x55)

/**********************************************************************
*                          Global Variables                           *
**********************************************************************/


/**********************************************************************
*                          Local Variables                           *
**********************************************************************/
static uint8_t Valid_GNSS_Data;
static struct nrf_modem_gnss_pvt_data_frame pvt_data;

/**********************************************************************
*                           Local Functions                           *
**********************************************************************/


static void gnss_event_handler(int event_id)
{
    int err;

    /* Process event */
    switch (event_id) 
    {
        case NRF_MODEM_GNSS_EVT_PVT:
            err = nrf_modem_gnss_read(&pvt_data, sizeof(pvt_data), NRF_MODEM_GNSS_DATA_PVT);
            if (err == 0) Valid_GNSS_Data = VALID_GNSS_DATA;
            break;
        default:
            break;
    }
}


/**********************************************************************
*                          Global Functions                           *
**********************************************************************/

/*
* Funcation Name : App_GNSS_Init
* Description    : Used to initialize and start the GNSS
* Parameters     : NA
* Return         : initialization state
*/
int App_GNSS_Init(void)
{
    int err = 0;

    Valid_GNSS_Data = INVALID_GNSS_DATA;

    err = nrf_modem_gnss_event_handler_set(gnss_event_handler);
    printk("nrf_modem_gnss_event_handler_set Return : %d\n\r", err);

    err = nrf_modem_gnss_start();
    printk("nrf_modem_gnss_start Return : %d\n\r", err);

    return err;
}


/*
* Funcation Name : App_GNSS_Data_Valid
* Description    : Used to get check if there is valid GNSS data
* Parameters     : Pointer to hold the position data
* Return         : NA
*/
uint8_t App_GNSS_Data_Valid(void)
{
    return (Valid_GNSS_Data == VALID_GNSS_DATA? 1 : 0);
}


/*
* Funcation Name : App_GNSS_Get_Position_Data
* Description    : Used to get the last read position data
* Parameters     : Pointer to hold the position data
* Return         : NA
*/
void App_GNSS_Get_Position_Data(GNSS_Position_Type *pos)
{
    pos->altitude  = pvt_data.altitude;
    pos->latitude  = pvt_data.latitude;
    pos->longitude = pvt_data.longitude;
}

