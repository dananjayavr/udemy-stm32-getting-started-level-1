/*
 * exti.c
 *
 *  Created on: 11 déc. 2021
 *      Author: danan
 */

#include "exti.h"

// PA0
void exti_buttonConfig(void) {
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
  // PA0 = MUX source (EXTI0)
  SET_BIT(AFIO->EXTICR[0], AFIO_EXTICR1_EXTI0_PA);
  // Unblock EXTI0 interrupt
  SET_BIT(EXTI->IMR, EXTI_IMR_IM0);
  // Edge-detection (enable rising edge / disable falling-edge)
  SET_BIT(EXTI->RTSR, EXTI_RTSR_RT0);
  CLEAR_BIT(EXTI->FTSR, EXTI_FTSR_FT0);
  // Enable NVIC interrupt
  NVIC_SetPriority(EXTI0_IRQn,5);
  NVIC_EnableIRQ(EXTI0_IRQn);
}
