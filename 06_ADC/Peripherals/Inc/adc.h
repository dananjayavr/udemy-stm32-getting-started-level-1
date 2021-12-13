/*
 * adc.h
 *
 *  Created on: 12 déc. 2021
 *      Author: danan
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#include "main.h"

// ADC Single Channel Select
typedef enum ADC_SingleSelect_TAG {
  ADC_SingleSelect_Potentiometer = 1,
  ADC_SingleSelect_Joystick_x,
  ADC_SingleSelect_Joystick_y,
} ADC_SingleSelect_e;

/*
 * @brief ADC GPIO pins: PA1 (Potentiometer), PA2 (X-Axis), PA3 (Y-axis)
 */
void adc_GPIO_config(void);

/*
 * @brief ADS Single Channel configuration
 */
void adc_SingleChannelConfig(ADC_SingleSelect_e channel);

/*
 * @brief ADC Start - SWSTART
 */
void adc_Start(void);

/*
 * @brief ADC Stop
 */
void adc_Stop(void);

/*
 * @brief ADC Poll for end of conversion
 */
bool adc_PollforEOC(uint32_t timeout);

/*
 * @brief ADC Read-value
 */
uint16_t adc_ReadValue(void);

/*
 * @brief ADC Enable/Disable Interrupt - EOC
 */
void adc_EnableEOC_IT(void);

void adc_DisableEOC_IT(void);


#endif /* INC_ADC_H_ */
