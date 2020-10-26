#ifndef LOG_H_
#define LOG_H_

#include <stdbool.h>

enum LogOutput {
  kLogOutputInfo,
  kLogOutputWarning,
  kLogOutputError,
  kLogOutputFatal
};

struct Log {
  enum LogOutput output_at_and_above;
  void (*info)(const char*, ...);
};

extern struct Log LOG;

#endif  // LOG_H_