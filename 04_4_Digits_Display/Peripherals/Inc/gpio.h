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

/*
 * @brief Button configuration (PA0)
 */
void gpio_PB_config(void);

/*
 * @brief Read push-button
 */
bool gpio_PB_read(void);

/*
 * @brief Slide switches configuration (PA8, PA15)
 */
void gpio_SS_config(void);

/*
 * @brief Read slide switches
 */
bool gpio_SS1_read(void);
bool gpio_SS2_read(void);

/*
 * @brief TM1637 LED Display GPIO pins configuration
 */
void gpio_tm1637_config(void);

#endif /* INC_GPIO_H_ */
