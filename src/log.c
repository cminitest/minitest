#include "minitest.h"

static void log_format(int log_level, const char* tag, const char* message, va_list args) {
  if (log_level >= minitest.log_level) {
    printf("[%s]: ", tag);
    vprintf(message, args);
    printf("\n");
  }
}

void mt_log_dev(const char* message, ...) {
  va_list args;
  va_start(args, message);
  log_format(MT_LOG_DEVELOPMENT, "DEV", message, args);
  va_end(args);
}

void mt_log_fatal(const char* message, ...) {
  va_list args;
  va_start(args, message);
  log_format(MT_LOG_FATAL, "FATAL", message, args);
  va_end(args);
}

void mt_log_error(const char* message, ...) {
  va_list args;
  va_start(args, message);
  log_format(MT_LOG_ERROR, "ERROR", message, args);
  va_end(args);
}

void mt_log_warn(const char* message, ...) {
  va_list args;
  va_start(args, message);
  log_format(MT_LOG_WARN, "WARNING", message, args);
  va_end(args);
}

void mt_log_info(const char* message, ...) {
  va_list args;
  va_start(args, message);
  log_format(MT_LOG_INFO, "INFO", message, args);
  va_end(args);
}

void mt_log_debug(const char* message, ...) {
  va_list args;
  va_start(args, message);
  log_format(MT_LOG_DEBUG, "DEBUG", message, args);
  va_end(args);
}