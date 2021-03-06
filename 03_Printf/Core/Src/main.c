#include "main.h"
#include "uart.h"
#include <stdio.h>

int main(void)
{
  // configure max clock speed (72 MHz)
  rcc_HSE_config();
  // configure SysTick timer
  rcc_SysTick_config(72000); // 72 000 000  / 72 000 => 1000
  // configure UART peripheral
  uart_UART1_GPIO_config();
  uart_UART1_config();
  printf("Program is starting...\r\n");
  while(1)
  {
    printf("Hello, STM32 World!\r\n");
    rcc_msDelayTicks(1000);
  }
}
