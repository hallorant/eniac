#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"

#define LINE_SIZE 1024

FILE *source_file;
int line_number;
char line[LINE_SIZE];

bool read_next_line() {
  if (fgets(line, LINE_SIZE, source_file) == NULL) {
    LOG.info("EOF");
    return false;
  }
  line[strcspn(line, "\r\n")] = 0;
  ++line_number;
  LOG.info("%4i \"%s\"", line_number, line);
  return true;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    exit(-1);
  }

  LOG.output_at_and_above = kLogOutputInfo;

  char *in_filename = argv[argc - 1];
  if ((source_file = fopen(in_filename, "r")) == NULL) {
    fprintf(stderr, "fatal: source file '%s' cannot be read\n", in_filename);
    exit(-2);
  }

  char buf[LINE_SIZE];
  while (read_next_line()) {
  };
  fclose(source_file);

  exit(0);
}
