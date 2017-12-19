#ifndef __BSP_KEY_H__
#define __BSP_KEY_H__

/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include <stm32f10x.h>

/* ���Ͷ��� ------------------------------------------------------------------*/
typedef enum
{
  KEY_UP   = 0,
  KEY_DOWN = 1,
}KEYState_TypeDef;
#define IS_KEY_STATE(STATE)           ((STATE) == KEY_UP) || ((STATE) == KEY_DOWN))

/* �궨�� --------------------------------------------------------------------*/
#define KEY1_RCC_CLOCKCMD             RCC_APB2PeriphClockCmd
#define KEY1_RCC_CLOCKGPIO            RCC_APB2Periph_GPIOC
#define KEY1_GPIO_PIN                 GPIO_Pin_10
#define KEY1_GPIO                     GPIOC
#define KEY1_INPUT_LEVEL              GPIO_ReadInputDataBit(KEY1_GPIO,KEY1_GPIO_PIN)
#define KEY1_DOWN_LEVEL               1  /* ���尴��KEY1����ʱ�Ǹߵ�ƽΪ1�������ǵ͵�ƽΪ0������ֵ��ԭ��ͼ����*/
#define KEY1_RCC_CLOCKAFIO            RCC_APB2Periph_AFIO
#define KEY1_GPIO_PORTSOURCE          GPIO_PortSourceGPIOC
#define KEY1_GPIO_PINSOURCE           GPIO_PinSource10
#define KEY1_EXITLINE                 EXTI_Line10
#define KEY1_IRQCHANNEL               EXTI15_10_IRQn
#define KEY1_IRQHANDLER               EXTI15_10_IRQHandler

#define KEY2_RCC_CLOCKCMD             RCC_APB2PeriphClockCmd
#define KEY2_RCC_CLOCKGPIO            RCC_APB2Periph_GPIOB
#define KEY2_GPIO_PIN                 GPIO_Pin_6
#define KEY2_GPIO                     GPIOB
#define KEY2_INPUT_LEVEL              GPIO_ReadInputDataBit(KEY2_GPIO,KEY2_GPIO_PIN)
#define KEY2_DOWN_LEVEL               0  
#define KEY2_RCC_CLOCKAFIO            RCC_APB2Periph_AFIO
#define KEY2_GPIO_PORTSOURCE          GPIO_PortSourceGPIOB
#define KEY2_GPIO_PINSOURCE           GPIO_PinSource6
#define KEY2_EXITLINE                 EXTI_Line6
#define KEY2_IRQCHANNEL               EXTI9_5_IRQn
#define KEY2_IRQHANDLER               EXTI9_5_IRQHandler

#define KEY3_RCC_CLOCKCMD             RCC_APB2PeriphClockCmd
#define KEY3_RCC_CLOCKGPIO            RCC_APB2Periph_GPIOE
#define KEY3_GPIO_PIN                 GPIO_Pin_4
#define KEY3_GPIO                     GPIOE
#define KEY3_INPUT_LEVEL              GPIO_ReadInputDataBit(KEY3_GPIO,KEY3_GPIO_PIN)
#define KEY3_DOWN_LEVEL               0  
#define KEY3_RCC_CLOCKAFIO            RCC_APB2Periph_AFIO
#define KEY3_GPIO_PORTSOURCE          GPIO_PortSourceGPIOE
#define KEY3_GPIO_PINSOURCE           GPIO_PinSource4
#define KEY3_EXITLINE                 EXTI_Line4
#define KEY3_IRQCHANNEL               EXTI4_IRQn
#define KEY3_IRQHANDLER               EXTI4_IRQHandler


#define IRQ_DISABLE                   __set_PRIMASK(1)		/* �ر����ж� */  
#define IRQ_ENABLE                    __set_PRIMASK(0)		/* �������ж� */ 

/* ��չ���� ------------------------------------------------------------------*/
/* �������� ------------------------------------------------------------------*/
void KEY_GPIO_Init(void);
#endif  // __BSP_KEY_H__

/******************* (C) COPYRIGHT 2015-2020 ӲʯǶ��ʽ�����Ŷ� *****END OF FILE****/
