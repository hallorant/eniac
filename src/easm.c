#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"

#define kLineSize 1024
#define kMnemonicSize 5

char *source_filename;
FILE *source_file;
int line_number;
char line[kLineSize];

typedef struct order {
  char mnemonic[kMnemonicSize];
  int code;
  int num_immediate_digits_with_code;
  int num_add_times_to_execute;
} Order;

Order ENIAC_converter_code[] = {
    // Mnemonic, Code, #Digits w/Code, Execution Time

    //////////////////////////
    // Storage Instructions //
    //////////////////////////
    {"Rd", 44, 0, 3000 /*A.T.*/},
    {"AB", 50, 0, 6 /*A.T.*/},
    {"CD", 51, 0, 6 /*A.T.*/},
    {"EF", 54, 0, 6 /*A.T.*/},
    {"GH", 55, 0, 6 /*A.T.*/},
    {"JK", 56, 0, 6 /*A.T.*/},
    {"N2D", 72, /*and*/ 2 /*immediate digits*/, 6 /*A.T.*/},
    {"N4D", 73, /*and*/ 4 /*immediate digits*/, 6 /*A.T.*/},
    {"N6D", 74, /*and*/ 6 /*immediate digits*/, 6 /*A.T.*/},
    {"FTN", 47, 0, 13 /*A.T.*/},
    {"FTC", 97, 0, 13 /*A.T.*/},
    {"1L", 1, 0, 6 /*A.T.*/},
    {"2L", 2, 0, 6 /*A.T.*/},
    {"3L", 3, 0, 6 /*A.T.*/},
    {"4L", 4, 0, 6 /*A.T.*/},
    {"5L", 5, 0, 6 /*A.T.*/},
    {"6L", 6, 0, 6 /*A.T.*/},
    {"7L", 7, 0, 6 /*A.T.*/},
    {"8L", 8, 0, 6 /*A.T.*/},
    {"9L", 9, 0, 6 /*A.T.*/},
    {"10L", 10, 0, 6 /*A.T.*/},
    {"11L", 11, 0, 6 /*A.T.*/},
    {"12L", 12, 0, 6 /*A.T.*/},
    {"13L", 13, 0, 6 /*A.T.*/},
    {"14L", 14, 0, 6 /*A.T.*/},
    {"16L", 16, 0, 6 /*A.T.*/},
    {"17L", 17, 0, 6 /*A.T.*/},
    {"18L", 18, 0, 6 /*A.T.*/},
    {"19L", 19, 0, 6 /*A.T.*/},
    {"20L", 20, 0, 6 /*A.T.*/},
    {"CL", 15, 0, 6 /*A.T.*/},
    {"6_1", 92, 0, 10 /*A.T.*/},
    {"6_2", 93, 0, 10 /*A.T.*/},
    {"S.C.", 91, 0, 7 /*A.T.*/},
    {"Pr", 45, 0, 3000 /*A.T.*/},
    ////////////////////////
    // Shift Instructions //
    ////////////////////////
    {"SR1", 32, 0, 9 /*A.T.*/},
    {"SR2", 43, 0, 9 /*A.T.*/},
    {"SR3", 42, 0, 9 /*A.T.*/},
    {"SR4", 53, 0, 9 /*A.T.*/},
    {"SR5", 52, 0, 9 /*A.T.*/},
    {"SL1", 60, 0, 9 /*A.T.*/},
    {"SL2", 71, 0, 9 /*A.T.*/},
    {"SL3", 70, 0, 9 /*A.T.*/},
    {"SL4", 81, 0, 9 /*A.T.*/},
    {"SL5", 80, 0, 9 /*A.T.*/},
    {"S'R1", 38, 0, 9 /*A.T.*/},
    {"S'R2", 49, 0, 9 /*A.T.*/},
    {"S'R3", 48, 0, 9 /*A.T.*/},
    {"S'R4", 59, 0, 9 /*A.T.*/},
    {"S'R5", 58, 0, 9 /*A.T.*/},
    {"S'L1", 66, 0, 9 /*A.T.*/},
    {"S'L2", 77, 0, 9 /*A.T.*/},
    {"S'L3", 76, 0, 9 /*A.T.*/},
    {"S'L4", 87, 0, 9 /*A.T.*/},
    {"S'L5", 86, 0, 9 /*A.T.*/},
    ///////////////////////
    // Arithmetic Orders //
    ///////////////////////
    {"1T", 21, 0, 6 /*A.T.*/},
    {"2T", 22, 0, 6 /*A.T.*/},
    {"3T", 23, 0, 6 /*A.T.*/},
    {"4T", 24, 0, 6 /*A.T.*/},
    {"5T", 25, 0, 6 /*A.T.*/},
    {"6T", 26, 0, 6 /*A.T.*/},
    {"7T", 27, 0, 6 /*A.T.*/},
    {"8T", 28, 0, 6 /*A.T.*/},
    {"9T", 29, 0, 6 /*A.T.*/},
    {"10T", 30, 0, 6 /*A.T.*/},
    {"11T", 31, 0, 6 /*A.T.*/},
    {"12T", 32, 0, 6 /*A.T.*/},
    {"13T", 33, 0, 6 /*A.T.*/},
    {"14T", 34, 0, 6 /*A.T.*/},
    {"16T", 36, 0, 6 /*A.T.*/},
    {"17T", 37, 0, 6 /*A.T.*/},
    {"18T", 38, 0, 6 /*A.T.*/},
    {"19T", 39, 0, 6 /*A.T.*/},
    {"20T", 30, 0, 6 /*A.T.*/},
};

bool match(const char* text, const char* within, int* mutable_index) {
  
}

bool read_next_line() {
  if (fgets(line, kLineSize, source_file) == NULL) {
    LOG_INFO("EOF");
    return false;
  }
  line[strcspn(line, "\r\n")] = 0;
  ++line_number;
  LOG_INFO("%s:%i \"%s\"", source_filename, line_number, line);
  return true;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    exit(-1);
  }

  output_at_or_above_level = kLogOutputInfo;

  source_filename = argv[argc - 1];
  if ((source_file = fopen(source_filename, "r")) == NULL) {
    fprintf(stderr, "fatal: source file '%s' cannot be read\n",
            source_filename);
    exit(-2);
  }

  char buf[kLineSize];
  while (read_next_line()) {
  };
  fclose(source_file);

  exit(0);
}
