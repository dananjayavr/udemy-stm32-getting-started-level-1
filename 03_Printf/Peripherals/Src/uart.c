/*
 * uart.h
 *
 *  Created on: 4 déc. 2021
 *      Author: dananjaya
 */

#include "uart.h"

/**
 * @brief UART1 GPIO Configuration
 */
void uart_UART1_GPIO_config(void) {
  // PA9 = Tx
  // PA10 = Rx

  // Enable Port A clock
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
  // Mode to alternate function (UART1)
  GPIOA->CRH &= ~(GPIO_CRH_CNF9);
  GPIOA->CRH |= GPIO_CRH_CNF9_1;

  GPIOA->CRH &= ~(GPIO_CRH_CNF10);
  GPIOA->CRH |= GPIO_CRH_CNF10_0;

  // Output max 10 MHz
  GPIOA->CRH &= ~(GPIO_CRH_MODE9);
  GPIOA->CRH |= GPIO_CRH_MODE9_0;

  GPIOA->CRH &= ~(GPIO_CRH_MODE10);
  // Map PA9, PA10 to UART1
  AFIO->MAPR &= ~(AFIO_MAPR_USART1_REMAP);

}

/**
 * @brief UART1 Peripheral Configuration
 */
void uart_UART1_config(void) {
  // Enable UART1 clock
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
  // Enable Tx
  USART1->CR1 |= USART_CR1_TE;
  // Parity to Even
  USART1->CR1 &= ~(USART_CR1_PS);
  // Parity control enable
  USART1->CR1 &= ~(USART_CR1_PCE);
  // Word length to 8-bits
  USART1->CR1 &= ~(USART_CR1_M);
  // Stop bits to be 1
  USART1->CR2 &= ~(USART_CR2_STOP);
  // Disable HW flow control
  USART1->CR3 &= ~(USART_CR3_CTSE);
  USART1->CR3 &= ~(USART_CR3_RTSE);
  // Set baudrate to 115200
  USART1->BRR = 0;
  USART1->BRR |= (39UL << 4); // Mantissa
  USART1->BRR |= (1UL << 0); // Fraction
  // Clear some flags
  USART1->CR2 &= ~(USART_CR2_LINEN | USART_CR2_CLKEN);
  USART1->CR3 &= ~(USART_CR3_SCEN | USART_CR3_HDSEL | USART_CR3_IREN);

  // Enalbe UART peripheral
  USART1->CR1 |= USART_CR1_UE;

}

/**
 * @brief UART1 Tx
 */
bool uart_UART1_Tx(uint8_t *data, uint8_t len, uint32_t timeout) {
  // wait on TXE to start transmit
  // write to DR as TXE flag is HIGH (Tx buffer empty)
  uint8_t dataIdx = 0;
  uint32_t startTick = rcc_msGetTicks();
  while(dataIdx < len) {
    if(USART1->SR & USART_SR_TXE) // Tx buffer empty
    {
      USART1->DR = data[dataIdx];
      dataIdx++;
    }
    else
    {
      if((rcc_msGetTicks() - startTick) >= timeout) return false;
    }
  }
  // wait for busy flag
  while(USART1->SR & USART_SR_TC)
  {
    if((rcc_msGetTicks() - startTick) >= timeout) return false;
  }
  return true;
}
