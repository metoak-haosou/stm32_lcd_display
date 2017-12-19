
/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "bsp/led/bsp_led.h"

/* ˽�����Ͷ��� --------------------------------------------------------------*/
/* ˽�к궨�� ----------------------------------------------------------------*/
/* ˽�б��� ------------------------------------------------------------------*/
/* ��չ���� ------------------------------------------------------------------*/
/* ˽�к���ԭ�� --------------------------------------------------------------*/
/* ������ --------------------------------------------------------------------*/

/**
  * ��������: ����LED��IO���ų�ʼ��.
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ����ʹ�ú궨�巽������������źţ����������ֲ��ֻҪ���޸�bsp_led.h
  *           �ļ���غ궨��Ϳ��Է����޸����š�
  */
void LED_GPIO_Init(void)
{
   /* ����IOӲ����ʼ���ṹ����� */
  GPIO_InitTypeDef GPIO_InitStructure;
	
	/* ʹ��(����)LED1���Ŷ�ӦIO�˿�ʱ�� */  
  RCC_APB2PeriphClockCmd(LED1_RCC_CLOCKGPIO|LED2_RCC_CLOCKGPIO , ENABLE);
  
  /* �趨LED1��Ӧ����IO��� */
  GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;  
  /* �趨LED1��Ӧ����IO�������ٶ� ��GPIO_Speed_50MHz */
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  /* �趨LED1��Ӧ����IOΪ���ģʽ */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
  /* ��ʼ��LED1��Ӧ����IO */
  GPIO_Init(LED1_GPIO, &GPIO_InitStructure);
 
  /* �趨LED2��Ӧ����IO��� */
  GPIO_InitStructure.GPIO_Pin = LED2_GPIO_PIN;  
  /* ��ʼ��LED2��Ӧ����IO */
  GPIO_Init(LED2_GPIO, &GPIO_InitStructure);
  
  /* �����������Ϊ�͵�ƽ����ʱLED1�� */
  GPIO_SetBits(LED1_GPIO,LED1_GPIO_PIN);  
  /* �����������Ϊ�͵�ƽ����ʱLED2�� */
  GPIO_SetBits(LED2_GPIO,LED2_GPIO_PIN);  

}

/**
  * ��������: ���ð���LED�Ƶ�״̬
  * �������: LEDx:����x������Ϊ(1,2,3)����ѡ���Ӧ��LED��
  * ���������state:����LED�Ƶ����״̬��
  *             ��ѡֵ��LED_OFF��LED����
  *             ��ѡֵ��LED_ON�� LED������
  * �� �� ֵ: ��
  * ˵    �����ú���ʹ�����Ʊ�׼�⺯���ı�̷��������������׼�⺯�����˼�롣
  */
void LEDx_StateSet(uint8_t LEDx,LEDState_TypeDef state)
{
  /* �����������Ƿ�Ϸ� */
  assert_param(IS_LED_TYPEDEF(LEDx));
  assert_param(IS_LED_STATE(state));
  
  /* �ж����õ�LED��״̬���������ΪLED���� */
  if(state==LED_OFF)
  {
    if(LEDx & LED1)            
      GPIO_ResetBits(LED1_GPIO,LED1_GPIO_PIN);/* �����������Ϊ�͵�ƽ����ʱLED1�� */
    if(LEDx & LED2)
      GPIO_ResetBits(LED2_GPIO,LED2_GPIO_PIN);/* �����������Ϊ�͵�ƽ����ʱLED2�� */  
  }
  else  /* state=LED_ON ����������LED��Ϊ�� */
  {
    if(LEDx & LED1)
      GPIO_SetBits(LED1_GPIO,LED1_GPIO_PIN);/* �����������Ϊ�ߵ�ƽ����ʱLED1�� */
    if(LEDx & LED2)
      GPIO_SetBits(LED2_GPIO,LED2_GPIO_PIN);/* �����������Ϊ�ߵ�ƽ����ʱLED2�� */
  }
}

/******************* (C) COPYRIGHT 2015-2020 ӲʯǶ��ʽ�����Ŷ� *****END OF FILE****/