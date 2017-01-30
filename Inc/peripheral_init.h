#ifndef __SYS_CFG_H
#define __SYS_CFG_H
#include "stm32f1xx_hal.h"
#include "stm32f1xx_nucleo.h"
#endif

void Term_Init(void);
void Term_Receive_IT(uint8_t * aRxBuffer);
void BT_Init(void);
void BT_Transmit(uint8_t * aTxBuffer,int TXBUFFERSIZE);
void BT_Receive_IT(uint8_t * aRxBuffer);
