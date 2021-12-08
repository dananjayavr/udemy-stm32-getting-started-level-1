/*
 * gpio.h
 *
 *  Created on: Dec 7, 2021
 *      Author: dananjaya
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include "main.h"

/*
 * @brief LED GPIO configuration
 * PB13 = Green
 * PB14 = Red
 */
void gpio_LED_config(void);

/*
 * @brief GPIO write/toggle functions
 */
void gpio_LED_writeGreen(bool state);
void gpio_LED_writeRed(bool state);
void gpio_LED_toggleGreen(void);
void gpio_LED_toggleRed(void);

#endif /* INC_GPIO_H_ */