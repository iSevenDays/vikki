//
//  string_helpers_test.h
//  vikki
//
//  Created by Anton Sokolchenko on 10/9/19.
//

#ifndef string_helpers_test_h
#define string_helpers_test_h

#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

void test_string_cats(void **state);
void test_string_concats_cats_free(void **state);


const struct CMUnitTest tests_string_helpers[] = {
	cmocka_unit_test(test_string_cats),
	cmocka_unit_test(test_string_concats_cats_free),
};
#endif /* string_helpers_test_h */
