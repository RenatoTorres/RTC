/*
 * unittests.c
 *
 *  Created on: Jun 28, 2023
 *      Author: charles
 */

#include <stdio.h>
#include "unittests.h"
#include "platform_types.h"
#include "RTC_API.h"

#include <math.h>

GROUP_SETUP(RTC_API_TempVsADC)
{
	
}

GROUP_TEARDOWN(RTC_API_TempVsADC)
{
	
}

DEFINE_TEST_CASE(RTC_API_TempVsADC, TEMP_0)
{
	ASSERT_TRUE_TEXT( (fabs(getTemperature(1940) - 0.0f) < 0.5f)  , "Expected Temperature for 0 degrees");
}

DEFINE_TEST_CASE(RTC_API_TempVsADC, TEMP_45)
{
	ASSERT_TRUE_TEXT( ( fabs(getTemperature(2130) - 56.0f ) < 0.5f), "Expected Temperature for 45 degrees");
}

DEFINE_TEST_CASE(RTC_API_TempVsADC, RANGE_0_45)
{
	for(int i = 0; i<46; i++)
	{
		uint16_t adcVal = getADCfromTemp( i );
		ASSERT_TRUE_TEXT( ( fabs(getTemperature(adcVal) - ((float)i) ) < 0.5f), "Expected Temperature for CORRECT for 0-45 degrees");
	}
}



TEST_GROUP_RUNNER(RTC_API_TempVsADC)
{
	INIT_TEST_GROUP(RTC_API_TempVsADC);
	RUN_TEST_CASE(RTC_API_TempVsADC, TEMP_0);
	RUN_TEST_CASE(RTC_API_TempVsADC, TEMP_45);
}

