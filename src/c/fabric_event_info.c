//
//  fabric_event_info.c
//  vikki
//
//  Created by Anton Sokolchenko on 10/9/19.
//

#ifdef UNIT_TESTS
#include <stdlib.h>
#endif
#include "fabric_event_info.h"

struct event_info create_empty_event_info(void) {
	struct event_info event_info;
	event_info.description = calloc(1, sizeof(char));
	return event_info;
}
