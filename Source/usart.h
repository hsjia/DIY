
#ifndef __USART_H
#define __USART_H

#define USART1_TX_BUF_SIZE 128
#define USART1_RX_BUF_SIZE 128

extern u8 usart1_tx_buf[USART1_TX_BUF_SIZE];
extern u8 usart1_rx_buf[USART1_RX_BUF_SIZE];

void usart1_init(void);

#endif
