#include "peripheral_init.h"

#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

static void Error_Handler(void);

void printf_init(){
  huart2.Instance        = USART2;

  huart2.Init.BaudRate   = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits   = UART_STOPBITS_1;
  huart2.Init.Parity     = UART_PARITY_NONE;
  huart2.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
  huart2.Init.Mode       = UART_MODE_TX_RX;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
}

void bluetooth_init(){
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

PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}

static void Error_Handler(void)
{
  while (1)
  {
  }
}
