/* 包含头文件 ----------------------------------------------------------------*/
#include "stm32f10x.h"
#include "bsp/led/bsp_led.h"
#include "bsp/key/bsp_key.h"
#include "bsp/spi/bsp_spi.h"
#include "bsp/LCD/bsp_LCD.h"


/**
  * 函数功能: 主函数.
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
  


 void delay_ms(u16 tm)
 {
	 int i;
	 for(i=0;i<10000*tm;i++);
 }
 
int main(void)
{
//	uint8_t key1,key2,key3;
	SystemInit();

	/* 初始化板载LED灯 */
	LED_GPIO_Init();

	/*初始化key按键*/
	KEY_GPIO_Init();
	
	/*初始化LCD*/
	lcd_init();
	/*初始化spi*/
	SPI_init();
	
	LED1_OFF;
	LED2_OFF;

	lcd_display_menu(CMD_EXIT);
  /* 无限循环 */
  while (1){	 

	}
}

/*****END OF FILE****/



