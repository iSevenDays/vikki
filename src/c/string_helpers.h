//
//  string_helpers.h
//  vikki
//
//  Created by Anton Sokolchenko on 10/9/19.
//

#ifndef string_helpers_h
#define string_helpers_h


char* mystrcat(char *dest, char *src);

/// char *str = "one";
/// cats(&str, ",");
/// cats(&str, "two");
/// cats(&str, ",three");
/// TO free the memory use cats(&str, NULL); // This frees the variable's memory
/// @param str string to append to
/// @param str2 string that will be appended
void cats(char **str, const char *str2);

#endif /* string_helpers_h */
