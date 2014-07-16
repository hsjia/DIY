#include "stm32f10x.h"
#include "usart.h"

u8 usart1_tx_buf[USART1_TX_BUF_SIZE];
u8 usart1_rx_buf[USART1_RX_BUF_SIZE];

void usart1_init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);	//ENABLE RCC_GPIOA AND RCC_AFIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;			//PA10 RX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;			//PA9 TX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//ENABLE RCC_USART1
	USART_DeInit(USART1);			//DEINIT USART1
	USART_InitStructure.USART_BaudRate = 38400;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1, &USART_InitStructure);			//INIT USART1
	
	USART_SendData(USART1, (uint8_t) 0x00);				//FOR CLEAR TXE
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	
	USART_Cmd(USART1, ENABLE);							//ENABLE USART1
	USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
	
	printf("USART1 INIT OK\r\n");
}

