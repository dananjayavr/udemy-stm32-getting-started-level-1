/*
 * main.h
 *
 *  Created on: Dec 2, 2021
 *      Author: dananjaya
 */

#ifndef INC_MAIN_H_
#define INC_MAIN_H_

#include "stm32f1xx.h"
#include <stdbool.h>
#include <stdio.h>

#include "rcc.h"
#include "gpio.h"
#include "uart.h"
#include "tm1637.h"
#include "exti.h"

#define TOGGLE_BIT(REG, BIT) ((REG) ^= (BIT))

// TM1637 digit pins
#define DIGIT_PORT      GPIOB
#define DIGIT_CLK_PIN   (1UL << 10)
#define DIGIT_DATA_IO   (1UL << 11)


#endif /* INC_MAIN_H_ */
