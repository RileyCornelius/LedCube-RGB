//* This file was NOT generated

#include <Arduino.h>
#include "ui.h"
#include "../pin_config.h"

void forwardButtonPressed(lv_event_t *e)
{
    Serial.println("Forward button pressed");
    SerialCube.println("next");
}

void backButtonPressed(lv_event_t *e)
{
    Serial.println("Back button pressed");
    SerialCube.println("prev");
}

void pauseButtonPressed(lv_event_t *e)
{
    Serial.println("Pause button pressed");
    SerialCube.println("pause");
}

void playButtonPressed(lv_event_t *e)
{
    Serial.println("Play button pressed");
    SerialCube.println("play");
}