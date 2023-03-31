#include <Arduino.h>
#include <TFT_eSPI.h> // https://github.com/Bodmer/TFT_eSPI
#include <lvgl.h>     // https://github.com/lvgl/lvgl

#include "ui/lv_setup.h"
#include "ui/ui.h"
#include "pin_config.h"

void setup()
{
  lv_begin(); // Setup LVGL
}

void loop()
{
  lv_timer_handler(); /* let the GUI do its work */
  delay(5);
}