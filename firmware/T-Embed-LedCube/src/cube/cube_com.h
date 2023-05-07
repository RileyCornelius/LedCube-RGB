#pragma once

#include <Arduino.h>

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
    MessageOtaProgress,
    // not used
    MessageRotationTime,
    MessageFps,
};

void writeDisplayCommand(DisplayType command);
void writeDisplayMessage(DisplayType type, String message);
void writeDisplayMessage(DisplayType type, char *message);
void readCube();