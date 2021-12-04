#include "main.h"
#include "rcc.h"

int main(void)
{
  // configure max clock speed (72 MHz)
  rcc_HSE_config();
  // configure SysTick timer
  rcc_SysTick_config(1000); // 72 000 000  / 72 000 => 1000
  while(1)
  {

  }
}
