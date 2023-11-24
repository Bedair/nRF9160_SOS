/**********************************************************************
* File Name : App_Modem.h
* 
* Description : Header file for the component responsible for controlling
*               the Modem
*
* Author : Mohamed Bedair
*
* Date : 24 Nov 2023
*
**********************************************************************/

/**********************************************************************
*                            Macro Section                            *
**********************************************************************/

#include <zephyr/kernel.h>

#include "App_Modem.h"



/**********************************************************************
*                          Global Variables                           *
**********************************************************************/


/**********************************************************************
*                          Local Variables                           *
**********************************************************************/


/**********************************************************************
*                           Local Functions                           *
**********************************************************************/

/**********************************************************************
*                          Global Functions                           *
**********************************************************************/

/*
* Funcation Name : App_Modem_Init
* Description    : Used to initialize the Modem
* Parameters     : NA
* Return         : NA
*/
int App_Modem_Init(void)
{       
        int err = 0;

       
        err = nrf_modem_lib_init();
        printk("nrf_modem_lib_init Return : %d\n\r", err);

        err |= lte_lc_init();
        printk("lte_lc_init Return        : %d\n\r", err);

        err |= lte_lc_psm_req(true);
        printk("lte_lc_psm_req Return     : %d\n\r", err);

        err |= lte_lc_connect();
        printk("lte_lc_connect Return     : %d\n\r", err);

        return err;
}

