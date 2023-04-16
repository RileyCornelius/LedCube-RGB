//* This file was NOT generated

#include <Arduino.h>
#include "ui.h"
#include "../pin_config.h"

void forwardButtonPressed(lv_event_t *e)
{
    Serial.println("Forward button pressed");
    CubeSerial.println("next");
}

void backButtonPressed(lv_event_t *e)
{
    Serial.println("Back button pressed");
    CubeSerial.println("prev");
}

void pauseButtonPressed(lv_event_t *e)
{
    Serial.println("Pause button pressed");
    CubeSerial.println("pause");
}

void playButtonPressed(lv_event_t *e)
{
    Serial.println("Play button pressed");
    CubeSerial.println("play");
}