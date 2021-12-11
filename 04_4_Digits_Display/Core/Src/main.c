#include "main.h"

int main(void)
{
  //uint8_t digitsData[4] = {1,2,3,4};
  uint16_t counter = 0;

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
  // config LED display GPIO pins
  gpio_tm1637_config();
  // config LED display
  tm1637_init(GPIOB, DIGIT_CLK_PIN, DIGIT_DATA_IO);

  //tm1637_writeDigits(digitsData, false);


  printf("Program is starting...\r\n");
  while(1)
  {
    tm1637_setCounter(counter);
    counter++;
    if(counter > 9999)
      counter = 0;
    gpio_LED_writeRed(gpio_SS1_read());
    //gpio_LED_writeGreen(gpio_SS2_read());
    gpio_LED_writeGreen(gpio_PB_read());
    printf("Hello, STM32 World!\r\n");
    rcc_msDelayTicks(1000);
  }
}
