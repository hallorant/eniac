// Simple lexical analysis for a line-oriented assembler.
#ifndef LEX_H_
#define LEX_H_

#include <stdbool.h>

// "Try to match" lexical routines for needed assembly tokens. Each passes the
// line and the (mutable) index a the current point of consumption. Each returns
// true is a match was possible and false if not. In all cases if false is
// returned then the mutable_index is unchanged (nothing was consumed).

// Consumes all whitespace, fails if none is found.
bool try_to_match_whitespace(char* line, int* mutable_index);

// Consumes a single digit [0,9] and returns the value in matched_digit.
bool try_to_match_digit(char* line, int* mutable_index, int* matched_digit);

// Consumes the passed keyword, e.g., 'Rd' (case insensitive), if found.
bool try_to_match_keyword(char* line, int* mutable_index, char* keyword);

// Consumes a label, e.g. "start_123_addr", if found, and returns the text in
// mutable_label. The label must start with a letter or underscore but the
// remainder may contain letters, digits and underscores. label_size limits the
// characters returned in mutable_label and can cause the match to fail if the
// label in the program text is too long.
bool try_to_match_label(char* line, int* mutable_index, char* mutable_label,
                        const int label_size);

// Consumes a label declaration, e.g., "start:", if found, and returns the text
// in mutable_label. The label must start with a letter or underscore but the
// remainder may contain letters, digits and underscores. label_size limits the
// characters returned in mutable_label and can cause the match to fail if the
// label in the program text is too long. On a failed match the contents of
// mutable_label are undefined.
bool try_to_match_label_decl(char* line, int* mutable_index,
                             char* mutable_label, const int label_size);

// Consumes to the end of the current line. Fails if any interesting text
// remains, thus the line should only contain nothing, whitespace, or a comment.
// For example, " ; reads the next punched card." or "" or "   " would be fine.
// On a failed match the contents of mutable_label are undefined.
bool try_to_match_eol(char* line, int* mutable_index);

#endif  // LEX_H_