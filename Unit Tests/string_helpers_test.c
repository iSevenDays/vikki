//
//  string_helpers_test.c
//  vikki
//
//  Created by Anton Sokolchenko on 10/9/19.
//

#include <stdio.h>

#include "string_helpers.h"
#include <setjmp.h>
#include <cmocka.h>

void test_string_cats(void **state) {
    (void) state; /* unused */

	char *str1 = "привет";
	char *str2 = " мир";

	char *result = "";
	cats(&result, str1);
	cats(&result, str2);

	assert_non_null(result);
	assert_string_equal(result, "привет мир");
}

void test_string_concats_cats_free(void **state) {
    (void) state; /* unused */

	char *str1 = "привет";
	char *str2 = " мир";

	char *result = "";
	cats(&result, str1);
	cats(&result, str2);
	cats(&result, NULL);

	assert_null(result);
}
