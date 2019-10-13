//
//  allocate_module.c
//  Unit Tests
//
//  Created by Anton Sokolchenko on 10/8/19.
//

#include <stdio.h>
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#ifdef HAVE_MALLOC_H
#include <malloc.h>
#endif
#include <sys/types.h>
#include <stdlib.h>

#ifdef UNIT_TESTING
extern void* _test_malloc(const size_t size, const char* file, const int line);
extern void* _test_calloc(const size_t number_of_elements, const size_t size,
                          const char* file, const int line);
extern void _test_free(void* const ptr, const char* file, const int line);

#define malloc(size) _test_malloc(size, __FILE__, __LINE__)
#define calloc(num, size) _test_calloc(num, size, __FILE__, __LINE__)
#define free(ptr) _test_free(ptr, __FILE__, __LINE__)
#endif // UNIT_TESTING

void leak_memory(void);
void buffer_overflow(void);
void buffer_underflow(void);

void leak_memory(void) {
    int * const temporary = (int*)malloc(sizeof(int));
    *temporary = 0;
}

void buffer_overflow(void) {
    char * const memory = (char*)malloc(sizeof(int));
    memory[sizeof(int)] = '!';
    free(memory);
}

void buffer_underflow(void) {
    char * const memory = (char*)malloc(sizeof(int));
    memory[-1] = '!';
    free(memory);
}
