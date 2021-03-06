
#ifndef   __BSP_LCD__
#define   __BSP_LCD__

#include  "stm32f10x.h"

//屏幕开始时显示方式，注意：当IDelay时显示第一幅画面是逐像素刷新的
//此时必须手动在刷新结束后加上  LCD_WR_REG(0x0007,0x0173);才能显示
//当Immediately时没有被注释掉是不需要此过程

/* 选择BANK1-BORSRAM1 连接 TFT，地址范围为0X60000000~0X63FFFFFF
 * FSMC_A16 接LCD的DC(寄存器/数据选择)脚
 * 16 bit => FSMC[24:0]对应HADDR[25:1]
 * 寄存器基地址 = 0X60000000
 * RAM基地址 = 0X60020000 = 0X60000000+2^16*2 = 0X60000000 + 0X20000 = 0X60020000
 * 当选择不同的地址线时，地址要重新计算。
 */
#define Bank1_LCD_D    ((u32)0x60020000)    //Disp Data ADDR
#define Bank1_LCD_C    ((u32)0x60000000)	   //Disp Reg ADDR

#define Set_Rst GPIOD->BSRR = GPIO_Pin_13;
#define Clr_Rst GPIOD->BRR  = GPIO_Pin_13;

#define Lcd_Light_ON   GPIOA->BSRR = GPIO_Pin_3;
#define Lcd_Light_OFF  GPIOA->BRR  = GPIO_Pin_3;

/*代表一个汉字*/
struct word_struct{
	u8 num;
	u16 data[16];
};
/*代表一个字符，如标点、字母*/
struct char_struct{
	u8 num;
	u8 data[16];
};

void lcd_init(void);//初始化LCD
void lcd_draw_box(u16 x,u16 y,u16 xLong,u16 yLong,u16 Color);//在指定位置画一个指定的矩形框
void lcd_draw_pixel(u16 x, u16 y, u16 Color);//在指定位置显示一个点
void lcd_flush_toolbar(void);//刷新toolbar
void lcd_put_char(u16 x,u16 y,u16 background,u16 word_color,u8 num);//在指定位置显示一个字符
void lcd_put_word(u16 x,u16 y,u16 background,u16 word_color,u8 num);//在指定位置显示一个汉字
void lcd_display_allchar(void);//显示所有字符
void lcd_display_allword(void);//显示所有汉字
void lcd_display_cmd(void);//显示munu，以供用户选择
void lcd_menu_choice_down(void);//显示框向下移动
void lcd_menu_choice_up(void);//显示框向上移动
void lcd_menu_choice_confirm(void);//确认当前选项，并更新命令
void lcd_WriteComm(u16 CMD);
void lcd_WriteData(u16 tem_data);
void lcd_WR_Start(void);
void lcd_set_area_to_display(u16 x_start,u16 x_end,u16 y_start,u16 y_end);
void send_cmd(void);

#define X_START 	(0) 
#define X_END   	(319)
#define Y_START 	(0)
#define Y_END		(239)

#define IMAGE_X_START 	X_START 
#define IMAGE_X_END   	X_END
#define IMAGE_Y_START 	Y_START
#define IMAGE_Y_END		Y_END

#define TOOLBAR_X_START 	X_START 
#define TOOLBAR_X_END   	X_END
#define TOOLBAR_Y_START 	Y_START
#define TOOLBAR_Y_END		(20)

/*背景颜色*/

#define TOOLBAR_COLOR 0x1111
#define CHOOSE_COLOR 0xeeee
#define INIT_COLOR 0xffff
            
#define BIT(data,num) (((data) & (1<<(num)))>>(num))


/*显示一些特定字符串*/
#define DISPLAY_TEST_C(x,y,background,color) \
	   lcd_put_word(x,y,background,color,0) \
	   lcd_put_word(x,y,background,color,0)

#define CMD_NONE 0
#define CMD_LED1 1
#define CMD_LED2 2
#define CMD_LED3 3
#define CMD_LED4 4
#define CMD_EXIT 5

#define CMD_IS_READY 1
#define CMD_IS_NOT_READY 2

#define MAX_MENU_STRING 5
#endif
