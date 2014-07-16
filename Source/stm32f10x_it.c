#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "usart.h"
#include "can.h"
#include "obd.h"

static u8 i;
static u8 usart1_rx_cnt;
	
void USART1_IRQHandler(void){
	printf("usart1 irq");							//TEST USART1 IRQ
	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET) {
		USART1->SR;									//���TCλʱ��USART1->SR;USART1->DR;		
		USART1->DR;									//�ڶ໺������USART_ClearFlag(USART1, USART_IT_TC);
		DMA_Cmd(DMA1_Channel5, DISABLE);			//�ر�DMAͨ��5��USART1_RX),����Ա������ݴ���ʱ���������ݸ���
		usart1_rx_cnt = DMA_GetCurrDataCounter(DMA1_Channel5);		//DMA�жϽ������ݸ���
//		printf("%c %c %c", RxBuffer1[0], RxBuffer1[1], RxBuffer1[2]);	//��ӡ�����ڣ����������Ƿ���ȷ
		for(i=0; i<usart1_rx_cnt; i++){
			if(usart1_rx_buf[i] != 0x55){
				continue;
			}
			if(usart1_rx_buf[i+1] != 0xaa){
				continue;
			}
			
			if(usart1_rx_buf[i+4] != 0x0d){
				continue;
			}
			if(usart1_rx_buf[i+5] != 0x0a){
				continue;
			}
			obd_mode = usart1_rx_buf[i+2];
			obd_pid = usart1_rx_buf[i+3];
			printf("mode,pid = %02x,%02x", obd_mode, obd_pid);
			break;
		}
		DMA_SetCurrDataCounter(DMA1_Channel5, USART1_RX_BUF_SIZE);
		DMA_Cmd(DMA1_Channel5, ENABLE);
	}
}

void CAN1_RX0_IRQHandler(void){
	CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
	printf("RX DATA IS:%02x,%02x,%02x,%02x,%02x,%02x,%02x,%02x", \
	RxMessage.Data[0], RxMessage.Data[1], RxMessage.Data[2], RxMessage.Data[3], \
	RxMessage.Data[4], RxMessage.Data[5], RxMessage.Data[6], RxMessage.Data[7]);
	
}

void DMA1_Channel5_IRQHandler(void){
	//printf("dma\r\n");
	if(DMA_GetITStatus(DMA1_IT_TC5) == SET){		//�տ�ʼ��DMA1_IT_TC5д��DMA_IT_TC������һֱ��DMA_IT_TC
		DMA_ClearITPendingBit(DMA1_IT_TC5);			//���³���һֱ����DMA�ж�
		printf("USART1 RX IS OVERFLOW\r\n");
	}
}
