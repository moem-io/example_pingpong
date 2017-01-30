/**
  ******************************************************************************
  * @file    UART/UART_Printf/Inc/main.h
  * @brief   Header for main.c module
  ******************************************************************************
  */

#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f1xx_hal.h"
#include "stm32f1xx_nucleo.h"
#include "stdio.h"
#include "sys_cfg.h"
#include "peripheral_init.h"

/* Size of Trasmission buffer */
#define TXBUFFERSIZE                      (COUNTOF(aTxBuffer) - 1)
/* Size of Reception buffer */
#define RXBUFFERSIZE                      TXBUFFERSIZE
  
/* Exported macro ------------------------------------------------------------*/
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))
/* Exported functions ------------------------------------------------------- */

#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
