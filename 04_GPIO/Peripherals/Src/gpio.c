/*
 * gpio.c
 *
 *  Created on: Dec 7, 2021
 *      Author: dananjaya
 */

#include "gpio.h"

void gpio_LED_config(void) {
  // Enable Port B clock
  RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
  // Mode to output
  CLEAR_BIT(GPIOB->CRH, GPIO_CRH_MODE13);
  SET_BIT(GPIOB->CRH, GPIO_CRH_MODE13_1);
  CLEAR_BIT(GPIOB->CRH, GPIO_CRH_MODE14);
  SET_BIT(GPIOB->CRH, GPIO_CRH_MODE14_1);
  // Push/Pull
  CLEAR_BIT(GPIOB->CRH, GPIO_CRH_CNF13);
  CLEAR_BIT(GPIOB->CRH, GPIO_CRH_CNF14);
}

void gpio_LED_writeGreen(bool state) {
  if(state)
  {
    SET_BIT(GPIOB->ODR, GPIO_ODR_ODR13);
  }
  else
  {
    CLEAR_BIT(GPIOB->ODR, GPIO_ODR_ODR13);
  }
}

void gpio_LED_writeRed(bool state) {
  if(state)
  {
    SET_BIT(GPIOB->ODR, GPIO_ODR_ODR14);
  }
  else
  {
    CLEAR_BIT(GPIOB->ODR, GPIO_ODR_ODR14);
  }
}

void gpio_LED_toggleGreen(void) {
  TOGGLE_BIT(GPIOB->ODR,GPIO_ODR_ODR13);
}

void gpio_LED_toggleRed(void) {
  TOGGLE_BIT(GPIOB->ODR,GPIO_ODR_ODR14);
}