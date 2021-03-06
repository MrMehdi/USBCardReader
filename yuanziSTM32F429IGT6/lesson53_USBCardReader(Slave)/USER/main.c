#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "string.h"
#include "sdram.h"
#include "malloc.h"
#include "w25qxx.h"
#include "string.h"
#include "sdio_sdcard.h"
#include "ftl.h"
#include "nand.h"
#include "usbd_msc_core.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usb_conf.h"
#include "usbd_msc_bot.h"
#include "pcf8574.h"
/************************************************
 ALIENTEK 阿波罗STM32F429开发板实验53
 USB读卡器(Slave)实验-HAL库函数版
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com  
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

USB_OTG_CORE_HANDLE USB_OTG_dev;
extern vu8 USB_STATUS_REG;		//USB状态
extern vu8 bDeviceState;		//USB连接 情况

int main(void)
{
//	u8 offline_cnt=0;
//	u8 tct=0;
//	u8 USB_STA;
//	u8 Divece_STA;
	
    Stm32_Clock_Init(384,25,2,8);   //设置时钟,192Mhz   
    delay_init(192);                //初始化延时函数
    uart_init(115200);              //初始化USART
//    LED_Init();                     //初始化LED 
//    KEY_Init();                     //初始化按键
    SDRAM_Init();                   //SDRAM初始化
//    LCD_Init();                     //LCD初始化
//	W25QXX_Init();				    //初始化W25Q256
    PCF8574_Init();				    //初始化PCF8574 
 	my_mem_init(SRAMIN);		    //初始化内部内存池
	my_mem_init(SRAMEX);		    //初始化外部内存池
	my_mem_init(SRAMCCM);		    //初始化CCM内存池 

	if(SD_Init())
	{
		printf("检测SD卡错误\r\n");
//		LCD_ShowString(30,130,200,16,16,"SD Card Error!");	//检测SD卡错误
	}
	else //SD 卡正常
	{   			
		printf("SD Card Successful!\r\n");
//		LCD_ShowString(30,130,200,16,16,"SD Card Size:     MB"); 
// 		LCD_ShowNum(134,130,SDCardInfo.CardCapacity>>20,5,16);	//显示SD卡容量
 	}
//	if(W25QXX_ReadID()!=W25Q256)LCD_ShowString(30,130,200,16,16,"W25Q128 Error!");	//检测W25Q128错误
//	else //SPI FLASH 正常
//	{   														 
//		LCD_ShowString(30,150,200,16,16,"SPI FLASH Size:25MB");	 
//	} 
//	if(FTL_Init())LCD_ShowString(30,170,200,16,16,"NAND Error!");	//检测W25Q128错误
//	else //NAND FLASH 正常
//	{   														 
//		LCD_ShowString(30,170,200,16,16,"NAND Flash Size:    MB"); 
// 		LCD_ShowNum(158,170,nand_dev.valid_blocknum*nand_dev.block_pagenum*nand_dev.page_mainsize>>20,4,16);	//显示SD卡容量
//	}  
// 	LCD_ShowString(30,190,200,16,16,"USB Connecting...");	//提示正在建立连接 	
	MSC_BOT_Data=mymalloc(SRAMIN,MSC_MEDIA_PACKET);			//申请内存
	USBD_Init(&USB_OTG_dev,USB_OTG_FS_CORE_ID,&USR_desc,&USBD_MSC_cb,&USR_cb);
	delay_ms(1800);			    
	while(1)
	{
#if 0
		
//		printf("Hello USB!\r\n");
        delay_ms(1);				  
		if(USB_STA!=USB_STATUS_REG)//状态改变了 
		{	 						   
//			LCD_Fill(30,210,240,210+16,WHITE);//清除显示			  	   
			if(USB_STATUS_REG&0x01)//正在写		  
			{
				LED1=0;
				printf("USB Writeing...");
//				LCD_ShowString(30,210,200,16,16,"USB Writing...");//提示USB正在写入数据	 
			}
			if(USB_STATUS_REG&0x02)//正在读
			{
				LED1=0;
				printf("USB Reading...");
//				LCD_ShowString(30,210,200,16,16,"USB Reading...");//提示USB正在读出数据  		 
			}	 										  
			if(USB_STATUS_REG&0x04)
			{
				printf("USB Write Err111");
//				LCD_ShowString(30,230,200,16,16,"USB Write Err ");//提示写入错误
			}
		
			if(USB_STATUS_REG&0x08)
			{
				printf("USB Read Err222");
//				LCD_ShowString(30,250,200,16,16,"USB Read  Err ");//提示读出错误
			}
			  
			USB_STA=USB_STATUS_REG;//记录最后的状态
		}
		if(Divece_STA!=bDeviceState) 
		{
			if(bDeviceState==1)
			{
				printf("USB Connected...");
//				LCD_ShowString(30,190,200,16,16,"USB Connected    ");//提示USB连接已经建立
			}
			else 
			{
				printf("USB DisConnected...");
//				LCD_ShowString(30,190,200,16,16,"USB DisConnected ");//提示USB被拔出了
			}
			Divece_STA=bDeviceState;
		}
		tct++;
//		if(tct==200)
//		{
//			tct=0;
//			LED1=1;
//			LED0=!LED0;//提示系统在运行
//			if(USB_STATUS_REG&0x10)
//			{
//				offline_cnt=0;//USB连接了,则清除offline计数器
//				bDeviceState=1;
//			}else//没有得到轮询 
//			{
//				offline_cnt++;  
//				if(offline_cnt>10)bDeviceState=0;//2s内没收到在线标记,代表USB被拔出了
//			}
//			USB_STATUS_REG=0;
//		}

#endif		
	}   //end if while(1)
}
