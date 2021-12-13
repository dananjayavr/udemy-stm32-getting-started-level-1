#include "main.h"

bool adcEoc = false;
uint16_t adcValue = 0;

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

  // ADC
  adc_GPIO_config();
  adc_SingleChannelConfig(ADC_SingleSelect_Potentiometer);
  //adc_SingleChannelConfig(ADC_SingleSelect_Joystick_x);
  adc_EnableEOC_IT();

  printf("Program is starting...\r\n");
  adc_Start();
  while(1)
  {
    if(adcEoc)
    {
      adcEoc = false;
      adcValue = adc_ReadValue();
      printf("Potentiometer = %d\r\n", (int)adcValue);
      adc_Start();
    }

    gpio_LED_toggleGreen();
    rcc_msDelayTicks(300);
  }
}

void ADC1_2_IRQHandler(void) {
  if(ADC1->SR & ADC_SR_EOC) {
    adcValue = adc_ReadValue();
    NVIC_ClearPendingIRQ(ADC1_IRQn);
    adcEoc = true;
    gpio_LED_toggleRed();
  }
}
