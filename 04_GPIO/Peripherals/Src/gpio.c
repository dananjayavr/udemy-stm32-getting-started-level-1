/*
 * gpio.c
 *
 *  Created on: Dec 7, 2021
 *      Author: dananjaya
 */

#include "gpio.h"

// Bit-banding stuff
#define BB_BASE_ADDR      0x42000000
#define GPIOB_ODR_OFFSET  (0x10C00 + 0x0C)
#define BB_PIN_13         13
#define BB_PIN_14         14
#define PB13_ODR_BB_ADDR  *(uint32_t *)(BB_BASE_ADDR + GPIOB_ODR_OFFSET*32 + BB_PIN_13*4)
#define PB14_ODR_BB_ADDR  *(uint32_t *)(BB_BASE_ADDR + GPIOB_ODR_OFFSET*32 + BB_PIN_14*4)

// Bit-banding with CMSIS
#define GPIOA_IDR_OFFSET  (GPIOA_BASE - PERIPH_BASE + 0x08) // 0x08 comes from the manual, page 172
#define BB_PIN_0          0
#define PA0_IDR_BB_ADDR  *(uint32_t *)(PERIPH_BB_BASE + GPIOA_IDR_OFFSET*32 + BB_PIN_0*4)

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
#if 0
  if(state)
  {
    SET_BIT(GPIOB->ODR, GPIO_ODR_ODR13);
  }
  else
  {
    CLEAR_BIT(GPIOB->ODR, GPIO_ODR_ODR13);
  }
#endif
  PB13_ODR_BB_ADDR = state;
}

void gpio_LED_writeRed(bool state) {
#if 0
  if(state)
  {
    //SET_BIT(GPIOB->ODR, GPIO_ODR_ODR14);
    *(uint32_t *)0x40010C0C |= GPIO_ODR_ODR14; // same as above, writing to actual address

  }
  else
  {
    CLEAR_BIT(GPIOB->ODR, GPIO_ODR_ODR14);
  }
#endif
  PB14_ODR_BB_ADDR = state;
}

void gpio_LED_toggleGreen(void) {
  TOGGLE_BIT(GPIOB->ODR,GPIO_ODR_ODR13);
}

void gpio_LED_toggleRed(void) {
  TOGGLE_BIT(GPIOB->ODR,GPIO_ODR_ODR14);
}

void gpio_PB_config(void) {
  // Enable clock port A
  SET_BIT(RCC->APB2ENR,RCC_APB2ENR_IOPAEN);
  // Input mode
  CLEAR_BIT(GPIOA->CRL, GPIO_CRL_MODE0);
  // Floating
  CLEAR_BIT(GPIOA->CRL, GPIO_CRL_CNF0);
  SET_BIT(GPIOA->CRL, GPIO_CRL_CNF0_0);
}

bool gpio_PB_read(void) {
  //return (bool)(GPIOA->IDR & GPIO_IDR_IDR0);
  //return 0;
  return (bool)PA0_IDR_BB_ADDR;
}

void gpio_SS_config(void) {
  // PA8
  // Enable clock port A
  SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPAEN);
  // Input mode
  CLEAR_BIT(GPIOA->CRH, GPIO_CRH_MODE8);
  // Floating
  CLEAR_BIT(GPIOA->CRH, GPIO_CRH_CNF8);
  SET_BIT(GPIOA->CRH, GPIO_CRH_CNF8_0);

  // PA15
  // Enable clock port A
  SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPAEN);
  // Input mode
  CLEAR_BIT(GPIOA->CRH, GPIO_CRH_MODE15);
  // Floating
  CLEAR_BIT(GPIOA->CRH, GPIO_CRH_CNF15);
  SET_BIT(GPIOA->CRH, GPIO_CRH_CNF15_0);
  // Remap PA15 from JTAG to IO
  SET_BIT(RCC->APB2ENR,  RCC_APB2ENR_AFIOEN);
  SET_BIT(RCC->APB2ENR, RCC_APB1ENR_PWREN);
  CLEAR_BIT(AFIO->MAPR, AFIO_MAPR_SWJ_CFG);
  SET_BIT(AFIO->MAPR, AFIO_MAPR_SWJ_CFG_1);

}

bool gpio_SS1_read(void) {
  return (bool)(GPIOA->IDR & GPIO_IDR_IDR8);
}
bool gpio_SS2_read(void) {
  return (bool)(GPIOA->IDR & GPIO_IDR_IDR15);
}
