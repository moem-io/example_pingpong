#include "peripheral_init.h"

#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif				/* __GNUC__ */

UART_HandleTypeDef huart2;

UART_HandleTypeDef huart3;

static void Error_Handler(void);

void Term_Init() {
  huart2.Instance = USART2;

  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  if (HAL_UART_Init(&huart2) != HAL_OK) {
    Error_Handler();
  }
}

void BT_Init() {
  huart3.Instance = USART3;

  huart3.Init.BaudRate = 9600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  if (HAL_UART_Init(&huart3) != HAL_OK) {
    Error_Handler();
  }
}

PUTCHAR_PROTOTYPE {
  HAL_UART_Transmit(&huart2, (uint8_t *) & ch, 1, 0xFFFF);

  return ch;
}

void Term_Receive_IT(uint8_t * aRxBuffer) {
  if (HAL_UART_Receive_IT(&huart2, (uint8_t *) aRxBuffer, 10) != HAL_OK) {
    printf("HAL_UART_Receive_IT() Error\n\r");
  }
}

void USART3_IRQHandler(void) {
  HAL_UART_IRQHandler(&huart3);
}

void BT_Transmit(uint8_t * aTxBuffer, int TXBUFFERSIZE) {
  if (HAL_UART_Transmit(&huart3, (uint8_t *) aTxBuffer, TXBUFFERSIZE, 5000) != HAL_OK) {
    printf("HAL_UART_Transmit() Error\n\r");
  }
}

void BT_Receive_IT(uint8_t * aRxBuffer) {
  /* set RXNE FLAG to 0 by Reading DR Register */
  uint8_t temp = 0;

  uint32_t tmp_state = 0;

  tmp_state = __HAL_UART_GET_FLAG(&huart3, UART_FLAG_RXNE);
  if (tmp_state == SET) {
    temp = (uint8_t) (huart3.Instance->DR & (uint8_t) 0x00FF);
		(void) temp; // suppress unused var warning
  }

  /* or Directly CLEAR RXNE Register - ** Error with CLEAR RXNE.** */
//  __HAL_UART_CLEAR_FLAG(&huart3, UART_FLAG_RXNE);
  if (HAL_UART_Receive_IT(&huart3, (uint8_t *) aRxBuffer, 10) != HAL_OK) {
    printf("HAL_UART_Receive_IT() Error\n\r");
  }
}

static void Error_Handler(void) {
  while (1) {
    printf("Initialize Error");
  }
}
