// Logging of info, warnings, and errors with dynamic control over the output.
#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>

enum LogLevel { kLogOutputInfo, kLogOutputWarning, kLogOutputError };

// Dynamically controls the level of log output. The default value is
// kLogOutputWarning (only warnings and errors are output).
extern enum LogLevel output_at_or_above_level;

// Dynamically controls the destination of log output. The default value is
// stderr.
extern FILE* log_output_file;

// Logging functions invoked similar to printf. Each prefixes the output with
// level and source provenance and appends a newline.

#define LOG_INFO(fmt, ...)                                            \
  do {                                                                \
    if (output_at_or_above_level <= kLogOutputInfo)                   \
      fprintf(log_output_file ? log_output_file : stderr,             \
              "I %s:%d:%s() " fmt "\n", __FILE__, __LINE__, __func__, \
              ##__VA_ARGS__);                                         \
  } while (0)

#define LOG_WARNING(fmt, ...)                                         \
  do {                                                                \
    if (output_at_or_above_level <= kLogOutputWarning)                \
      fprintf(log_output_file ? log_output_file : stderr,             \
              "W %s:%d:%s() " fmt "\n", __FILE__, __LINE__, __func__, \
              ##__VA_ARGS__);                                         \
  } while (0)

#define LOG_ERROR(fmt, ...)                                         \
  do {                                                              \
    fprintf(log_output_file ? log_output_file : stderr,             \
            "E %s:%d:%s() " fmt "\n", __FILE__, __LINE__, __func__, \
            ##__VA_ARGS__);                                         \
  } while (0)

#endif  // LOG_H_
