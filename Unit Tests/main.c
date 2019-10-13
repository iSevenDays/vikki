//
//  main.c
//  vikki
//
//  Created by Anton Sokolchenko on 10/9/19.
//

#include "main.h"

int main(void) {

	return cmocka_run_group_tests(tests_string_helpers, NULL, NULL) +
	cmocka_run_group_tests(tests_date_parser, NULL, NULL);
}
