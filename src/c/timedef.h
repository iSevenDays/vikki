//
//  timedef.h
//  vikki
//
//  Created by Anton Sokolchenko on 10/10/19.
//

#ifndef timedef_h
#define timedef_h

#if defined(UNIT_TESTS) && !defined(TARGET_OS_SIMULATOR)
#include <time.h>
#else
#include <pebble.h>
#endif

#endif /* timedef_h */
