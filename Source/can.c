#include "stm32f10x.h"
#include "can.h"

CanTxMsg	TxMessage;
CanRxMsg	RxMessage;

void can1_init(void){
	
	GPIO_InitTypeDef			GPIO_InitStructure;
	CAN_InitTypeDef				CAN_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);	//ENABLE RCC_AFIO,RCC_GPIOA
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);						//ENABLE RCC_CAN1
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;			//GPIOA_11 = CAN_RX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;			//GPIOA_12 = CAN_TX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = STBY_PIN;				//2561 STBY PIN
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(STBY_GPIO, &GPIO_InitStructure);
	GPIO_ResetBits(STBY_GPIO, STBY_PIN);				//CLEAR STBY

	CAN_DeInit(CAN1);
	CAN_StructInit(&CAN_InitStructure);
	CAN_InitStructure.CAN_TTCM = DISABLE;
	CAN_InitStructure.CAN_ABOM = DISABLE;
	CAN_InitStructure.CAN_AWUM = DISABLE;
	CAN_InitStructure.CAN_NART = DISABLE;
	CAN_InitStructure.CAN_RFLM = DISABLE;
	CAN_InitStructure.CAN_TXFP = ENABLE;
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
	CAN_InitStructure.CAN_SJW  = CAN_SJW_1tq;
	CAN_InitStructure.CAN_BS1  = CAN_BS1_3tq;
	CAN_InitStructure.CAN_BS2  = CAN_BS2_2tq;
	CAN_InitStructure.CAN_Prescaler = 12;		//BUAT RATE 500khz
	CAN_Init(CAN1, &CAN_InitStructure);			//INIT CAN1
	
	can1_filter_config();
	
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);	//CAN1 INT ENABLE
	
	TxMessage.StdId = 0x7df;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.DLC = 0;
	
	printf("CAN INIT OK\r\n");
	
}

static void can1_filter_config(void){		//CAN1 FILTER CONFIG
	
	CAN_FilterInitTypeDef		CAN_FilterInitStructure;
	
	CAN_FilterInitStructure.CAN_FilterNumber = 0;
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdList;
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh = ((u32)0x07df<<5);
	CAN_FilterInitStructure.CAN_FilterIdLow = CAN_RTR_DATA | CAN_ID_STD;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0xffff;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0xffff;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
	
	CAN_FilterInitStructure.CAN_FilterNumber = 1;
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdList;
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh = ((u32)0x07e8<<5);
	CAN_FilterInitStructure.CAN_FilterIdLow = CAN_RTR_DATA | CAN_ID_STD;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0xffff;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0xffff;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
	
}

void can1_transmit_str(u8 *pdata){
	u8 i;
	
	TxMessage.StdId = 0x7df;
//	TxMessage.ExtId = 0x00;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.DLC = sizeof(pdata) - 1;
	TxMessage.Data[0] = sizeof(pdata) - 2;
	for(i=0; i<TxMessage.Data[0]; i++){
		TxMessage.Data[i] = *(pdata + i);
	}
	CAN_Transmit(CAN1, &TxMessage);
	
}

void can1_transmit_buf(u8 *pdata, u8 num){
	u8 i;
	
	TxMessage.StdId = 0x7df;
//	TxMessage.ExtId = 0x00;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.DLC = num + 1;
	TxMessage.Data[0] = num;
	for(i=0; i<TxMessage.Data[0]; i++){
		TxMessage.Data[i] = *(pdata + i);
		printf("%d", TxMessage.Data[i]);
	}
	CAN_Transmit(CAN1, &TxMessage);
	
}
