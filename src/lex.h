#ifndef LEX_H_
#define LEX_H_

#include <stdbool.h>

// Case insensitive keyword match.
bool match_keyword(char* keyword, char* line, int* mutable_index);

// whitespace and comment ";" (nothing important left on the line).
bool match_eol(const char* line, int*mutable_index);

// Label such as "loop1:" indicating an an address (doesn't return colon).
bool match_label(const char* line, int* mutable_index, char** label_text);

bool match_digit(const char* line, int* mutable_index, int* digit_value);

bool match_whitespace(const char* line, int* mutable_index);

bool match_letter(const char* line, int* mutable_index, char* letter);

bool match_nonwhitespace(const char* line, int*mutable_index, char* value);



#endif  // LEX_H_