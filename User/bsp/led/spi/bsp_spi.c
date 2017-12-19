#include "bsp/spi/bsp_spi.h"
#include "bsp/LCD/bsp_LCD.h"
#include "bsp/led/bsp_led.h"
#include "stdlib.h"


u8 spi_status = SEARCH;

u16 frame_head_get_offset = 0;
u16 frame_head_length = FRAME_HEAD_SIZE;
u16 *frame_head = NULL;
u16 frame_data_get_offset = 0;
u16 frame_data_length = 0;
u16 *data_receive = NULL;
u16 frame_type = 0;
//�ж����ȼ�����
void SPI_NIV_config(void)
{
NVIC_InitTypeDef NVIC_InitStructure;
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);     
NVIC_Init(&NVIC_InitStructure);
NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;      //SPI1ͨ��
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;    //�����ȼ�
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   //ͨ��ʹ��
NVIC_Init(&NVIC_InitStructure);   
}
void SPI_init(void)          //SPI1���ú���
{
  SPI_InitTypeDef  SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  /* ʹ�� GPIOA ʱ�� */  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
  /*SPI1����ʱ�ӿ� */  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
 /*��������*/
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������������ģʽ����������ɳ��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //�����������������ģʽ����������ɳ��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  /* SPI1 ������ʽ���� */
  SPI_Cmd(SPI1, DISABLE);   //����ǰ�ȹر�SPI
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //ȫ˫������ģʽ��
  SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;      //����SPI1Ϊ��ģʽ��
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;  //����λ16λ
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;  //����ʱ��Ϊ�ߣ�DSP�Ǳ�Ҳ��Ϊ�ߡ�
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; //ʱ����λ�������ڵ�2�������ر��ɼ�
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;     //CS����Ϊ��ģʽ����ͨ���������Ƭѡ�š� 
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;  //256��ƵΪ�����ʣ���Ϊ���������������ṩ�ġ���������������û�����塣
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;//�ȴ����ֽڣ���ΪDSPֻ�и��ֽڴ������ַ�ʽ����������Ҫ����Ϊ���ֽ���ǰ����Ȼ�����ˡ�
  SPI_InitStructure.SPI_CRCPolynomial = 7;  //CRC����ʽ�����ã�Ĭ�ϡ�
  SPI_Init(SPI1, &SPI_InitStructure);
  SPI_NIV_config();
  //Ϊ֡ͷ����ռ�
  frame_head = (u16 *)malloc(8);
  SPI_Cmd(SPI1, ENABLE);   /* ʹ�� SPI1  */
  SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, ENABLE); //���ջ��������ݷǿ��жϣ����������жϡ�
}
	
static void send_2_byte(u16 data)
{
	SPI_I2S_SendData(SPI1,data);
	//�ȴ����ͻ�����Ϊ��
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_IT_TXE) == RESET);
}
static u16 get_2_byte(void)
{
	//�ȴ�����������byte����
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_IT_RXNE) == RESET);
	return SPI_I2S_ReceiveData(SPI1);
}
void send_fram(void *head,void * data)
{
	int i;
	int length = get_frame_length(head);
	//������ʼλ
	send_2_byte(FRAME_START);
	//����֡ͷ
	for(i=0;i<3;i++)
		send_2_byte(*((u16 *)head+i));
	//��������
  	for(i=0;i<length;i++)
		send_2_byte(*((u16 *)data+i));
}
int i=320*220;
void SPI1_IRQHandler(void)
{

#ifdef  NO
/***************************************���ڽ�������spi��ͼ�������������***********************************************/	
/* 	 
*	�������չ��̷�Ϊ��������״̬λ��������Ĭ��״̬ΪSEARCH
*	��ģʽ�Ĺ������ҵ�ͬ������ʼλ�����ҵ���ʼλ��ģʽ����
*	�л���GET_HEAD,��ģʽ�Ĺ����ǽ���֡ͷ����֡ͷ�п��Եĵ�
*	��ǰ֡�����͡�֡�š��������ݵĳ��ȣ���������֡ͷ��״̬
*	��Ǩ�Ƶ�������״̬GET_DATA,���״̬�Ĺ�����ȡ�õ�ǰ֡��
*	���ݣ������п��ܷ�Ϊ���Σ�ǰ�沿���ǵ�ǰ���ݵĶ�����������
*	���沿�ֵ�����������ʹ�õ����ݣ�����֡���͵Ĳ�ͬ��֡����
*	Ӧ�Ĵ��� 
*/
	
	switch(spi_status){
	case SEARCH:
		if(FRAME_START == get_2_byte()){
			spi_status = GET_HEAD;//�ҵ���ʼλ�ͽ�״̬����ΪGET_HEAD
			frame_head_get_offset = 0;
		}
		break;
	case GET_HEAD:
		frame_head[frame_head_get_offset] = get_2_byte();
		frame_head_get_offset += 2;//ƫ������2
		//�ж�֡ͷ�Ƿ���꣬���ڽ���ʱʹ�õ�ʱ���ֽ�Ϊһ����λ�������ж�ʱ��Ҫ����2
		if(frame_head_get_offset >= frame_head_length){
			spi_status = GET_DATA;
			//Ϊ���ݶη�������
			frame_data_get_offset = 0;
			frame_type = get_frame_type(frame_head);
			//Ϊ���ν�Ҫ���յ����ݷ���ռ�
			frame_data_length = get_frame_length(frame_head);
			data_receive = malloc(frame_data_length);
		}
		break;
	case GET_DATA:
		data_receive[frame_data_get_offset] = get_2_byte();
		frame_data_get_offset += 2;//����2
		/* ���ݲ�ͬ��֡���Ͷ��Ʋ�ͬ������ */
		switch(frame_type){
		case FRAME_TYPE_IMAGE:
			if(0 == frame_data_get_offset%(IMAGE_LINE_SIZE*2)){
				//data_receive�Ŀռ���������ط���ʹ�ã����Բ����ڷ���ĵط���ʼ��
				//��������ʹ���ߵ�
				lcd_prepare_to_display_line(0,0,frame_data_get_offset-IMAGE_LINE_SIZE,data_receive);
			}
			break;
		case FRAME_TYPE_STATUS:
			//��������
			break;
		case FRAME_TYPE_CMD:
			//��������
			break;
		default:
			/* ֡���Ͳ�ƥ�����ʲô�ط������˲���ͷŷ���ռ������״̬ */
			free(data_receive);
			spi_status = SEARCH;
			break;
		}
		break;
	default:
		spi_status = SEARCH;
		break;
	}

/***************************************���ڲ���spi����ͨ��***********************************************/	
	i++;
	if(i%100000==0){
		LED1_TOGGLE;
	
	}
	SPI_I2S_SendData(SPI1,SPI_I2S_ReceiveData(SPI1));
	if(i%167000==0){
		LED2_TOGGLE;
	}
#endif
/***************************************���ڲ���spi������ʾͼ��***********************************************/
	if(!i--){
		lcd_set_area_to_display(IMAGE_X_START,IMAGE_X_END,IMAGE_Y_START,IMAGE_Y_END);
		i=320*220;
	}
	lcd_WriteData(SPI_I2S_ReceiveData(SPI1));
}


