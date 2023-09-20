/*
 * unittest_framework.c
 *
 *  Created on: Jun 27, 2023
 *      Author: charles
 */

#include <stdio.h>
#include <string.h>
#include "unittest_framework.h"


#define UNIT_TEST_MAX_STR_LEN 256
#define RETURN_ON_NULL(ptr, rtn) if(ptr == NULL) return rtn
#define BASE_GROUP_SIZE 10

char* resultStrings[] = {"OK!", "FAIL!", "ERROR!"};

#define GET_RESULT_STRING(result_type) result_type >= NUM_RESULT_TYPES ? "INVALID" : resultStrings[result_type];
static void test_log(const char* s);
static void print_current_test_group_result(void);
static void print_test_result(const TEST_RESULT* result);

static TEST_GROUP_INFO* currentGroup = NULL;

void set_current_test_group(TEST_GROUP_INFO* testGroup)
{
    currentGroup = testGroup;
}

static void print_current_test_group_result()
{
	int i = 0;
    char spmsg[UNIT_TEST_MAX_STR_LEN * 3];
    int numTests = 0;
    TEST* tests = NULL;
    int numTestsOk = 0;

    RETURN_ON_NULL(currentGroup, );

    numTests = currentGroup->numTests;
    tests = currentGroup->tests;

    for(i = 0; i< numTests; i++)
	{
		if(currentGroup->tests[i].result.type == OK)
		{
			numTestsOk++;
		}
	}

    test_log("\n\n-----------------------GROUP RESULTS----------------------------\n\n");
	if(numTestsOk == currentGroup->numTests)
	{
		test_log("\n\n ALL TEST PASSED!\n\n");
	}
	else
	{
        for(i = 0; i < numTests; i++)
        {
    	    if(tests[i].result.type != OK)
    	    {
    		    char* resultStr = GET_RESULT_STRING(tests[i].result.type);
                sprintf(spmsg, "TEST: %s() %s: %s\n", tests[i].testName, resultStr, tests[i].result.msg);
    	        test_log(spmsg);
    	    }
        }
	}
    test_log("\n----------------------------------------------------------------\n\n");
    sprintf(spmsg, "\n\n %d of %d tests passed. \n\n", numTestsOk, numTests);
	test_log(spmsg);
}

static void test_log(const char* s)
{
    printf("%s", s);
}


static void print_test_result(const TEST_RESULT* result)
{
	char msg[UNIT_TEST_MAX_STR_LEN];
	char* resultStr = NULL;

	RETURN_ON_NULL(result, );

	resultStr = GET_RESULT_STRING(result->type);

	sprintf(msg, "%s", resultStr);
	test_log(msg);

	return;
}

void run_test(TEST_GROUP_INFO* group, void (*testFunc)(TEST* testInfo), const char* testName)
{
	 char msg[UNIT_TEST_MAX_STR_LEN];
     RETURN_ON_NULL(group, );

     if(group->numTests >= MAX_TESTS_PER_GROUP)
     {
     	sprintf(msg, "\n\n FRAMEWORK ERROR: Too many tests specified for this group (test file %s, line %d)\n", __FILE__, __LINE__);
    	test_log(msg);
    	return;
     }

     if(testFunc == NULL)
     {
    	sprintf(msg, "\n\n FRAMEWORK ERROR: Undefined test function (test file %s, line %d)\n", __FILE__, __LINE__);
     	test_log(msg);
     	return;
     }

     sprintf(msg, "\n Running Test %s() ......... ", testName);
     test_log(msg);
     group->setup();
     testFunc(&group->tests[group->numTests]);
     group->tearDown();
     print_test_result(&group->tests[group->numTests].result);
     strncpy(group->tests[group->numTests].testName, testName, MAX_TESTNAME_SIZE-2);
     group->numTests++;
}

void run_group_tests(char* groupName, void (*testRunnerFunc)(void))
{
    char spmsg[UNIT_TEST_MAX_STR_LEN];

	sprintf(spmsg, "\nRunning tests for Test Group %s\n", groupName);
	test_log(spmsg);
	testRunnerFunc();
	print_current_test_group_result();

}

