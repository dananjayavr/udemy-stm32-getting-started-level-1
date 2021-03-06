#include "main.h"
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
  // config GPIO LED
  gpio_LED_config();
  // config GPIO PB
  gpio_PB_config();
  // config Slide switches
  gpio_SS_config();

  printf("Program is starting...\r\n");
  while(1)
  {
    gpio_LED_writeRed(gpio_SS1_read());
    //gpio_LED_writeGreen(gpio_SS2_read());
    gpio_LED_writeGreen(gpio_PB_read());
    printf("Hello, STM32 World!\r\n");
    rcc_msDelayTicks(1000);
  }
}
