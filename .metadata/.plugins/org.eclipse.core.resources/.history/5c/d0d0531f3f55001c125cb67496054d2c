/*
 * uart.c
 *
 *  Created on: Mar 6, 2021
 *      Author: Dananjaya Ramanayake
 */

#include "main.h"

/**
 * @brief UART1 GPIO Configuration
 */
void uart_UART1_GPIO_config(void)
{
  // PA9 -> Tx PA10 -> Rx
  // Enable Port A clock
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
  // Mode to AF (UART1)
  GPIOA->CRH &= ~(GPIO_CRH_CNF9); // Clear PA 9
  GPIOA->CRH |= GPIO_CRH_CNF9_1; // Setting mode to output AF

  GPIOA->CRH &= ~(GPIO_CRH_CNF10); // Clear PA 10
  GPIOA->CRH |= GPIO_CRH_CNF10_0; // Setting mode to floating input (Rx not used)

  // Output max 10 MHz
  GPIOA->CRH &= ~(GPIO_CRH_MODE9); // Clearing output mode bitfield
  GPIOA->CRH |= GPIO_CRH_MODE9_0; // Mode to high (PA9)

  GPIOA->CRH &= ~(GPIO_CRH_MODE10); // Clearing output mode bitfield

  // Map PA9, PA10 to UART1
  AFIO->MAPR &= ~(AFIO_MAPR_USART1_REMAP);

}

/**
 * @brief UART1 Peripheral Configuration
 */
void uart_UART1_config(void)
{
  // Enable UART1 clock
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
  // Enable Tx
  USART1->CR1 |= USART_CR1_TE;
  // Parity to Even
  USART1->CR1 &= ~(USART_CR1_PS);
  // Parity Control Disabled
  USART1->CR1 &= ~(USART_CR1_PCE);
  // Word length to 8bits
  USART1->CR1 &= ~(USART_CR1_M);
  // Stop bits to 1
  USART1->CR2 &= ~(USART_CR2_STOP);
  // Disable HW flow control
  USART1->CR3 &= ~(USART_CR3_CTSE);
  USART1->CR3 &= ~(USART_CR3_RTSE);
  // Set baud rate to 115200
  USART1->BRR = 0;
  USART1->BRR |= (39UL << 4);
  USART1->BRR |= (1UL << 0);
  // Clear some flags and enable some
  USART1->CR2 &= ~(USART_CR2_LINEN | USART_CR2_CLKEN);
  USART1->CR3 &= ~(USART_CR3_SCEN | USART_CR3_HDSEL | USART_CR3_IREN);
  // Enable UART
  USART1->CR1 |= USART_CR1_UE;
}

/**
 * @brief UART1 Tx Configuration
 */
bool uart_UART1_Tx(uint8_t *data, uint8_t len, uint32_t timeout)
{
   //Wait on TXE to start transmit
   //Write to DR as TXE flag is HIGH (Tx buffer Empty)
   uint8_t dataIdx = 0;
   uint32_t startTick = rcc_msGetTicks();
   while(dataIdx<len)
   {
     if(USART1->SR & USART_SR_TXE) //Tx buffer empty
     {
       USART1->DR = data[dataIdx];
       dataIdx++;
     }
     else //Manage timeout
     {
       if((rcc_msGetTicks() - startTick)>= timeout) return false;
     }
   }
   //Wait for busy flag
   while(USART1->SR & USART_SR_TC)
   {
     if((rcc_msGetTicks() - startTick)>= timeout) return false;
   }
   return true;
}
