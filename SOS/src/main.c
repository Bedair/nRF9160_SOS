#include <zephyr/kernel.h>

#include "IoHwAbs_LED.h"

static uint32_t counter = 0;

int main(void)
{       
        IoHwAbs_LED_Init();

        //IoHwAbs_LED_Set_State(LED_1, LED_ON);

        while (1)
        {
                
                IoHwAbs_LED_Toggle(LED_0);
                IoHwAbs_LED_Toggle(LED_1); 
                IoHwAbs_LED_Toggle(LED_2); 
                IoHwAbs_LED_Toggle(LED_3); 
                
                k_msleep(200); 
                /*    
                if (counter % 2)
                {
                        IoHwAbs_LED_Set_State(LED_0, LED_ON);
                        IoHwAbs_LED_Set_State(LED_1, LED_ON);
                        IoHwAbs_LED_Set_State(LED_2, LED_ON);
                        IoHwAbs_LED_Set_State(LED_3, LED_ON);
                }  
                else
                {
                        IoHwAbs_LED_Set_State(LED_0, LED_OFF);
                        IoHwAbs_LED_Set_State(LED_1, LED_OFF);
                        IoHwAbs_LED_Set_State(LED_2, LED_OFF);
                        IoHwAbs_LED_Set_State(LED_3, LED_OFF);
                }
                counter++; 
                */

                    
        }
        return 0;
}
