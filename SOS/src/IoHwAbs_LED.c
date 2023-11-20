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

#include "IoHwAbs_LED.h"


/**********************************************************************
*                          Global Variables                           *
**********************************************************************/



/**********************************************************************
*                           Local Functions                           *
**********************************************************************/
static const struct gpio_dt_spec LEDs[TOTAL_LEDS_COUNT] = {
    GPIO_DT_SPEC_GET(DT_NODELABEL(led0), gpios),
    GPIO_DT_SPEC_GET(DT_NODELABEL(led1), gpios),
    GPIO_DT_SPEC_GET(DT_NODELABEL(led2), gpios),
    GPIO_DT_SPEC_GET(DT_NODELABEL(led3), gpios)
};

/**********************************************************************
*                          Global Functions                           *
**********************************************************************/
/*
* Funcation Name : IoHwAbs_LED_Init
* Description    : Used to initialize all the LEDs on the Board
* Parameters     : NA
* Return         : NA
*/
void IoHwAbs_LED_Init(void)
{
    for (uint8_t led = LED_0; led < TOTAL_LEDS_COUNT; led++)
    {
        gpio_pin_configure_dt(&LEDs[led], GPIO_OUTPUT_INACTIVE);
    }
}



/*
* Funcation Name : IoHwAbs_LED_Set_State
* Description    : Used to update the State of the Board LED
* Parameters     : LED ID, LED State
* Return         : NA
*/
void IoHwAbs_LED_Set_State(LEDs_Type led, LED_State_Type state)
{
    gpio_pin_set_dt(&LEDs[led], state);
}


/*
* Funcation Name : IoHwAbs_LED_Toggle
* Description    : Used to toggle Board LED
* Parameters     : LED number
* Return         : NA
*/
void IoHwAbs_LED_Toggle(LEDs_Type led)
{
    gpio_pin_toggle_dt(&LEDs[led]);
}
