#include <Arduino.h>
#include <Logger.h>

#if LOG_PRINT_LONG_NAME
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

static void iprintf(const char *loglevel, const char *tag, const char *format, va_list args)
{
    char message[64];
    vsprintf(message, format, args);
#if LOG_PRINT_TIME

    LOG_TIME_PRINTER("[%s] (%s) %s %s\n", loglevel, LOG_TIME_GETTER, tag, message);
#else
    LOG_TIME_PRINTER("[%s] %s %s\n", loglevel, tag, message);
#endif
}

static void ilogf(uint8_t level, const char *tag, const char *format, va_list args)
{
    if (LOG_LEVEL_MAX >= level && LOG_LEVEL_MIN <= level)
    {
        switch (level)
        {
        case LOG_LEVEL_ERROR:
            iprintf(I_ERROR_NAME, tag, format, args);
            break;
        case LOG_LEVEL_WARN:
            iprintf(I_WARN_NAME, tag, format, args);
            break;
        case LOG_LEVEL_INFO:
            iprintf(I_INFO_NAME, tag, format, args);
            break;
        default:
            iprintf(I_DEBUG_NAME, tag, format, args);
            break;
        }
    }
}

void iformat(uint8_t level, const char *tag, String format, ...)
{
    va_list args;
    va_start(args, format);
    ilogf(level, tag, format.c_str(), args);
    va_end(args);
}

void iformat(uint8_t level, const char *tag, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    ilogf(level, tag, format, args);
    va_end(args);
}
