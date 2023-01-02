#include <stm32f4xx.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"
#include<string.h>
void Clock_Setting(void);
void xx();
UART_HandleTypeDef huart2;
void Error_handler(void);

	
int main()
{
	
HAL_Init();
//Clock_Setting();
HAL_MspInit();
UART2_init();
char *data = "testing";	
uint32_t len_data =strlen(data);	

HAL_UART_Transmit(&huart2, (uint8_t*)data, len_data, HAL_MAX_DELAY);

	return 0;	
}
//void Clock_Setting(void)
//{

//}
void HAL_MspInit(void)
{
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	SCB->SHCSR|=0x07<<16;
	HAL_NVIC_SetPriority(MemoryManagement_IRQn,0,0);
	HAL_NVIC_SetPriority(BusFault_IRQn,0,0);
	HAL_NVIC_SetPriority(UsageFault_IRQn,0,0);
	
}
void UART2_init()
{
	huart2.Instance=USART2;
	huart2.Init.BaudRate=115200;
	huart2.Init.WordLength=8;
	huart2.Init.Parity=UART_PARITY_NONE;
	huart2.Init.HwFlowCtl=UART_HWCONTROL_NONE;
	huart2.Init.HwFlowCtl=UART_HWCONTROL_NONE;
	huart2.Init.Mode=UART_MODE_TX_RX;
	if(HAL_UART_Init(&huart2)!=HAL_OK)
	{
	Error_handler();
	}
}	
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  GPIO_InitTypeDef gpio_uart;
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	gpio_uart.Pin=GPIO_PIN_2;
	gpio_uart.Mode=GPIO_MODE_AF_PP;
	gpio_uart.Speed=GPIO_SPEED_FREQ_LOW;
	gpio_uart.Alternate=GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &gpio_uart);
	
	gpio_uart.Pin=GPIO_PIN_3;
	HAL_GPIO_Init(GPIOA, &gpio_uart);
	
	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn,15,0); 
}



void Error_handler()
	{
	while(1)
{
	
	}
}

void SysTick_Handler (void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}