//
//  vikki.h
//  vikki
//
//  Created by Anton Sokolchenko on 10/10/19.
//

#ifndef vikki_h
#define vikki_h

#if defined(UNIT_TESTS) && !defined(TARGET_OS_SIMULATOR)
#include "timedef.h"
#include "event_info.h"
#else
#include <pebble.h>
#endif

#endif /* vikki_h */
