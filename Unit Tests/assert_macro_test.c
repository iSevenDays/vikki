//
//  assert_macro_test.c
//  Unit Tests
//
//  Created by Anton Sokolchenko on 10/8/19.
//

#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "assert_macro.h"

/* This test will fail since the string returned by get_status_code_string(0)
 * doesn't match "Connection timed out". */
static void get_status_code_string_test(void **state) {
    (void) state; /* unused */

    assert_string_equal(get_status_code_string(0), "Address not found");
    assert_string_equal(get_status_code_string(2), "Connection timed out");
}

/* This test will fail since the status code of "Connection timed out" isn't 1 */
static void string_to_status_code_test(void **state) {
    (void) state; /* unused */

    assert_int_equal(string_to_status_code("Address not found"), 0);
    assert_int_equal(string_to_status_code("Connection timed out"), 2);
}

//int main(void) {
//    const struct CMUnitTest tests[] = {
//        cmocka_unit_test(get_status_code_string_test),
//        cmocka_unit_test(string_to_status_code_test),
//    };
//    return cmocka_run_group_tests(tests, NULL, NULL);
//}
