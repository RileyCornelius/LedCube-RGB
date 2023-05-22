#pragma once

#include <Arduino.h>

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

void writeDisplayCommand(DisplayType command);
void writeDisplayMessage(DisplayType type, String message);
void writeDisplayMessage(DisplayType type, char *message);
void handleCom();