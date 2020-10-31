#include "lex.h"

#include <ctype.h>
#include <string.h>

#include "log.h"

static bool try_to_match_letter_or_underscore(char* line, int* mutable_index,
                                              char* matched_letter,
                                              bool also_allow_digit) {
  line += *mutable_index;
  if (!(isalpha(*line) || *line == '_' || (also_allow_digit && isdigit(*line))))
    return false;
  *matched_letter = *line;
  (*mutable_index)++;
  return true;
}

// Comments start with ';' '*' or '#' and extend to the end of the line.
static bool try_to_match_comment(char* line, int* mutable_index) {
  if (try_to_match_keyword(line, mutable_index, ";") ||
      try_to_match_keyword(line, mutable_index, "*") ||
      try_to_match_keyword(line, mutable_index, "#")) {
    *mutable_index = strlen(line);
    return true;
  }
  return false;
}

bool try_to_match_whitespace(char* line, int* mutable_index) {
  line += *mutable_index;
  if (!isspace(*line)) return false;
  do {
    line++;
    (*mutable_index)++;
  } while (isspace(*line));
  return true;
}
bool try_to_match_digit(char* line, int* mutable_index, int* matched_digit) {
  line += *mutable_index;
  if (!isdigit(*line)) return false;
  *matched_digit = *line - '0';
  (*mutable_index)++;
  return true;
}

bool try_to_match_keyword(char* line, int* mutable_index, char* keyword) {
  line += *mutable_index;
  int chars_consumed = 0;
  while (*keyword) {
    if (toupper(*keyword++) != toupper(*line++)) return false;
    ++chars_consumed;
  }
  *mutable_index += chars_consumed;
  return true;
}

bool try_to_match_label(char* line, int* mutable_index, char* mutable_label,
                        const int label_size) {
  const int original_index = *mutable_index;
  if (label_size < 2) {
    LOG_ERROR("label_size must be >= 2 : label_size=%d", label_size);
    return false;
  }
  char value;
  int size = 0;
  if (!try_to_match_letter_or_underscore(line, mutable_index, &value,
                                         /*also_allow_digit=*/false)) {
    return false;
  }
  *mutable_label++ = value;
  ++size;

  while (try_to_match_letter_or_underscore(line, mutable_index, &value,
                                           /*also_allow_digit=*/true)) {
    if (size == label_size - 2) {
      LOG_ERROR("label_size of %d cannot fit label '%s<truncated>'", label_size,
                mutable_label);
      *mutable_index = original_index;  // Restore index due to failure.
      return false;
    }
    *mutable_label++ = value;
    *mutable_label = 0;  // Proactively null terminate the label string.
    ++size;
  }
  return true;
}

bool try_to_match_label_decl(char* line, int* mutable_index,
                             char* mutable_label, const int label_size) {
  const int original_index = *mutable_index;
  if (try_to_match_label(line, mutable_index, mutable_label, label_size) &&
      try_to_match_keyword(line, mutable_index, ":")) {
    return true;
  }
  // We might have matched just the label, no ';', so restore the index.
  *mutable_index = original_index;
  return false;
}

bool try_to_match_eol(char* line, int* mutable_index) {
  const int original_index = *mutable_index;
  const int line_size = strlen(line);
  if (*mutable_index == line_size) return true;
  try_to_match_whitespace(line, mutable_index);
  if (*mutable_index == line_size) return true;
  if (try_to_match_comment(line, mutable_index)) return true;
  // We might have matched just whitespace, so restore the index.
  *mutable_index = original_index;
  return false;
}
