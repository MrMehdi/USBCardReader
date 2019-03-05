#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h"  
#include "key.h"     
#include "usmart.h" 
#include "malloc.h"
#include "sdio_sdcard.h"  
#include "w25qxx.h"    
#include "ff.h"  
#include "exfuns.h"    
 
#include "mass_mal.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"
#include "memory.h"	    
#include "usb_bot.h" 
 
/************************************************
 ALIENTEK精英STM32开发板实验36
 FATFS文件系统实验 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/


extern u8 Max_Lun;	//支持的磁盘个数,0表示1个,1表示2个.
 int main(void)
 {	 
	u8 t=0;	
   	    

	delay_init();	    	 //延时函数初始化	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
 	usmart_dev.init(72);		//初始化USMART		
 	LED_Init();		  			//初始化与LED连接的硬件接口
 	my_mem_init(SRAMIN);		//初始化内部内存池
	exfuns_init();							//为fatfs相关变量申请内存				 
	f_mount(fs[0],"0:",1); 					//挂载SD卡 
	  
	if(SD_Init())
	{
		Max_Lun=0;											//SD卡错误,则仅只有一个磁盘.
	}else //SD 卡正常
	{   															  
			Mass_Memory_Size[0]=SDCardInfo.CardCapacity;		//得到SD卡容量（字节），当SD卡容量超过4G的时候,需要用到两个u32来表示
	    Mass_Block_Size[0] =512;							//因为我们在Init里面设置了SD卡的操作字节为512个,所以这里一定是512个字节.
	    Mass_Block_Count[0]=Mass_Memory_Size[0]/Mass_Block_Size[0];
 	}


	delay_ms(1800);
	USB_Port_Set(0); 	//USB先断开
	delay_ms(700);
	USB_Port_Set(1);	//USB再次连接 
  	Data_Buffer=mymalloc(SRAMIN,BULK_MAX_PACKET_SIZE*2*4);	//为USB数据缓存区申请内存
	Bulk_Data_Buff=mymalloc(SRAMIN,BULK_MAX_PACKET_SIZE);	//申请内存
 	//USB配置
 	USB_Interrupts_Config();    
 	Set_USBClock();    
 	USB_Init();	    
	delay_ms(1800);	  											    
			  												  			    

	while(1)
	{
		t++; 
		delay_ms(200);		 			   
		LED0=!LED0;
	} 
}

















