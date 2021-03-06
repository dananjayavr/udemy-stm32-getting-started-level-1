/*
 * uart.h
 *
 *  Created on: 4 déc. 2021
 *      Author: dananjaya
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"

/**
 * @brief UART1 GPIO Configuration
 */
void uart_UART1_GPIO_config(void);

/**
 * @brief UART1 Peripheral Configuration
 */
void uart_UART1_config(void);

/**
 * @brief UART1 Tx
 */
bool uart_UART1_Tx(uint8_t *data, uint8_t len, uint32_t timeout);

#endif /* INC_UART_H_ */

