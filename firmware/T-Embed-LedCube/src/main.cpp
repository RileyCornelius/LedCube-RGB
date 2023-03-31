#include <Arduino.h>

#include "ui/lv_setup.h"
#include "pin_config.h"

void setup()
{
  Serial.begin(115200);
  lv_begin(); // Setup display and inputs with LVGL
}

void loop()
{
  lv_handler(); // Handles LVGL events
}