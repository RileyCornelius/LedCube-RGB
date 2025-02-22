#pragma once

#include <Arduino.h>
#include "Config/Config.h"

enum DisplayType
{
    CommandPlay,
    CommandPause,
    CommandStop,
    CommandNext,
    CommandPrevious,
    CommandOtaStart,
    CommandOtaEnd,
    MessageOtaProgress,
    MessageAnimation,
    // not used yet
    CommandRotation,
    MessageRotationTime,
    MessageFps,
};

void handleDisplay();

void writeDisplayCommand(DisplayType command);
void writeDisplayMessage(DisplayType type, String message);
void writeDisplayMessage(DisplayType type, char *message);

#if DISPLAY_ENABLE
#define DISPLAY_BEGIN(x) SerialDisplay.begin(x)
#define DISPLAY_PRINTLN(x) SerialDisplay.println(x)
#define WRITE_DISPLAY_COMMAND(type) writeDisplayCommand(type)
#define WRITE_DISPLAY_MESSAGE(type, message) writeDisplayMessage(type, message)
#else
#define DISPLAY_BEGIN(x)
#define DISPLAY_PRINTLN(x)
#define WRITE_DISPLAY_COMMAND(type)
#define WRITE_DISPLAY_MESSAGE(type, message)
#endif
