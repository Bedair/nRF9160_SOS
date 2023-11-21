/**********************************************************************
* File Name : IoHwAbs_LED.c
* 
* Description : Source file for the component responsible for controlling
*               the LEDs
*
* Author : Mohamed Bedair
*
* Date : 20 Nov 2023
*
**********************************************************************/

/**********************************************************************
*                            Macro Section                            *
**********************************************************************/

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#include "IoHwAbs_Switch.h"


/**********************************************************************
*                          Global Variables                           *
**********************************************************************/
static const struct gpio_dt_spec Switches[TOTAL_SWITCHS_COUNT] = {
    GPIO_DT_SPEC_GET(DT_NODELABEL(button0), gpios),
    GPIO_DT_SPEC_GET(DT_NODELABEL(button1), gpios),
    GPIO_DT_SPEC_GET(DT_NODELABEL(button2), gpios),
    GPIO_DT_SPEC_GET(DT_NODELABEL(button3), gpios)
};


/**********************************************************************
*                           Local Functions                           *
**********************************************************************/

/**********************************************************************
*                          Global Functions                           *
**********************************************************************/
/*
* Funcation Name : IoHwAbs_Switch_Init
* Description    : Used to initialize all the Switches on the Board
* Parameters     : NA
* Return         : NA
*/
void IoHwAbs_Switch_Init(void)
{
    for (uint8_t sw = SWITCH_0; sw < TOTAL_SWITCHS_COUNT; sw++)
    {
        gpio_pin_configure_dt(&Switches[sw], GPIO_INPUT | GPIO_PULL_UP);
    }
}


/*
* Funcation Name : IoHwAbs_Switch_Get_State
* Description    : Used to read the State of the Board LED
* Parameters     : Switch ID
* Return         : Switch state
*/
Switch_State_Type IoHwAbs_Switch_Get_State(Switch_Type sw)
{
    return gpio_pin_get_dt(&Switches[sw]);
}
