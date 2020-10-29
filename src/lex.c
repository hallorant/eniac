#include "lex.h"

#include <ctype.h>
#include <stdio.h>


bool match_keyword(char* keyword, char* line, int* mutable_index) {
  line += *mutable_index;
  int chars_consumed = 0;
  while (*keyword) {
    if (toupper(*keyword++) != toupper(*line++)) return false;
    ++chars_consumed;
  }
  *mutable_index += chars_consumed;
  return true;
}