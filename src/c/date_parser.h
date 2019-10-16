//
//  date_parser.h
//  Unit Tests
//
//  Created by Anton Sokolchenko on 10/8/19.
//

#ifndef date_parser_h
#define date_parser_h

#if defined(UNIT_TESTS) && !defined(TARGET_OS_SIMULATOR)
#include "timedef.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#else
#include <pebble.h>
#endif

#include "string_helpers.h"
#include "fabric_event_info.h"

struct tm *date_time_now(void);

/// Add interval to tm time
/// If you call mktime(&x) after applying the additions, it will normalise the structure (so eg. 40 October becomes 9 November)
/// @param t tim struct
/// @param year year
/// @param mon month
/// @param day day
struct tm *addinterval(struct tm *t, int year, int mon, int day);


struct day_hours_info {
	int	morning;		/* время утром */
	int	lunchtime;		/* обед */
	int	evening;	/* вечер */
	int	tomorrow;	/* стандартное время для завтра, если не задано конкретное время суток */
};


/// Parse input string into
/// @param str input str like "
struct event_info parse_event_from_string(char *str, struct day_hours_info *day_hours_info);

#endif /* date_parser_h */
