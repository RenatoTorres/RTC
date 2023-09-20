#include "platform_types.h"
#include "RTC_API.h"

void main()
{
    uint32_t uiloop = 1;
    uint16_t uiADCVal;

    while(uiloop)
    {
        printf("Value of ADC (12bit - 0 to 4095): ");
        scanf("%hu", &uiADCVal);

        if(uiADCVal == 0)
        {
            uiloop = 0;
            continue;
        }

        printf("ADC Value: %04hu => Temperature in Celsius: %02.2f\n", uiADCVal, getTemperature(uiADCVal));
    }
}