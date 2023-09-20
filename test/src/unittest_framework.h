/*
 * unittest_framework.h
 *
 *  Created on: Jun 27, 2023
 *      Author: charles
 */

#ifndef INCLUDE_UNITTEST_FRAMEWORK_H_
#define INCLUDE_UNITTEST_FRAMEWORK_H_

#include <string.h>

#define MAX_TESTS_PER_GROUP 20
#define MAX_GROUPS 10

#define MAX_MSG_SIZE 150
#define MAX_GROUPNAME_SIZE 256
#define MAX_TESTNAME_SIZE 256
#define BASE_RESULT_SIZE 10

#define GROUP_SETUP(groupName) void setup_##groupName(void)
#define GROUP_TEARDOWN(groupName) void tearDown_##groupName(void)
#define DEFINE_TEST_CASE(groupName, testName) void testName(TEST* test)
#define INIT_TEST_GROUP(groupName) TEST_GROUP_INFO group_info_##groupName = {setup_##groupName, tearDown_##groupName, #groupName, 0}; \
	                               set_current_test_group(&group_info_##groupName);
#define TEST_OUTPUT_METHOD(s) test_log(s);

#define ASSERT_TRUE_TEXT(cond, text)  if(!(cond)){test->result.type = FAIL; strncpy(test->result.msg, text, MAX_MSG_SIZE); return;}
#define ASSERT_TRUE(cond) ASSERT_TRUE_TEXT(cond, "")

#define ASSERT_FALSE_TEXT(cond, text)  if((cond)){test->result.type = FAIL; strncpy(test->result.msg, text, MAX_MSG_SIZE); return;}
#define ASSERT_FALSE(cond) ASSERT_TRUE_TEXT(cond, "")

#define TEST_GROUP_RUNNER(groupName) void test_group_runner_##groupName(void)

#define RUN_TEST_GROUP(groupName) run_group_tests(#groupName, test_group_runner_##groupName)
#define RUN_TEST_CASE(groupName, testName)   run_test(&group_info_##groupName, testName, #testName);

typedef enum{
    OK = 0,
	FAIL,
	UNDEFINED,
	NUM_RESULT_TYPES
}RESULT_TYPE;



typedef struct result{
	RESULT_TYPE type;
	char msg[MAX_MSG_SIZE];
}TEST_RESULT;

typedef struct test{
	char testName[MAX_TESTNAME_SIZE];
	void (*testFunc)(void);
	TEST_RESULT result;
}TEST;
typedef struct group_test{
	void (*setup)(void);
	void (*tearDown)(void);
	char* groupName;
	int numTests;
	TEST tests[MAX_TESTS_PER_GROUP];
}TEST_GROUP_INFO;

void run_test(TEST_GROUP_INFO* group, void (*testFunc)(TEST* testInfo), const char* testName);
void set_current_test_group(TEST_GROUP_INFO* testGroup);
void run_group_tests(char* groupName, void (*testRunnerFunc)(void));
#endif /* INCLUDE_UNITTEST_FRAMEWORK_H_ */
