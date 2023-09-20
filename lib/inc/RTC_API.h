#ifndef TFPT_SENSOR_LIBRARY_H
#define TFPT_SENSOR_LIBRARY_H

#include "platform_types.h"

/**
 * @brief Get the temperature in degrees Celsius from an ADC value.
 *
 * This function calculates the temperature in degrees Celsius based on the ADC
 * value obtained from the sensor and the datasheet values.
 *
 * @param uiADCVal The ADC value obtained from the sensor.
 * @return The temperature in degrees Celsius if within the valid range,
 *         or -273.0f (absolute zero) if out of range.
 */
float getTemperature(uint16_t uiADCVal);

#endif // TFPT_SENSOR_LIBRARY_H
