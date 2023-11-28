/**********************************************************************
* File Name : main.c
* 
* Description : Source file for main application component
*
* Author : Mohamed Bedair
*
* Date : 28 Nov 2023
*
**********************************************************************/

/**********************************************************************
*                            Macro Section                            *
**********************************************************************/
#include <zephyr/kernel.h>
#include <string.h>

#include "App_SMS.h"
#include "App_GNSS.h"
#include "App_Modem.h"
#include "IoHwAbs_LED.h"
#include "IoHwAbs_Switch.h"



#define TASK_STACK_SIZE                 (1024)
#define TASK_PRIORITY                   (5)

#define BUTTON_HANDLER_PERIODICITY      (50)
#define MODEM_HANDLER_PERIODICITY       (6000)

#define BUTTON_DEBOUNCE_DELAY           (10)

#define LED_INITIAL_PERIODICITY         (500)


typedef enum{
        TASK_STATE_SUSPEND = 0xAA,
        TASK_STATE_RESUME  = 0x55
}TaskState_Type;



/**********************************************************************
*                          Global Variables                           *
**********************************************************************/


/**********************************************************************
*                          Local Variables                           *
**********************************************************************/


/**********************************************************************
*                           Local Functions                           *
**********************************************************************/

static void LED_Handler(void);
static void Button_Handler(void);
static void Modem_Handler(void);

K_THREAD_DEFINE(LED_Handler_id, TASK_STACK_SIZE, LED_Handler, NULL, NULL, NULL, TASK_PRIORITY, 0, 0);
K_THREAD_DEFINE(Button_Handler_id, TASK_STACK_SIZE, Button_Handler, NULL, NULL, NULL, TASK_PRIORITY, 0, 0);
K_THREAD_DEFINE(Modem_Handler_id, TASK_STACK_SIZE, Modem_Handler, NULL, NULL, NULL, TASK_PRIORITY, 0, 0);




static void LED_Handler(void)
{       
        IoHwAbs_LED_Init();

        while (1)
        {
                IoHwAbs_LED_Toggle(LED_0);
                IoHwAbs_LED_Toggle(LED_1); 
                IoHwAbs_LED_Toggle(LED_2); 
                IoHwAbs_LED_Toggle(LED_3);
                k_msleep(LED_INITIAL_PERIODICITY); 
        }
        
}

static void Button_Handler(void)
{       
        static TaskState_Type Modem_Task_State = TASK_STATE_SUSPEND;
        IoHwAbs_Switch_Init();
        while (1)
        {
                if (IoHwAbs_Switch_Get_State(SWITCH_0))
                {
                        /* Debounce the Button */
                        k_msleep(BUTTON_DEBOUNCE_DELAY);
                        if (IoHwAbs_Switch_Get_State(SWITCH_0))
                        {
                                printk("Button Pressed ... \n\r");
                                if (Modem_Task_State != TASK_STATE_RESUME)
                                {
                                        /* Activate thee Modem_Handler task */
                                        k_wakeup(Modem_Handler_id);
                                        printk("Modem_Handler Task Activated ... \n\r");
                                        Modem_Task_State = TASK_STATE_RESUME;
                                }  
                        } 
                }
                k_msleep(BUTTON_HANDLER_PERIODICITY); 
        }  
}

static void Modem_Handler(void)
{       

        printk("Modem_Handler Task Suspended ... \n\r");
        /* Wait until the Button is Pressed */
        k_sleep(K_FOREVER);
        while (1)
        {
                printk("Modem_Handler ... \n\r");
                k_msleep(MODEM_HANDLER_PERIODICITY); 
        }
        
}



/**********************************************************************
*                          Global Functions                           *
**********************************************************************/
int main(void)
{       
        /* The Code is executed from the threads */
        return 0;
}



