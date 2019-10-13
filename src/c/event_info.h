//
//  event_info.h
//  vikki
//
//  Created by Anton Sokolchenko on 10/9/19.
//

#ifndef event_info_h
#define event_info_h

#include "timedef.h"


struct event_info {
	struct tm *time;
	char *description;
};

#endif /* event_info_h */
