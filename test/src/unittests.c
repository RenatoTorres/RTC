/*
 * unittests.c
 *
 *  Created on: Jun 28, 2023
 *      Author: charles
 */

#include <stdio.h>
#include "unittests.h"
#include "square.h"

struct MagicSquare* sq;

GROUP_SETUP(magic_square_3)
{
	sq = create_magic_square(3);
}

GROUP_TEARDOWN(magic_square_3)
{
	delete_magic_square(&sq);
}

DEFINE_TEST_CASE(magic_square_3, test_fill)
{
	ASSERT_TRUE_TEXT(fill_magic_square(sq) == SUCCESS, "Expected fill_magic_square to return SUCCESS");
}

DEFINE_TEST_CASE(magic_square_3, test_magic_constant)
{
	unsigned int expected = 15;
	unsigned int result = 0;

	ASSERT_TRUE_TEXT(fill_magic_square(sq) == SUCCESS, "Expected fill_magic_square to return SUCCESS");
	ASSERT_TRUE_TEXT(get_magic_constant(sq, &result) == SUCCESS, "Expected get_magic_constant to return SUCCESS");
	ASSERT_TRUE_TEXT(result == expected, "Incorrect magic constant");
}

DEFINE_TEST_CASE(magic_square_3, test_row_and_col_sums)
{
	unsigned int expected = 15;
	unsigned int result = 0;
    unsigned int row_result = 0;
    unsigned int col_result = 0;

	ASSERT_TRUE_TEXT(fill_magic_square(sq) == SUCCESS, "Expected fill_magic_square to return SUCCESS");
	ASSERT_TRUE_TEXT(get_magic_constant(sq, &result) == SUCCESS, "Expected get_magic_constant to return SUCCESS");
	ASSERT_TRUE_TEXT(result == expected, "Incorrect magic constant");
	ASSERT_TRUE_TEXT(sum_row(0, sq, &row_result) == SUCCESS, "Expected sum_row to return SUCCESS");
	ASSERT_TRUE_TEXT(sum_column(2, sq, &col_result) == SUCCESS, "Expected sum_column to return SUCCESS");
	printf("Col %d ROw %d\n", col_result, row_result);
	ASSERT_TRUE_TEXT(((result == row_result) && (result  == col_result)), "Rows and Columns should sum to the magic constant");

}

TEST_GROUP_RUNNER(magic_square_3)
{
	INIT_TEST_GROUP(magic_square_3);

	RUN_TEST_CASE(magic_square_3, test_fill);
	RUN_TEST_CASE(magic_square_3, test_magic_constant);
	RUN_TEST_CASE(magic_square_3, test_row_and_col_sums);
}

