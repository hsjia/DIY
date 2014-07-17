#ifndef __CAN_H
#define __CAN_H

#define STBY_PIN	GPIO_Pin_7
#define STBY_GPIO	GPIOA

extern CanTxMsg	TxMessage;
extern CanRxMsg	RxMessage;

void can1_init(void);
static void can1_filter_config(void);
void can1_transmit_str(u8 *pdata);
void can1_transmit_buf(u8 *pdata, u8 num);

#endif
