#pragma once

#include <Arduino.h>
#include "config.h"

enum DisplayType : uint8_t
{
    CommandPlay,
    CommandPause,
    CommandStop,
    CommandNext,
    CommandPrevious,
    CommandRotation,
    CommandOtaStart,
    CommandOtaEnd,
    // has params
    MessageAnimation,
    MessageRotationTime,
    MessageFps,
    MessageOtaProgress,
};

void readDisplay();

void writeDisplayCommand(DisplayType command);
void writeDisplayMessage(DisplayType type, String message);
void writeDisplayMessage(DisplayType type, char *message);

#if DISPLAY_ENABLE
#define WRITE_DISPLAY_COMMAND(type) writeDisplayCommand(type)
#define WRITE_DISPLAY_MESSAGE(type, message) writeDisplayMessage(type, message)
#else
#define WRITE_DISPLAY_COMMAND(type)
#define WRITE_DISPLAY_MESSAGE(type, message)
#endif
