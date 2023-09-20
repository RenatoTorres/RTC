#include "platform_types.h"
#include "RTC_TFPT1206L1002FM.h"

#define _DEBUG_RTC_API  0

/**
 * @brief Binary search to find the temperature based on datasheet values.
 *
 * This function performs a binary search on the TFPT_Vishay_Values array to find the
 * temperature corresponding to a target resistance ratio.
 *
 * @param targetRatio The target resistance ratio for which to find the temperature.
 * @return The temperature in degrees Celsius if a match or approximate match is found,
 *         or -273.0f (absolute zero) if the ratio is out of range.
 */
static float getTemp_Datasheet(float targetRatio) {
    int low = 0;
    int high = sizeof(TFPT_Vishay_Values) / sizeof(TFPT_Vishay_Values[0]) - 1;
    int resultIndex = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (TFPT_Vishay_Values[mid].fRatio_R25 == targetRatio) {
            resultIndex = mid;
            break;
        }

        if (TFPT_Vishay_Values[mid].fRatio_R25 < targetRatio) {
            low = mid + 1;
        } else {
            resultIndex = mid;
            high = mid - 1;
        }
    }

    if (resultIndex != -1) {
        // Found the exact match or the next lower fRatio
        if (resultIndex > 0) {
            // Use linearization between 2 datasheet points to optimize accuracy
            // fTx = fT1 + ((fRx - fR1)/(fR2 - fR1))*(T2 - T1);
            // (T2 - T1) is always 1 oC
            float fT1 = TFPT_Vishay_Values[resultIndex - 1].ftemperature;
            float fT2 = TFPT_Vishay_Values[resultIndex].ftemperature;
            float fR1 = TFPT_Vishay_Values[resultIndex - 1].fRatio_R25;
            float fR2 = TFPT_Vishay_Values[resultIndex].fRatio_R25;
            float fTx = fT1 + ((targetRatio - fR1) / (fR2 - fR1));
            
            #if( _DEBUG_RTC_API == 1)
            printf("getTemp_Datasheet(targetRatio=%f, fT1=%f, fT2=%f, fR1=%f, fR2=%f) => fTx = %f\n", targetRatio, fT1, fT2, fR1, fR2, fTx);
            #endif

            return fTx;
        }
        else 
        {
            #if( _DEBUG_RTC_API == 1)
            printf("getTemp_Datasheet(targetRatio=%f, fTx=%f\n", targetRatio, TFPT_Vishay_Values[resultIndex].ftemperature);
            #endif
        
            return TFPT_Vishay_Values[resultIndex].ftemperature;
        }
    } else {
        // Return 'absolute zero' in case of ratio out of range
        return -273.0f;
    }
}

/**
 * @brief Calculate the resistance ratio from an ADC value.
 *
 * This function calculates the resistance ratio based on a 12-bit ADC value and
 * the characteristics of the TFPT1206L1002FM sensor.
 *
 * @param uiADCVal The ADC value obtained from the sensor.
 * @return The resistance ratio.
 */
static float getRatioFromADCValue(uint16_t uiADCVal) {
    // 12-bit ADC => 2^12 = 4096
    // Range:
    // 0V   - 0
    // 2.5V - 4095

    // R213 = [(uiADCVal) / (VREF - uiADCVal)] * R600
    // However, R600 is 10K and R213 (TFPT1206L1002FM) is 10K on 25 oC.
    // R213/R600 = datasheet_ratio itself

    uint16_t VREF = 4095;
    float diff = (float) (VREF - uiADCVal);
    float fratio = ((float)(uiADCVal)) / ((float) diff) ;

    #if( _DEBUG_RTC_API == 1)
    printf("getRatioFromADCValue(%hu) => %f\n", uiADCVal, fratio);
    #endif

    return fratio;
}

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
float getTemperature(uint16_t uiADCVal) {
    return getTemp_Datasheet(getRatioFromADCValue(uiADCVal));
}
