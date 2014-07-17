#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "dma.h"
#include "nvic.h"
#include "usart.h"
#include "can.h"
#include "obd.h"
#include <stdio.h>

int main(void){
	usart1_init();
	can1_init();
	nvic_init();
	dma_init();
	
	while(1){
		if((obd_mode != 0xff) && (obd_pid != 0xff)){
			obd_cmd_parse(obd_mode, obd_pid);
		}
//		while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
//		while(DMA_GetFlagStatus(DMA1_FLAG_TC4) == RESET);
	}
}

#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
	
PUTCHAR_PROTOTYPE
{
  USART_SendData(USART1, (uint8_t) ch);
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}
  return ch;
}
