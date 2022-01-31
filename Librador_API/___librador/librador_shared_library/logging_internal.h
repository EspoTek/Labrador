#ifndef LOGGING_INTERNAL_H
#define LOGGING_INTERNAL_H

#include "logging.h"

#define LIBRADOR_LOG(level, ...) \
    do { \
        librador_global_logger(level, __VA_ARGS__); \
    } while (0)

void librador_global_logger(const int level, const char * format, ...);

#endif // LOGGING_INTERNAL_H
