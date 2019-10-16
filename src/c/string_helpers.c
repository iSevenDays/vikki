//
//  string_helpers.c
//  vikki
//
//  Created by Anton Sokolchenko on 10/9/19.
//

#include "string_helpers.h"
#if defined(UNIT_TESTS) && !defined(TARGET_OS_SIMULATOR)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#else
#include <pebble.h>
#endif

char* mystrcat(char *dest, char *src) {
    while (*dest) dest++;
	while ((*dest++ = *src++))
		;
    return --dest;
}

void cats(char **str, const char *str2) {
    char *tmp = NULL;

    // Reset *str
    if ( *str != NULL && str2 == NULL ) {
        free(*str);
        *str = NULL;
        return;
    }

    // Initial copy
    if (*str == NULL) {
        *str = calloc( strlen(str2)+1, sizeof(char) );
        memcpy( *str, str2, strlen(str2) );
    }
    else { // Append
        tmp = calloc( strlen(*str)+1, sizeof(char) );
        memcpy( tmp, *str, strlen(*str) );
        *str = calloc( strlen(*str)+strlen(str2)+1, sizeof(char) );
        memcpy( *str, tmp, strlen(tmp) );
        memcpy( *str + strlen(*str), str2, strlen(str2) );
        free(tmp);
    }
}
