#include "RTC_TFPT1206L1002FM.h"

// Binary search to find the temperature based on datasheet
static float getTemp_Datasheet(float targetRatio) {
    int low = 0;
    int high = sizeof(TFPT_Vishay_Values) / sizeof(TFPT_Vishay_Values[0]) - 1;
    int resultIndex = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (TFPT_Vishay_Values[mid].fRatio_R25 == targetRatio)
        {
            resultIndex = mid;
            break;
        }

        if (TFPT_Vishay_Values[mid].fRatio_R25 < targetRatio)
        {
            low = mid + 1;
        }
        else
        {
            resultIndex = mid;
            high = mid - 1;
        }
    }

    if (resultIndex != -1)
    {
        // Found the exact match or the next lower fRatio
        if( resultIndex > 0)
        {
            //fTx = fT1 + ((fRx - fR1)/(fR2 - fR1))*(T2 - T1);
            float fT1 = TFPT_Vishay_Values[resultIndex-1].ftemperature;
            float fT2 = TFPT_Vishay_Values[resultIndex].ftemperature;
            float fR1 = TFPT_Vishay_Values[resultIndex-1].fRatio_R25;
            float fR2 = TFPT_Vishay_Values[resultIndex].fRatio_R25;
            float fTx = fT1 + ((targetRatio - fR1)/(fR2 - fR1));
            return fTx;
        }
        else
        {
            return TFPT_Vishay_Values[resultIndex].ftemperature;
        }
    }
    else
    {
        // Return 'absolute zero' in case of ratio out of range
        return -273.0;
    }
}

static float getRatioFromADCValue(uint16_t uiADCVal)
{

    uint16_t VREF = 4095;
    float fratio = 

    return 

}

float getTemperature(uint16_t uiADCVal, float fvref, float R1)
{

}