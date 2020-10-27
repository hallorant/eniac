#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"

#define LINE_SIZE 1024

char *source_filename;
FILE *source_file;
int line_number;
char line[LINE_SIZE];

bool read_next_line() {
  if (fgets(line, LINE_SIZE, source_file) == NULL) {
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

  char buf[LINE_SIZE];
  while (read_next_line()) {
  };
  fclose(source_file);

  exit(0);
}
