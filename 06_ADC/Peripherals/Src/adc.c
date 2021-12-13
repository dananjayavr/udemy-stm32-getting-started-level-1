/*
 * adc.c
 *
 *  Created on: 12 déc. 2021
 *      Author: danan
 */


#include "adc.h"

void adc_GPIO_config(void) {
  // Enable Port A clock
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

  // Mode = Input Mode & Input Configuration = Analog
  // PA1
  CLEAR_BIT(GPIOA->CRL, GPIO_CRL_MODE1);
  CLEAR_BIT(GPIOA->CRL, GPIO_CRL_CNF1);
  // PA2
  CLEAR_BIT(GPIOA->CRL, GPIO_CRL_MODE2);
  CLEAR_BIT(GPIOA->CRL, GPIO_CRL_CNF2);
  // PA3
  CLEAR_BIT(GPIOA->CRL, GPIO_CRL_MODE2);
  CLEAR_BIT(GPIOA->CRL, GPIO_CRL_CNF2);
}

void adc_SingleChannelConfig(ADC_SingleSelect_e channel) {
  // Enable ADC clock
  RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
  // Right aligned
  CLEAR_BIT(ADC1->CR2, ADC_CR2_ALIGN);
  // Single conversion
  CLEAR_BIT(ADC1->CR2, ADC_CR2_CONT);
  // Software trigger
  SET_BIT(ADC1->CR2, ADC_CR2_SWSTART);
  // SET_BIT(ADC1->CR2, ADC_CR2_EXTSEL);
  // Sample time 28 cycles (12 + 28 / 12 MHz = 3.3us)
  // PA1
  CLEAR_BIT(ADC1->SMPR2, ADC_SMPR2_SMP1);
  SET_BIT(ADC1->SMPR2, ADC_SMPR2_SMP1_0 | ADC_SMPR2_SMP1_1);
  // PA2
  CLEAR_BIT(ADC1->SMPR2, ADC_SMPR2_SMP2);
  SET_BIT(ADC1->SMPR2, ADC_SMPR2_SMP2_0 | ADC_SMPR2_SMP2_1);
  // PA3
  CLEAR_BIT(ADC1->SMPR2, ADC_SMPR2_SMP3);
  SET_BIT(ADC1->SMPR2, ADC_SMPR2_SMP3_0 | ADC_SMPR2_SMP3_1);
  // Number of conversion = 1
  CLEAR_BIT(ADC1->SQR1, ADC_SQR1_L);
  // Rank 1 Channel1, channel2 and channel3
  ADC1->SQR3 = channel;
  // Power up ADC
  SET_BIT(ADC1->CR2, ADC_CR2_ADON);
  // Wait for ADC to stabilize (waiting 1-2 us)
  for(uint16_t i=0; i<36;i++);
}

void adc_Start(void) {
  ADC1->SR = 0;
  SET_BIT(ADC1->CR2,ADC_CR2_SWSTART);
  SET_BIT(ADC1->CR2,ADC_CR2_ADON);
}

void adc_Stop(void) {
  ADC1->SR = 0;
  CLEAR_BIT(ADC1->CR2,ADC_CR2_SWSTART);
}

bool adc_PollforEOC(uint32_t timeout) {
  uint32_t startTicks = rcc_msGetTicks();
  while((ADC1->SR & 0x02) == 0) {     // 0x02 = EOC Flag
    if((rcc_msGetTicks() - startTicks) > timeout) {
      return false;
    }
  }
  return true;
}

uint16_t adc_ReadValue(void) {
  return (ADC1->DR & 0xFFF); // & 0xFFF to make sure output value is 12-bits.
}

void adc_EnableEOC_IT(void) {
  // Enable EOC IT enable flag
  SET_BIT(ADC1->CR1, ADC_CR1_EOCIE);
  // ADC NVIC interrupt
  NVIC_EnableIRQ(ADC1_IRQn);
}

void adc_DisableEOC_IT(void) {
  // Enable EOC IT enable flag
  CLEAR_BIT(ADC1->CR1, ADC_CR1_EOCIE);
  // ADC NVIC interrupt
  NVIC_DisableIRQ(ADC1_IRQn);
}


void adc_MultiChannelConfig(void) {
  // Enable ADC1 Clock
  RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
  // Right Align
  CLEAR_BIT(ADC1->CR2, ADC_CR2_ALIGN);
  // Sample Time (28.5 cycles x3 => 12 bits + 28 cycles / 12 MHz => 3.375 us)
  // PA1
  CLEAR_BIT(ADC1->SMPR2, ADC_SMPR2_SMP1);
  SET_BIT(ADC1->SMPR2, ADC_SMPR2_SMP1_0 | ADC_SMPR2_SMP1_1);
  // PA2
  CLEAR_BIT(ADC1->SMPR2, ADC_SMPR2_SMP2);
  SET_BIT(ADC1->SMPR2, ADC_SMPR2_SMP2_0 | ADC_SMPR2_SMP2_1);
  // PA3
  CLEAR_BIT(ADC1->SMPR2, ADC_SMPR2_SMP3);
  SET_BIT(ADC1->SMPR2, ADC_SMPR2_SMP3_0 | ADC_SMPR2_SMP3_1);
  // Software Trigger
  SET_BIT(ADC1->CR2, ADC_CR2_SWSTART);
  // SET_BIT(ADC1->CR2, ADC_CR2_EXTSEL); // Same as above
  // Sequencer
  // Rank1 => PA1 = channel number to be converted = channel1 (pot)
  ADC1->SQR3 = (1UL << 0*5);
  // Rank2 => PA2 = channel number to be converted = channel2 (x axis)
  ADC1->SQR3 = (2UL << 1*5);
  // Rank3 => PA3 = channel number to be converted = channel3 (y axis)
  ADC1->SQR3 = (3UL << 2*5);
  // Number of conversion (3)
  CLEAR_BIT(ADC1->SQR1, ADC_SQR1_L);
  SET_BIT(ADC1->SQR1, ADC_SQR1_L_1);
  // Enable Scan mode
  SET_BIT(ADC1->CR1, ADC_CR1_SCAN);
  // Enable DMA (from ADC registers)
  SET_BIT(ADC1->CR2, ADC_CR2_DMA);
  // Single conversion mode
  CLEAR_BIT(ADC1->CR2, ADC_CR2_CONT);
  // Power up ADC
  SET_BIT(ADC1->CR2, ADC_CR2_ADON);
  // Wait for ADC to stabilize (waiting 1-2 us)
  for(uint16_t i=0; i<36;i++);
}

void adc_MultiChannelDMAConfig(uint16_t *pAdcBuffer) {
  // Enable DMA Clock
  //
}
