

/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "bsp/key/bsp_key.h"
#include "bsp/LCD/bsp_LCD.h"



/**
  * ��������: �򵥴ֱ�����ʱ����
  * �������: time����ʱʱ������
  * �� �� ֵ: ��
  * ˵    ���������ڰ����뵯�����̴��ڶ�����һ����Ҫ��������������������򵥷���
  *           ���Ǽ���ʱ��
  */
void KEY_ScanDelay(void)
{  
  uint32_t i,j;
  for(i=0;i<100;++i)
    for(j=0;j<1000;++j){ }
}
/**
  * ��������: ����KEY1��Ϊ�ж����Ų�ʹ���ж�
  * �����������
  * �� �� ֵ: ��
  * ˵    ������������KEY1Ϊ�������жϣ��鿴������ԭ��ͼ��֪��KEY1��û������ʱPA0Ϊ
  *           �͵�ƽ(�����������ý��)�����Ե����ǰ��°���ʱ����һ���ӵ͵�ƽ��Ϊ��
  *           ��ƽ���̣�stm32f103оƬ���԰�����̼����������������������Դ��Ϳ�
  *           ����stm32�Ѽ�⵽���ƽ�仯��Ϣ���߸����ǣ��Ӷ�����֪�������ǵĶ���
  *           Ч����������һ����������
  */
void KEY1_EXIT_Config(void)
{
  /* ����IOӲ����ʼ���ṹ����� */
  GPIO_InitTypeDef GPIO_InitStructure;
  /* �����ⲿ�ж��߳�ʼ���ṹ����� */
  EXTI_InitTypeDef EXTI_InitStructure;
  /* ����Ƕ�������жϿ�������ʼ���ṹ����� */
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Ϊ����IO�����жϹ�����Ҫʹ�ܸ��ù���ʱ�� */
  KEY1_RCC_CLOCKCMD(KEY1_RCC_CLOCKGPIO | KEY1_RCC_CLOCKAFIO,ENABLE);
  
  /* �趨KEY1��Ӧ����IO��� */
  GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN;  
  /* �趨KEY1��Ӧ����IO�������ٶ� ��GPIO_Speed_50MHz */
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  /* �趨KEY1��Ӧ����IOΪ��������ģʽ */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
  /* ��ʼ��KEY1��Ӧ����IO */
  GPIO_Init(KEY1_GPIO, &GPIO_InitStructure);

  /* ѡ��PA0��Ϊ�ж�����Դ */
  GPIO_EXTILineConfig(KEY1_GPIO_PORTSOURCE,KEY1_GPIO_PINSOURCE);
  
  /* KEY1��Ӧ�Ķ��� */
  EXTI_InitStructure.EXTI_Line=KEY1_EXITLINE;
  /* �ⲿ�ж�ģʽ */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  /* �����ش�����ʽ */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  /* ʹ���ж� */
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  /* ����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ��� */
  EXTI_Init(&EXTI_InitStructure);
  
  /* ѡ���ж����ȼ�������Ϊ4����ռʽ���ȼ���4�������ȼ������Բο�misc.h�ļ��˽�������� */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* ʹ��KEY1���ڵ��ⲿ�ж�ͨ�� */
  NVIC_InitStructure.NVIC_IRQChannel = KEY1_IRQCHANNEL;
  /* ������ռʽ���ȼ�Ϊ2 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02; 
  /* ���������ȼ�Ϊ3 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;
  /* ʹ���ⲿ�ж�ͨ�� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
  /* ��ʼ������Ƕ�������жϿ����� */
  NVIC_Init(&NVIC_InitStructure); 
}

/**
  * ��������: ����KEY2��Ϊ�ж����Ų�ʹ���ж�
  * �����������
  * �� �� ֵ: ��
  * ˵    ������������KEY2Ϊ�½����жϣ��鿴������ԭ��ͼ��֪��KEY2��û������ʱPC0Ϊ
  *           �ߵ�ƽ(�����������ý��)�����Ե����ǰ��°���ʱ����һ���Ӹߵ�ƽ��Ϊ��
  *           ��ƽ���̣�stm32f103оƬ���԰�����̼����������������������Դ��Ϳ�
  *           ����stm32�Ѽ�⵽���ƽ�仯��Ϣ���߸����ǣ��Ӷ�����֪�������ǵĶ���
  *           Ч����������һ����������
  */
void KEY2_EXIT_Config(void)
{
  /* ����IOӲ����ʼ���ṹ����� */
  GPIO_InitTypeDef GPIO_InitStructure;
  /* �����ⲿ�ж��߳�ʼ���ṹ����� */
  EXTI_InitTypeDef EXTI_InitStructure;
  /* ����Ƕ�������жϿ�������ʼ���ṹ����� */
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Ϊ����IO�����жϹ�����Ҫʹ�ܸ��ù���ʱ�� */
  KEY2_RCC_CLOCKCMD(KEY2_RCC_CLOCKGPIO | KEY2_RCC_CLOCKAFIO,ENABLE);
  
  /* �趨KEY2��Ӧ����IO��� */
  GPIO_InitStructure.GPIO_Pin = KEY2_GPIO_PIN;  
  /* �趨KEY2��Ӧ����IO�������ٶ� ��GPIO_Speed_50MHz */
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  /* �趨KEY2��Ӧ����IOΪ��������ģʽ */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
  /* ��ʼ��KEY2��Ӧ����IO */
  GPIO_Init(KEY2_GPIO, &GPIO_InitStructure);

  /* ѡ��KEY2��Ϊ�ж�����Դ */
  GPIO_EXTILineConfig(KEY2_GPIO_PORTSOURCE,KEY2_GPIO_PINSOURCE);
  
  /* KEY2��Ӧ���ж��� */
  EXTI_InitStructure.EXTI_Line=KEY2_EXITLINE;
  /* �ⲿ�ж�ģʽ */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  /* �½��ش�����ʽ */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  /* ʹ���ж� */
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  /* ����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ��� */
  EXTI_Init(&EXTI_InitStructure);
  
  /* ѡ���ж����ȼ�������Ϊ4����ռʽ���ȼ���4�������ȼ������Բο�misc.h�ļ��˽�������� */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* ʹ��KEY2���ڵ��ⲿ�ж�ͨ�� */
  NVIC_InitStructure.NVIC_IRQChannel = KEY2_IRQCHANNEL;
  /* ������ռʽ���ȼ�Ϊ1 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01; 
  /* ���������ȼ�Ϊ1 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
  /* ʹ���ⲿ�ж�ͨ�� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
  /* ��ʼ������Ƕ�������жϿ����� */
  NVIC_Init(&NVIC_InitStructure); 
}



/**
  * ��������: ����KEY3��Ϊ�ж����Ų�ʹ���ж�
  * �����������
  * �� �� ֵ: ��
  * ˵    ����
  */
void KEY3_EXIT_Config(void)
{
  /* ����IOӲ����ʼ���ṹ����� */
  GPIO_InitTypeDef GPIO_InitStructure;
  /* �����ⲿ�ж��߳�ʼ���ṹ����� */
  EXTI_InitTypeDef EXTI_InitStructure;
  /* ����Ƕ�������жϿ�������ʼ���ṹ����� */
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Ϊ����IO�����жϹ�����Ҫʹ�ܸ��ù���ʱ�� */
  KEY3_RCC_CLOCKCMD(KEY3_RCC_CLOCKGPIO | KEY3_RCC_CLOCKAFIO,ENABLE);
  
  /* �趨KEY3��Ӧ����IO��� */
  GPIO_InitStructure.GPIO_Pin = KEY3_GPIO_PIN;  
  /* �趨KEY3��Ӧ����IO�������ٶ� ��GPIO_Speed_50MHz */
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  /* �趨KEY3��Ӧ����IOΪ��������ģʽ */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
  /* ��ʼ��KEY3��Ӧ����IO */
  GPIO_Init(KEY3_GPIO, &GPIO_InitStructure);

  /* ѡ��KEY3��Ϊ�ж�����Դ */
  GPIO_EXTILineConfig(KEY3_GPIO_PORTSOURCE,KEY3_GPIO_PINSOURCE);
  
  /* KEY3��Ӧ���ж��� */
  EXTI_InitStructure.EXTI_Line=KEY3_EXITLINE;
  /* �ⲿ�ж�ģʽ */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  /* �½��ش�����ʽ */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  /* ʹ���ж� */
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  /* ����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ��� */
  EXTI_Init(&EXTI_InitStructure);
  
  /* ѡ���ж����ȼ�������Ϊ4����ռʽ���ȼ���4�������ȼ������Բο�misc.h�ļ��˽�������� */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* ʹ��KEY3���ڵ��ⲿ�ж�ͨ�� */
  NVIC_InitStructure.NVIC_IRQChannel = KEY3_IRQCHANNEL;
  /* ������ռʽ���ȼ�Ϊ1 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01; 
  /* ���������ȼ�Ϊ1 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
  /* ʹ���ⲿ�ж�ͨ�� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
  /* ��ʼ������Ƕ�������жϿ����� */
  NVIC_Init(&NVIC_InitStructure); 
}
/**
  * ��������: ���ذ���IO���ų�ʼ��.
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ����ʹ�ú궨�巽������������źţ����������ֲ��ֻҪ���޸�bsp_key.h
  *           �ļ���غ궨��Ϳ��Է����޸����š�
  */
void KEY_GPIO_Init(void)
{
    KEY1_EXIT_Config();
	KEY2_EXIT_Config();
	KEY3_EXIT_Config();
}



/**
  * ��������: KEY1�жϷ�����
  * �����������
  * �� �� ֵ: ��
  * ˵    ������stm32f103��⵽�½����źź���Զ������Ӧ���жϷ����������ǿ�����
  *           ��������ʵ��һЩ������
  */
void KEY1_IRQHANDLER(void)
{
  /* ȷ���Ƿ������EXTI Line�ж� */
	if(EXTI_GetITStatus(KEY1_EXITLINE) != RESET)
	{
		/*do something*/	
		lcd_menu_choice_up()  ;
    /* ����жϱ�־λ	*/
		EXTI_ClearITPendingBit(KEY1_EXITLINE);     
	}
}

/**
  * ��������: KEY2�жϷ�����
  * �����������
  * �� �� ֵ: ��
  * ˵    ������stm32f103��⵽�½����źź���Զ������Ӧ���жϷ����������ǿ�����
  *           ��������ʵ��һЩ������
  */
void KEY3_IRQHANDLER(void)
{
  /* ȷ���Ƿ������EXTI Line�ж� */
	if(EXTI_GetITStatus(KEY3_EXITLINE) != RESET)
	{
	/*do something*/
	lcd_menu_choice_down();
    /* ����жϱ�־λ	*/
		EXTI_ClearITPendingBit(KEY3_EXITLINE);     
	}
}

/**
  * ��������: KEY2�жϷ�����
  * �����������
  * �� �� ֵ: ��
  * ˵    ������stm32f103��⵽�½����źź���Զ������Ӧ���жϷ����������ǿ�����
  *           ��������ʵ��һЩ������
  */
void KEY2_IRQHANDLER(void)
{
  /* ȷ���Ƿ������EXTI Line�ж� */
	if(EXTI_GetITStatus(KEY2_EXITLINE) != RESET)
	{
    /*do something*/
	lcd_menu_choice_confirm();	
    /* ����жϱ�־λ	*/
		EXTI_ClearITPendingBit(KEY2_EXITLINE);     
	}
}
/*****END OF FILE****/