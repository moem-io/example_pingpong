/**
  ******************************************************************************
  * @file    UART/UART_Printf/Src/main.c
  * @brief   This example shows how to retarget the C library printf function
  *          to the UART.
  ******************************************************************************
  */

#include "main.h"
#define TRANSMITTER_BOARD
uint8_t BTRole[] = "AT+ROLE1";
uint8_t BTConn[] = "AT+CONB4994C57C4CF";

uint8_t aTxBuffer[] = "\n\rBT_TransmitTest+OK\n\r";
uint8_t aRxBuffer[RXBUFFERSIZE];

uint8_t ping[] = "\n\rPING+OK\n\r";
uint8_t pong[] = "\n\rPONG+OK\n\r";

__IO ITStatus UartReady = RESET;

int main(void) {
  HAL_Init();
  SystemClock_Config();

  Term_Init();
  BT_Init();

  printf("\n\rTERM_START+OK+\n\r");
  printf("\n\rBT_START+OK+\n\r");

#ifdef TRANSMITTER_BOARD
//              BT_Transmit(BTRole, COUNTOF(BTRole)-1);
//  BT_Transmit(BTConn, COUNTOF(BTConn)-1);
  BT_Transmit(ping, PINGSIZE);
#endif

  BT_Receive_IT(aRxBuffer, PINGSIZE);

  printf("** Test finished successfully. ** \n\r");

  while (1) {
    if (UartReady == SET) {
      UartReady = RESET;
      printf("\n\rArray is : %s \n\r", aRxBuffer);
      BT_Receive_IT(aRxBuffer, PINGSIZE);
    }
  }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef * UartHandler) {
  UartReady = SET;
  aRxBuffer[10] = '\0';
  BT_Transmit(aRxBuffer, PINGSIZE);
}


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t * file, uint32_t line) {
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  while (1) {
  }
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
