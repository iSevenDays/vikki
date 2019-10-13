//
//  date_parser.c
//  Unit Tests
//
//  Created by Anton Sokolchenko on 10/8/19.
//

#include "date_parser.h"
#include "tiny_sscanf.h"

struct tm *date_time_now(void) {
	time_t now = time(NULL);
	struct tm *current_time = localtime(&now);
	struct tm *copy = malloc(sizeof *copy);
	memcpy(copy, current_time, sizeof(struct tm));
	return copy;
}

time_t end_of_month(time_t t) {

	struct tm *tm = date_time_now();
	tm->tm_sec = -1;
	tm->tm_min = 0;
	tm->tm_hour = 0;
	tm->tm_mday = 1;
	++tm->tm_mon;
	tm->tm_isdst = -1;
	time_t result = mktime(tm);
	free(tm);
	return result;
}

struct tm *addinterval(struct tm *t, int year, int mon, int day) {
	t->tm_year += year;
	t->tm_mon += mon;
	t->tm_mday += day;
	mktime(t);
	return t;
}

bool string_in_array(const char *str, const char *array[], int length) {
	for (int i = 0; i < length; i++) {
		if (strcmp(str, array[i]) == 0) {
			return true;
		}
	}
	return false;
}

struct event_info parse_event_from_string(char *str, struct day_hours_info *day_hours_info) {
	struct event_info event_info = create_empty_event_info();
	struct tm *result_time = date_time_now();
	int hh, mm;

	const char *skippedWords[] = {"в", "во", "часа", "часов", "минут"};
	char *token = strtok(str, " ");
	while (token != NULL) {
		bool is_current_token_parsed = false;
		if (strstr(token, "завтра") != NULL) {
			result_time = addinterval(result_time, 0, 0, 1);
			is_current_token_parsed = true;
			if(is_current_token_parsed) {
				printf(" ");
			}
		} if (day_hours_info != NULL) {
			if (strstr(token, "утром") != NULL) {
				result_time->tm_min = 0;
				result_time->tm_sec = 0;
				result_time->tm_hour = day_hours_info->morning;
				is_current_token_parsed = true;
			} else if (strstr(token, "днем") != NULL || strstr(token, "днём") != NULL) {
				result_time->tm_min = 0;
				result_time->tm_sec = 0;
				result_time->tm_hour = day_hours_info->lunchtime;
				is_current_token_parsed = true;
			} else if (strstr(token, "вечером")) {
				result_time->tm_min = 0;
				result_time->tm_sec = 0;
				result_time->tm_hour = day_hours_info->evening;
				is_current_token_parsed = true;
			}
		} else if (tiny_sscanf(token, "%d:%d", &hh, &mm) == 2) {
			result_time->tm_hour = hh;
			result_time->tm_min = mm;
			is_current_token_parsed = true;
		}
		if (!is_current_token_parsed) {
			bool isTokenStopWord = string_in_array(token, skippedWords, sizeof(skippedWords)/sizeof(skippedWords[0]));
			if (!isTokenStopWord) {
				if (strlen(event_info.description) > 0) {
					// we already have text here, inserting space separator
					cats(&event_info.description, " ");
				}
				cats(&event_info.description, token);
			}
		}
		token = strtok(NULL, " ");
	}
	event_info.time = result_time;
	return event_info;
}

