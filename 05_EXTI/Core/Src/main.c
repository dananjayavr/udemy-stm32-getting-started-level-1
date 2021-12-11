#include "main.h"

bool extiFlag = 0;

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
  // exti config
  exti_buttonConfig();

  printf("Program is starting...\r\n");
  while(1)
  {
    if(extiFlag) {
      extiFlag = false;
      printf("EXTI0 Fired.\r\n");
      rcc_msDelayTicks(200);
      SET_BIT(EXTI->IMR, EXTI_IMR_IM0); // Enable EXTI0_IRQn
    }
  }
}

void EXTI0_IRQHandler(void) {
  NVIC_ClearPendingIRQ(EXTI0_IRQn);
  SET_BIT(EXTI->PR, EXTI_PR_PIF0); // Clear pending interrupt also
  CLEAR_BIT(EXTI->IMR, EXTI_IMR_IM0); // Masking it

  extiFlag = true;
  gpio_LED_toggleGreen();
}
