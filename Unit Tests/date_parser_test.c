//
//  date_parser_test.c
//  Unit Tests
//
//  Created by Anton Sokolchenko on 10/8/19.
//

#include "time.h"
#include "date_parser.h"
#include <setjmp.h>
#include <cmocka.h>
#include "event_info.h"

void parse_use_case_21_30(void **state) {
    (void) state; /* unused */

	struct tm *current_time = date_time_now();

	struct tm result = *parse_event_from_string("21:30", NULL).time;
	assert_int_equal(result.tm_mday, current_time->tm_mday);
	assert_int_equal(result.tm_hour, 21);
	assert_int_equal(result.tm_min, 30);
}

void parse_use_case_05_30(void **state) {
    (void) state; /* unused */

	struct tm *current_time = date_time_now();

	char str[] = "5:30";
	struct tm result = *parse_event_from_string(str, NULL).time;
	assert_int_equal(result.tm_mday, current_time->tm_mday);
	assert_int_equal(result.tm_hour, 5);
	assert_int_equal(result.tm_min, 30);
}

void parse_use_case_tomorrow_05_30(void **state) {
    (void) state; /* unused */

	struct tm *current_time = date_time_now();

	char str[] = "завтра в 5:30";
	struct tm result = *parse_event_from_string(str, NULL).time;
	assert_int_equal(result.tm_hour, 5);
	assert_int_equal(result.tm_min, 30);

	int tomorrowExpected = addinterval(current_time, 0, 0, 1)->tm_mday;
	int tomorrowActual = result.tm_mday;
	
	assert_int_equal(tomorrowExpected, tomorrowActual);
}

void parse_use_case_morning(void **state) {
    (void) state; /* unused */

	struct tm *current_time = date_time_now();

	char str[] = "утром";
	struct day_hours_info dhi;
	dhi.morning = 9;

	struct tm result = *parse_event_from_string(str, &dhi).time;
	assert_int_equal(result.tm_mday, current_time->tm_mday);
	assert_int_equal(result.tm_hour, 9);
	assert_int_equal(result.tm_min, 0);
	assert_int_equal(result.tm_sec, 0);
}

void parse_use_case_lunchtime(void **state) {
    (void) state; /* unused */

	struct tm *current_time = date_time_now();

	char str[] = "днём";
	struct day_hours_info dhi;
	dhi.lunchtime = 12;

	struct tm result = *parse_event_from_string(str, &dhi).time;
	assert_int_equal(result.tm_mday, current_time->tm_mday);
	assert_int_equal(result.tm_hour, 12);
	assert_int_equal(result.tm_min, 0);
	assert_int_equal(result.tm_sec, 0);
}

void parse_use_case_evening(void **state) {
    (void) state; /* unused */

	struct tm *current_time = date_time_now();

	char str[] = "вечером";
	struct day_hours_info dhi;
	dhi.evening = 18;

	struct tm result = *parse_event_from_string(str, &dhi).time;
	assert_int_equal(result.tm_mday, current_time->tm_mday);
	assert_int_equal(result.tm_hour, 18);
	assert_int_equal(result.tm_min, 0);
	assert_int_equal(result.tm_sec, 0);
}

void parse_use_case_description_05_30_wash_a_cat(void **state) {
    (void) state; /* unused */

	struct tm *current_time = date_time_now();

	char str[] = "завтра в 5:30 помыть кота";
	struct event_info event_info = parse_event_from_string(str, NULL);
	assert_int_equal(event_info.time->tm_hour, 5);
	assert_int_equal(event_info.time->tm_min, 30);
	assert_string_equal(event_info.description, "помыть кота");

	int tomorrowExpected = addinterval(current_time, 0, 0, 1)->tm_mday;
	int tomorrowActual = event_info.time->tm_mday;

	assert_int_equal(tomorrowExpected, tomorrowActual);
}
