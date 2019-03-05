#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h"  
#include "malloc.h"
#include "sdio_sdcard.h"  
#include "w25qxx.h"    
#include "mass_mal.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"
#include "memory.h"	    
#include "usb_bot.h" 
 
/************************************************
 ALIENTEK��ӢSTM32������ʵ��44
 USB������ ʵ��  
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/


extern u8 Max_Lun;	//֧�ֵĴ��̸���,0��ʾ1��,1��ʾ2��.
 int main(void)
 {	 

	delay_init();	    	 //��ʱ������ʼ��	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
 	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ��
	if(SD_Init())
	{
		Max_Lun=0;											//SD������,���ֻ��һ������.
	}else //SD ������
	{   															  
			Mass_Memory_Size[0]=SDCardInfo.CardCapacity;		//�õ�SD���������ֽڣ�����SD����������4G��ʱ��,��Ҫ�õ�����u32����ʾ
	    Mass_Block_Size[0] =512;							//��Ϊ������Init����������SD���Ĳ����ֽ�Ϊ512��,��������һ����512���ֽ�.
	    Mass_Block_Count[0]=Mass_Memory_Size[0]/Mass_Block_Size[0];
 	}
           
	delay_ms(1800);
	USB_Port_Set(0); 	//USB�ȶϿ�
	delay_ms(700);
	USB_Port_Set(1);	//USB�ٴ����� 
  	Data_Buffer=mymalloc(SRAMIN,BULK_MAX_PACKET_SIZE*2*4);	//ΪUSB���ݻ����������ڴ�
	Bulk_Data_Buff=mymalloc(SRAMIN,BULK_MAX_PACKET_SIZE);	//�����ڴ�
 	//USB����
 	USB_Interrupts_Config();    
 	Set_USBClock();    
 	USB_Init();	    
	delay_ms(1800);	   	    
	while(1)
	{	

	}
}














