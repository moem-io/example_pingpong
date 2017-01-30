/**
  ******************************************************************************
  * @file    UART/UART_Printf/Src/main.c
  * @brief   This example shows how to retarget the C library printf function
  *          to the UART.
  ******************************************************************************
  */

#include "main.h"

uint8_t aTxBuffer[] = "\n\rBT_TransmitTest+OK\n\r";
uint8_t aRxBuffer[RXBUFFERSIZE];


int main(void) {

  /* STM32F103xB HAL library initialization:
     - Configure the Flash prefetch
     - Systick timer is configured by default as source of time base, but user 
     can eventually implement his proper time base source (a general purpose 
     timer for example or other time source), keeping in mind that Time base 
     duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
     handled in milliseconds basis.
     - Set NVIC Group Priority to 4
     - Low Level Initialization
   */
  HAL_Init();

  /* Configure the system clock to 64 MHz */
  SystemClock_Config();
  Term_Init();
  BT_Init();

  printf("\n\rTERM_START+OK+\n\r");
  printf("\n\rBT_START+OK+\n\r");
	
	BT_Transmit(aTxBuffer, TXBUFFERSIZE);
	BT_Receive_IT(aRxBuffer);
	
  printf("** Test finished successfully. ** \n\r");

  while (1) {
  }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandler){
	printf("\n\r BT OR Printf Send Complete \n\r");
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandler){
	aRxBuffer[10]='\0';
	printf("%s",aRxBuffer);
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
