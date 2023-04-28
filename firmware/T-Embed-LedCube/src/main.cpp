#include <Arduino.h>

#include "ui/lv_setup.h"
#include "ui/ui.h"
#include "ui/ui_helpers.h"
#include "ota.h"
#include "pin_config.h"

void getUartData()
{
  while (SerialCube.available())
  {
    String data = SerialCube.readStringUntil('\n');
    data.trim();
    if (data == "playing")
      lv_obj_add_state(ui_play_image, LV_STATE_CHECKED);
    else if (data == "paused")
      lv_obj_clear_state(ui_play_image, LV_STATE_CHECKED);
    else if (data == "ota start")
      lv_scr_load(ui_ota_screen);
    else if (data == "ota end")
      lv_scr_load(ui_main_screen);
    else if (data.endsWith("%"))
    {
      lv_label_set_text(ui_progress_text, data.c_str());
      data.remove(data.length() - 1); // remove the % sign
      lv_bar_set_value(ui_progress_bar, data.toInt(), LV_ANIM_ON);
    }
    else
      lv_label_set_text(ui_animation_text, data.c_str());
  }
}

void setup()
{
  SerialCube.begin(115200);
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