#pragma once

#include <Arduino.h>

/**--------------------------------------------------------------------------------------
 * Internal
 *-------------------------------------------------------------------------------------*/

#define I_LOG_LEVEL_NONE 0
#define I_LOG_LEVEL_DEBUG 1
#define I_LOG_LEVEL_INFO 2
#define I_LOG_LEVEL_WARN 3
#define I_LOG_LEVEL_ERROR 4

// Internal print new line
#define I_PRINTLN(level, message) Serial.println(String(level) + message)

// Internal log
#define I_LOG(level, message)               \
    if (level <= LOG_LEVEL)                 \
    {                                       \
        switch (level)                      \
        {                                   \
        case I_LOG_LEVEL_DEBUG:             \
            I_PRINTLN("[DEBUG] ", message); \
            break;                          \
        case I_LOG_LEVEL_INFO:              \
            I_PRINTLN("[INFO] ", message);  \
            break;                          \
        case I_LOG_LEVEL_WARN:              \
            I_PRINTLN("[WARN] ", message);  \
            break;                          \
        case I_LOG_LEVEL_ERROR:             \
            I_PRINTLN("[ERROR] ", message); \
            break;                          \
        }                                   \
    }

/**--------------------------------------------------------------------------------------
 * Public API
 *-------------------------------------------------------------------------------------*/

#ifndef LOG_LEVEL
// I_LOG_LEVEL_NONE   0
// I_LOG_LEVEL_DEBUG  1
// I_LOG_LEVEL_INFO   2
// I_LOG_LEVEL_WARN   3
// I_LOG_LEVEL_ERROR  4
#define LOG_LEVEL I_LOG_LEVEL_DEBUG // default log level
#endif

#if LOG_LEVEL > 0
#define LOG_DEBUG(message) I_LOG(I_LOG_LEVEL_DEBUG, message)
#define LOG_INFO(message) I_LOG(I_LOG_LEVEL_INFO, message)
#define LOG_WARN(message) I_LOG(I_LOG_LEVEL_WARN, message)
#define LOG_ERROR(message) I_LOG(I_LOG_LEVEL_ERROR, message)
#else
#define LOG_DEBUG(message)
#define LOG_INFO(message)
#define LOG_WARN(message)
#define LOG_ERROR(message)
#endif // LOG_LEVEL > 0

// #define LOG_FORMAT_DEBUG(...)
// #define LOG_FORMAT_INFO(...)
// #define LOG_FORMAT_WARN(...)
// #define LOG_FORMAT_ERROR(...)
