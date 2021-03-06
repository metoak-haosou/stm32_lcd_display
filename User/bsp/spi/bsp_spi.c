#include "bsp/spi/bsp_spi.h"
#include "bsp/LCD/bsp_LCD.h"
#include "bsp/led/bsp_led.h"
#include "stdlib.h"


u8 spi_status = SEARCH;

u16 frame_head_get_offset = 0;
u16 frame_head_length = FRAME_HEAD_SIZE;
u16 frame_head[FRAME_HEAD_SIZE/2];
u16 frame_data_get_offset = 0;
u16 frame_data_length = 0;
u16 frame_type = 0;
u16 frame_image_x = 0;
u16 frame_image_y = 0;
u16 frame_image_v = 0;
u16 frame_image_h = 0;
//中断优先级配置
void SPI_NIV_config(void)
{
NVIC_InitTypeDef NVIC_InitStructure;
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);     
NVIC_Init(&NVIC_InitStructure);
NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;      //SPI1通道
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//抢占优先级
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;    //子优先级
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   //通道使能
NVIC_Init(&NVIC_InitStructure);   
}
void SPI_init(void)          //SPI1配置函数
{
  SPI_InitTypeDef  SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  /* 使能 GPIOA 时钟 */  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
  /*SPI1外设时钟开 */  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
 /*引脚配置*/
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出，复用模式的输入输出由程序决定。
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //复用推挽输出，复用模式的输入输出由程序决定。
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  /* SPI1 工作方式配置 */
  SPI_Cmd(SPI1, DISABLE);   //配置前先关闭SPI
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //全双工工作模式。
  SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;      //设置SPI1为从模式。
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;  //数据位16位
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;  //空闲时刻为高，DSP那边也设为高。
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; //时钟相位，数据在第2个跳边沿被采集
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;     //CS引脚为软模式，即通过程序控制片选脚。 
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;  //256分频为波特率，因为波特率是由主机提供的。所以在这里设置没有意义。
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;//先传高字节，因为DSP只有高字节传送这种方式，所以这里要设置为高字节在前。不然就乱了。
  SPI_InitStructure.SPI_CRCPolynomial = 7;  //CRC多项式不设置，默认。
  SPI_Init(SPI1, &SPI_InitStructure);
  SPI_NIV_config();
  //为帧头分配空间
  SPI_Cmd(SPI1, ENABLE);   /* 使能 SPI1  */
  SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, ENABLE); //接收缓冲区数据非空中断，开启接收中断。
}
	
static void send_2_byte(u16 data)
{
	SPI_I2S_SendData(SPI1,data);
	//等待发送缓冲区为空
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_IT_TXE) == RESET);
}
static u16 get_2_byte(void)
{
	//等待接收完两个byte数据
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_IT_RXNE) == RESET);
	return SPI_I2S_ReceiveData(SPI1);
}
void send_fram(void *head,void * data)
{
	int i;
	int length = get_frame_length(head);
	//发送起始位
	send_2_byte(FRAME_START);
	//发送帧头
	for(i=0;i<3;i++)
		send_2_byte(*((u16 *)head+i));
	//发送数据
  	for(i=0;i<length;i++)
		send_2_byte(*((u16 *)data+i));
}
int i=320*240;
void SPI1_IRQHandler(void)
{
	
#ifdef  NO
/***************************************用于接收来自spi的图像或者其他数据***********************************************/	
/* 	 
*	整个接收过程分为三步，用状态位来作区别，默认状态为SEARCH
*	该模式的工作是找到同步的起始位，当找到起始位后，模式将被
*	切换到GET_HEAD,该模式的工作是接收帧头，在帧头中可以的到
*	当前帧的类型、帧号、后面数据的长度，当接收完帧头后，状态
*	将迁移到第三种状态GET_DATA,这个状态的工作是取得当前帧的
*	数据，数据有可能分为两段，前面部分是当前数据的额外描述部分
*	后面部分的数据是用来使用的数据，根据帧类型的不同对帧作相
*	应的处理。 
*/
	
	switch(spi_status){
	case SEARCH:
		if(FRAME_START == get_2_byte()){
			spi_status = GET_HEAD;//找到起始位就将状态设置为GET_HEAD
			frame_head_get_offset = 0;
		}
		break;
	case GET_HEAD:
		frame_head[frame_head_get_offset] = get_2_byte();
		frame_head_get_offset += 2;//偏移自增2
		//判断帧头是否接完，由于接收时使用的时两字节为一个单位，所以判断时需要除以2
		if(frame_head_get_offset >= frame_head_length){
			spi_status = GET_DATA;
			//为数据段分配数据
			frame_data_get_offset = 0;
			frame_type = get_frame_type(frame_head);
			frame_data_length = get_frame_length(frame_head);
		}
		break;
	case GET_DATA:
		/* 根据不同的帧类型定制不同处理方法 */
		switch(frame_type){
		case FRAME_TYPE_IMAGE:
			switch(frame_data_get_offset){
			case 0:
				//接收的第一个数据用于更新x坐标
				frame_image_x = get_2_byte();
				break;
			case 2:
				//接收的第二个数据用于更新y坐标
				frame_image_y = get_2_byte();
				break;
			case 4:
				//接收的第三个数据用于更新宽度
				frame_image_v = get_2_byte();
				break;
			case 6:
				//接收的第四个数据用于更新高度
				frame_image_h = get_2_byte();
				//根据接收到的起始点坐标和宽度和高度设置显示区域
				lcd_set_area_to_display(frame_image_x,frame_image_x+frame_image_v,frame_image_y,frame_image_y+frame_image_h);
				break;
			default:
				/* 接收的第五个以及到第frame_data_length个都用作数据 */
				lcd_WriteData(SPI_I2S_ReceiveData(SPI1));
				break;
			}
			frame_data_get_offset += 2;
			if(frame_data_get_offset>=frame_data_length){
				lcd_display_cmd();
				spi_status = SEARCH;//所有数据都接收完成了，将状态位设置为SEARCH，寻找下一帧
			}
			break;
		case FRAME_TYPE_STATUS:
			//保留后用
			break;
		case FRAME_TYPE_CMD:
			//保留后用
			break;
		default:
			/* 帧类型不匹配可能什么地方出现了差错，释放分配空间后重置状态 */
			spi_status = SEARCH;
			break;
		}
		break;
	default:
		spi_status = SEARCH;
		break;
	}
#endif
/***************************************用于测试spi接收显示图像***********************************************/
	if(!i--){
		lcd_set_area_to_display(X_START,X_END,Y_START,Y_END);
		LED1_TOGGLE;
		i=320*240;
	}
	lcd_WriteData(get_2_byte());
}


