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
#if 0
		static u8 flag = 0;
		static u16 color = 0;
		key1 = KEY1_INPUT_LEVEL;
		key2 = KEY2_INPUT_LEVEL;
		key3 = KEY3_INPUT_LEVEL;
	    if(key1 == 0){
			color -= 0x01070e;
			flag = 1;
		}
		if(key2 == 0){
            color = 0;
			flag = 1;
		}
		if(key3 == 0){
			color += 0x01070e;
			flag = 1;
		}
		
		if(flag == 1){
			flag = 0;
//			lcd_flush_scream();
			lcd_draw_box(IMAGE_X_START,IMAGE_X_END,IMAGE_Y_START,IMAGE_Y_END,color);
//			lcd_display_allchar();
//			delay_ms(1000);
//			lcd_display_allword();
		}
	  
#endif	  
#if 0
	  
		if(SPI_get_data_status() ==DATA_VALID){
			data_receive = SPI_receive_half_word();
			delay_ms(100);
			SPI_send_half_word(data_receive);
			
			LED1_TOGGLE;
		}
		i++;
		if(i%100000 == 0){
			LED2_TOGGLE
		}
	
#endif
		
#if 0 
		key1 = KEY1_INPUT_LEVEL;
		key2 = KEY2_INPUT_LEVEL;
		key3 = KEY3_INPUT_LEVEL;
		if(key1 == 0){
			LED1_ON;
		}else{
			LED1_OFF;
		}
		if(key2 == 0){
			LED2_ON;
		}else{
			LED2_OFF;
		}
		if(key3 == 0){
			LED1_ON;
			LED2_ON;
		}else{
			LED1_OFF;
			LED2_OFF;
		}
#endif
	}
}

/*****END OF FILE****/



