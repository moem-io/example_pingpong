#ifndef __SYS_CFG_H
#define __SYS_CFG_H
#include "stm32f1xx_hal.h"
#include "stm32f1xx_nucleo.h"
#endif

extern void printf_init(void);
extern void bt_init(void);
extern void BT_Transmit(uint8_t * aTxBuffer,int TXBUFFERSIZE);
extern void BT_Receive_IT(uint8_t * aRxBuffer);
