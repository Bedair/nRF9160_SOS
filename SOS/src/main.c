#include <zephyr/kernel.h>

#include "IoHwAbs_LED.h"
#include "IoHwAbs_Switch.h"

int main(void)
{       
        IoHwAbs_LED_Init();
        IoHwAbs_Switch_Init();

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
                k_msleep(200);           
        }
        return 0;
}
