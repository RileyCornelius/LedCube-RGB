#include <Arduino.h>

#include "ui/lv_setup.h"
#include "ui/ui.h"
#include "ui/ui_helpers.h"
#include "ota.h"
#include "pin_config.h"

void getUartData()
{
  while (CubeSerial.available())
  {
    String data = CubeSerial.readStringUntil('\n');
    data.trim();
    if (data == "playing")
      lv_obj_add_state(ui_playImage, LV_STATE_CHECKED);
    else if (data == "paused")
      lv_obj_clear_state(ui_playImage, LV_STATE_CHECKED);
    else
      lv_label_set_text(ui_aninmationText, data.c_str());
  }
}

void setup()
{
  CubeSerial.begin(115200);
  Serial.begin(115200);
  lv_begin(); // Setup display and inputs with LVGL
  ui_init();
  otaBegin();
}

void loop()
{
  otaHandle();
  getUartData();
  lv_handler(); // Update the display
}