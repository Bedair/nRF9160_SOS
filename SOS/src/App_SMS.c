/**********************************************************************
* File Name : App_SMS.c
* 
* Description : Source file for the component responsible for send SMS
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

#include "App_SMS.h"


#include <modem/sms.h>


/**********************************************************************
*                          Global Variables                           *
**********************************************************************/


/**********************************************************************
*                          Local Variables                           *
**********************************************************************/


/**********************************************************************
*                           Local Functions                           *
**********************************************************************/

static void sms_callback(struct sms_data *const data, void *context)
{
	if (data == NULL) {
		printk("%s with NULL data\n", __func__);
		return;
	}

	if (data->type == SMS_TYPE_DELIVER) {
		/* When SMS message is received, print information */
		struct sms_deliver_header *header = &data->header.deliver;

		printk("\nSMS received:\n");
		printk("\tTime:   %02d-%02d-%02d %02d:%02d:%02d\n",
			header->time.year,
			header->time.month,
			header->time.day,
			header->time.hour,
			header->time.minute,
			header->time.second);

		printk("\tText:   '%s'\n", data->payload);
		printk("\tLength: %d\n", data->payload_len);

		if (header->app_port.present) {
			printk("\tApplication port addressing scheme: dest_port=%d, src_port=%d\n",
				header->app_port.dest_port,
				header->app_port.src_port);
		}
		if (header->concatenated.present) {
			printk("\tConcatenated short message: ref_number=%d, msg %d/%d\n",
				header->concatenated.ref_number,
				header->concatenated.seq_number,
				header->concatenated.total_msgs);
		}
	} else if (data->type == SMS_TYPE_STATUS_REPORT) {
		printk("SMS status report received\n");
	} else {
		printk("SMS protocol message with unknown type received\n");
	}
}



/**********************************************************************
*                          Global Functions                           *
**********************************************************************/
/*
* Funcation Name : App_SMS_Init
* Description    : Used to initialize the SMS driver
* Parameters     : NA
* Return         : NA
*/
void App_SMS_Init(void)
{
    int handle = 0;

    handle = sms_register_listener(sms_callback, NULL);
    if (handle) 
    {
		printk("sms_register_listener returned err: %d\n", handle);
	}
    else
    {
        printk("SMS sample is ready for sending messages\n");
    }

}


/*
* Funcation Name : App_SMS_Send
* Description    : Used to send SMS
* Parameters     : number to send to , and sms text
* Return         : return state
*/
int App_SMS_Send(char *number, char *text)
{
    return sms_send_text(number, text);
}

