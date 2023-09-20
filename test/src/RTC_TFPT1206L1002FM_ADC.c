#include "platform_types.h"
#include "RTC_TFPT1206L1002FM_ADC.h"

uint16_t getADCfromTemp(float targetRatio) {
    int low = 0;
    int high = sizeof(TFPT_Vishay_Values_ADC) / sizeof(TFPT_Vishay_Values_ADC[0]) - 1;
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