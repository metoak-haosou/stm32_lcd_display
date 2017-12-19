
#ifndef   __BSP_LCD__
#define   __BSP_LCD__

#include  "stm32f10x.h"

//��Ļ��ʼʱ��ʾ��ʽ��ע�⣺��IDelayʱ��ʾ��һ��������������ˢ�µ�
//��ʱ�����ֶ���ˢ�½��������  LCD_WR_REG(0x0007,0x0173);������ʾ
//��Immediatelyʱû�б�ע�͵��ǲ���Ҫ�˹���

/* ѡ��BANK1-BORSRAM1 ���� TFT����ַ��ΧΪ0X60000000~0X63FFFFFF
 * FSMC_A16 ��LCD��DC(�Ĵ���/����ѡ��)��
 * 16 bit => FSMC[24:0]��ӦHADDR[25:1]
 * �Ĵ�������ַ = 0X60000000
 * RAM����ַ = 0X60020000 = 0X60000000+2^16*2 = 0X60000000 + 0X20000 = 0X60020000
 * ��ѡ��ͬ�ĵ�ַ��ʱ����ַҪ���¼��㡣
 */
#define Bank1_LCD_D    ((u32)0x60020000)    //Disp Data ADDR
#define Bank1_LCD_C    ((u32)0x60000000)	   //Disp Reg ADDR

#define Set_Rst GPIOD->BSRR = GPIO_Pin_13;
#define Clr_Rst GPIOD->BRR  = GPIO_Pin_13;

#define Lcd_Light_ON   GPIOA->BSRR = GPIO_Pin_3;
#define Lcd_Light_OFF  GPIOA->BRR  = GPIO_Pin_3;

/*����һ������*/
struct word_struct{
	u8 num;
	u16 data[16];
};
/*����һ���ַ������㡢��ĸ*/
struct char_struct{
	u8 num;
	u8 data[16];
};

void lcd_init(void);//��ʼ��LCD
void lcd_draw_box(u16 x,u16 y,u16 xLong,u16 yLong,u16 Color);//��ָ��λ�û�һ��ָ���ľ��ο�
void lcd_draw_pixel(u16 x, u16 y, u16 Color);//��ָ��λ����ʾһ����
void lcd_flush_toolbar(void);//ˢ��toolbar
void lcd_put_char(u16 x,u16 y,u16 background,u16 word_color,u8 num);//��ָ��λ����ʾһ���ַ�
void lcd_put_word(u16 x,u16 y,u16 background,u16 word_color,u8 num);//��ָ��λ����ʾһ������
void lcd_display_allchar(void);//��ʾ�����ַ�
void lcd_display_allword(void);//��ʾ���к���
void lcd_display_menu(u16 choice);//��ʾmunu���Թ��û�ѡ��
void lcd_menu_choice_down(void);//��ʾ�������ƶ�
void lcd_menu_choice_up(void);//��ʾ�������ƶ�
void lcd_menu_choice_confirm(void);//ȷ�ϵ�ǰѡ�����������
void lcd_WriteComm(u16 CMD);
void lcd_WriteData(u16 tem_data);
void lcd_WR_Start(void);
void lcd_set_area_to_display(u16 x_start,u16 x_end,u16 y_start,u16 y_end);

#define X_START 	(0) 
#define X_END   	(319)
#define Y_START 	(0)
#define Y_END		(239)

#define IMAGE_X_START 	X_START 
#define IMAGE_X_END   	X_END
#define IMAGE_Y_START 	(20)
#define IMAGE_Y_END		Y_END

#define TOOLBAR_X_START 	X_START 
#define TOOLBAR_X_END   	X_END
#define TOOLBAR_Y_START 	Y_START
#define TOOLBAR_Y_END		(20)

/*������ɫ*/

#define TOOLBAR_COLOR 0x1111
#define CHOOSE_COLOR 0xeeee
#define INIT_COLOR 0xffff
            
#define BIT(data,num) (((data) & (1<<(num)))>>(num))


/*��ʾһЩ�ض��ַ���*/
#define DISPLAY_TEST_C(x,y,background,color) \
	   lcd_put_word(x,y,background,color,0) \
	   lcd_put_word(x,y,background,color,0)

#define CMD_NONE 0
#define CMD_LED1 1
#define CMD_LED2 2
#define CMD_LED3 3
#define CMD_LED4 4
#define CMD_EXIT 5


#define MAX_MENU_STRING 5
#endif