#include <Arduino.h>
#include <Logger.h>

#include "ui/lv_setup.h"
#include "ota/ota.h"
#include "com/cube_com.h"
#include "config.h"



void setup()
{
    SerialCube.begin(115200);
    Serial.begin(115200);
    lv_begin(); // Setup display and inputs with LVGL
    ui_init();
    initOta();
}

void loop()
{
    handleOta();
    handleCom();
    lv_handler(); // Update the display
}