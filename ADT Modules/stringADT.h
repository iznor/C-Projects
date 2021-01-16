#ifndef _STR_ADT
#define _STR_ADT

#include <stdio.h>
#include <stdbool.h>

typedef struct _string *String;

typedef enum
{
    LOWER_CASE,
    UPPER_CASE
} CASE;

#define STRING_FOREACH(word, string)            \
    for (String word = string_GetFirst(string); \
         !string_IsDone(string);                \
         word = string_GetNext(string))

String string_create(char *c);                           // creates data type "string"
String multString_create(String s, int mult_by);         // multiplies a string
void string_destroy(String s);                           // free a string from it's allocation in memory
int string_length(String s);                             // returns the length of a string
char *string_chars(String s);                            // returns the string
String string_dup(String s);                             // duplicates a string
char string_charByIndex(String s, int index);            // returns the char from a given index
int string_findIndexByChar(String s, char c);            // returns the index from a given char
bool string_isEqual(String s1, String s2);               // returns 1 if two strings are equal, 0 if not
String string_addString(String dest, String src);        // append a string to another
String string_copy(String dest, String src);             // copies one string to another
String string_convertCase(String s, CASE ul);            // turns a whole string to upper or lower letters
bool string_isAllDigits(String s);                       // returns 1 if string is made out of numbers only
int string_findString(String dest, String sub_str);      // returns the index of a sub-string's first appearance
String string_removeString(String dest, String sub_str); // removes a sub-string from a string
void string_print(String s);                             // prints out a string

String string_GetNext(String s);
String string_GetFirst(String s);
bool string_IsDone(String s);

#endif