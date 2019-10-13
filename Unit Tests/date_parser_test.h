//
//  date_parser_test.h
//  vikki
//
//  Created by Anton Sokolchenko on 10/9/19.
//

#ifndef date_parser_test_h
#define date_parser_test_h

#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

void parse_use_case_21_30(void **state);
void parse_use_case_05_30(void **state);
void parse_use_case_tomorrow_05_30(void **state);
void parse_use_case_morning(void **state);
void parse_use_case_lunchtime(void **state);
void parse_use_case_evening(void **state);
void parse_use_case_description_05_30_wash_a_cat(void **state);

const struct CMUnitTest tests_date_parser[] = {
	cmocka_unit_test(parse_use_case_21_30),
	cmocka_unit_test(parse_use_case_05_30),
	cmocka_unit_test(parse_use_case_tomorrow_05_30),
	cmocka_unit_test(parse_use_case_morning),
	cmocka_unit_test(parse_use_case_lunchtime),
	cmocka_unit_test(parse_use_case_evening),
	cmocka_unit_test(parse_use_case_description_05_30_wash_a_cat),
};
#endif /* date_parser_test_h */
