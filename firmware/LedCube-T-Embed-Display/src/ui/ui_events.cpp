//* This file was NOT generated

#include <Arduino.h>
#include <Logger.h>
#include "com/cube_com.h"
#include "ui.h"

static const char *TAG = "[UI Events]";

void forwardButtonPressed(lv_event_t *e)
{
    LOG_DEBUG(TAG, "Forward button pressed");
    writeDisplayCommand(CommandNext);
}

void backButtonPressed(lv_event_t *e)
{
    LOG_DEBUG(TAG, "Back button pressed");
    writeDisplayCommand(CommandPrevious);
}

void pauseButtonPressed(lv_event_t *e)
{
    LOG_DEBUG(TAG, "Pause button pressed");
    writeDisplayCommand(CommandPause);
}

void playButtonPressed(lv_event_t *e)
{
    LOG_DEBUG(TAG, "Play button pressed");
    writeDisplayCommand(CommandPlay);
}