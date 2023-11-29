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


/* TODO : update the Phone Number */
#define CONFIG_SMS_SEND_PHONE_NUMBER "+000000000000"

#define TASK_STACK_SIZE                 (1024)
#define TASK_PRIORITY                   (5)

#define BUTTON_HANDLER_PERIODICITY      (50)
#define MODEM_HANDLER_PERIODICITY       (5000)

#define BUTTON_DEBOUNCE_DELAY           (10)

#define LED_INITIAL_PERIODICITY         (500)


#define MODEM_NOT_STARTED               (0xAA)
#define MODEM_STARTED                   (0x55)

#define SOS_NOT_REQUESTED               (0xAA)
#define SOS_REQUESTED                   (0x55)


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
static uint8_t Modem_State = MODEM_NOT_STARTED;
static uint8_t SOS_State   = SOS_NOT_REQUESTED;

/**********************************************************************
*                           Local Functions                           *
**********************************************************************/

static void LED_Handler(void);
static void Button_Handler(void);
static void Modem_Handler(void);


static void Modem_Handler(void);

K_THREAD_DEFINE(LED_Handler_id, TASK_STACK_SIZE, LED_Handler, NULL, NULL, NULL, TASK_PRIORITY, 0, 0);
K_THREAD_DEFINE(Button_Handler_id, TASK_STACK_SIZE, Button_Handler, NULL, NULL, NULL, TASK_PRIORITY, 0, 0);
K_THREAD_DEFINE(Modem_Handler_id, TASK_STACK_SIZE, Modem_Handler, NULL, NULL, NULL, TASK_PRIORITY, 0, 0);




static void LED_Handler(void)
{       
        IoHwAbs_LED_Init();

        while (1)
        {
                /* Toogle LED During Modem Initialization and make it ON when modem is initialized */
                if (MODEM_STARTED == Modem_State)
                {
                        IoHwAbs_LED_Set_State(LED_0, LED_ON);
                }
                else
                {
                        IoHwAbs_LED_Toggle(LED_0);
                }

                /* Toggle LED2 if SOS not requested and make it ON when SOS is requested */
                if (SOS_REQUESTED == SOS_State)
                {
                        IoHwAbs_LED_Set_State(LED_2, LED_ON);
                }
                else
                {
                        IoHwAbs_LED_Toggle(LED_2); 
                }

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
        int ret = 0;
        GNSS_Position_Type position;
        uint32_t attampt = 0;

        char textBuff[100];

        printk("START Modem ... \n\r");
        App_Modem_Init();

        printk("START GNSS ... \n\r");
        App_GNSS_Init();

        App_SMS_Init();

        Modem_State = MODEM_STARTED;

        printk("Modem_Handler Task Suspended ... \n\r");
        /* Wait until the Button is Pressed */
        k_sleep(K_FOREVER);

        SOS_State = SOS_REQUESTED;
        while (1)
        {       
                if (App_GNSS_Data_Valid())
                {

                        App_GNSS_Get_Position_Data(&position);
                        attampt++;
                        sprintf(textBuff, "Attampt: %d, longitude: %.6f, latitude: %.6f\n\r ", attampt, position.longitude, position.latitude);

                        ret = App_SMS_Send(CONFIG_SMS_SEND_PHONE_NUMBER, textBuff);
                        if (ret) 
                        {
                                printk("Sending SMS failed with error: %d\n", ret);
                        }
                }
                
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



