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

#define TOGGLE_BIT(REG, BIT) ((REG) ^= (BIT))


#endif /* INC_MAIN_H_ */
