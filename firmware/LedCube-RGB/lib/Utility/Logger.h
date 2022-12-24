#pragma once

#include <Arduino.h>

/**--------------------------------------------------------------------------------------
 * Logger Defines
 *-------------------------------------------------------------------------------------*/

// Log levels defines
#define LOG_LEVEL_NONE 0
#define LOG_LEVEL_DEBUG 1
#define LOG_LEVEL_INFO 2
#define LOG_LEVEL_WARN 3
#define LOG_LEVEL_ERROR 4

// Log level variable
#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_DEBUG // default log level
#endif

// Min log level variable
#ifndef LOG_LEVEL_MIN
#define LOG_LEVEL_MIN LOG_LEVEL_DEBUG // default min log level
#endif

// Time getter
#ifndef LOG_TIME_GETTER
#define LOG_TIME_GETTER() millis() // default time getter
#endif

// Print time in message
#ifndef LOG_PRINT_TIME
#define LOG_PRINT_TIME 1 // default print time
#endif

// Print log types full name or single letter
#ifndef LOG_NAME_LONG
#define LOG_NAME_LONG 1 // default name type
#endif

// Log format defines
#if LOG_LEVEL > 0
#define LOG_DEBUG(format, ...) iformat(LOG_LEVEL_DEBUG, format, ##__VA_ARGS__)
#define LOG_INFO(format, ...) iformat(LOG_LEVEL_INFO, format, ##__VA_ARGS__)
#define LOG_WARN(format, ...) iformat(LOG_LEVEL_WARN, format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) iformat(LOG_LEVEL_ERROR, format, ##__VA_ARGS__)
#else
#define LOG_DEBUG_F(format, ...)
#define LOG_INFO_F(format, ...)
#define LOG_WARN_F(format, ...)
#define LOG_ERROR_F(format, ...)
#endif

/**--------------------------------------------------------------------------------------
 * Internals
 *-------------------------------------------------------------------------------------*/

// Log name defines
#if LOG_NAME_LONG
#define I_DEBUG_NAME "DEBUG"
#define I_INFO_NAME "INFO"
#define I_WARN_NAME "WARN"
#define I_ERROR_NAME "ERROR"
#else
#define I_DEBUG_NAME "D"
#define I_INFO_NAME "I"
#define I_WARN_NAME "W"
#define I_ERROR_NAME "E"
#endif

static void iprintf(const char *loglevel, const char *format, va_list args)
{
    char buffer[64];
    vsprintf(buffer, format, args);
#if LOG_PRINT_TIME
    Serial.printf("[%s] (%d) %s\n", loglevel, LOG_TIME_GETTER(), buffer);
#else
    Serial.printf("[%s] %s\n", loglevel, buffer);
#endif
}

static void ilogf(uint8_t level, const char *format, va_list args)
{
    if (LOG_LEVEL >= level && LOG_LEVEL_MIN <= level)
    {
        switch (level)
        {
        case LOG_LEVEL_ERROR:
            iprintf(I_ERROR_NAME, format, args);
            break;
        case LOG_LEVEL_WARN:
            iprintf(I_WARN_NAME, format, args);
            break;
        case LOG_LEVEL_INFO:
            iprintf(I_INFO_NAME, format, args);
            break;
        default:
            iprintf(I_DEBUG_NAME, format, args);
            break;
        }
    }
}

static void iformat(uint8_t level, String format, ...)
{
    va_list args;
    va_start(args, format);
    ilogf(level, format.c_str(), args);
    va_end(args);
}

static void iformat(uint8_t level, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    ilogf(level, format, args);
    va_end(args);
}