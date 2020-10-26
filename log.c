#include "log.h"

#include <stdarg.h>
#include <stdio.h>

static void info(const char *fmt, ...) {
  if (LOG.output_at_and_above > kLogOutputInfo) return;
  va_list varargs;
  va_start(varargs, fmt);
  fprintf(stderr, "%s:%d:%s(): ", __FILE__, __LINE__, __func__);
  vfprintf(stderr, fmt, varargs);
  fprintf(stderr, "\n");
  va_end(varargs);
}

struct Log LOG = {.output_at_and_above = kLogOutputWarning, .info = info};