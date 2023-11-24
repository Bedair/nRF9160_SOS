#include <zephyr/kernel.h>
#include <string.h>

#include "App_SMS.h"
#include "App_GNSS.h"
#include "App_Modem.h"
#include "IoHwAbs_LED.h"
#include "IoHwAbs_Switch.h"




#define CONFIG_SMS_SEND_PHONE_NUMBER "+4917674937323"



GNSS_Position_Type position;


int main(void)
{       
        
        int ret = 0;

        IoHwAbs_LED_Init();
        IoHwAbs_Switch_Init();

        printk("START Modem ... \n\r");
        App_Modem_Init();
        printk("Modem Started ... \n\r");

        printk("START GNSS ... \n\r");
        App_GNSS_Init();
        printk("GNSS Started ... \n\r");

        App_SMS_Init();

        k_msleep(10000); 
        
        

        printk("Sending SMS: number=%s, text=\"SMS sample: testing\"\n", CONFIG_SMS_SEND_PHONE_NUMBER);


        ret = App_SMS_Send(CONFIG_SMS_SEND_PHONE_NUMBER, "SMS sample: testing");
        if (ret) 
        {
                printk("Sending SMS failed with error: %d\n", ret);
        }
        else
        {
                printk("Sending SMS succeed \n");
        }

        while (1)
        {
               if (IoHwAbs_Switch_Get_State(SWITCH_0) ||
                   IoHwAbs_Switch_Get_State(SWITCH_1) ||
                   IoHwAbs_Switch_Get_State(SWITCH_2) ||
                   IoHwAbs_Switch_Get_State(SWITCH_3)
               )
               {
                        IoHwAbs_LED_Toggle(LED_0);
                        IoHwAbs_LED_Toggle(LED_1); 
                        IoHwAbs_LED_Toggle(LED_2); 
                        IoHwAbs_LED_Toggle(LED_3); 
               }

                /*
                if (App_GNSS_Data_Valid())
                {
                        App_GNSS_Get_Position_Data(&position);

                        printk("altitude  : %d\n\r", position.altitude);
                        printk("latitude  : %d\n\r", position.latitude);
                        printk("longitude : %d\n\r", position.longitude);
                }
                */

                k_msleep(2000);           
        }
        return 0;
}
