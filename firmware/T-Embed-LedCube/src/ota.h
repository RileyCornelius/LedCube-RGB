#include <WiFi.h>
#include <ArduinoOTA.h>
#include "ui/ui.h"
#include "ui/lv_setup.h"
#include "secret.h" // This file is not included in the repository it contains the WiFi credentials

// Enter your WiFi credentials here
// #define WIFI_SSID ""
// #define WIFI_PASS ""

void otaBegin()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    Serial.print("WiFi connecting");
    uint16_t timeout = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(200);
        Serial.print(".");

        timeout++;
        if (timeout > 30)
        {
            Serial.println("\nWiFi connection failed!");
            return;
        }
    }

    // Host name to be used for OTA updates
    ArduinoOTA.setHostname("ledcube-display");

    ArduinoOTA
        .onStart([]()
                 { 
                    Serial.println("Start updating");
                    lv_scr_load(ui_ota_screen);
                    lv_label_set_text(ui_ota_device_name_text, "Display");
                    lv_handler(); })
        .onEnd([]()
               { Serial.println("\nEnd"); })
        .onProgress([](unsigned int progress, unsigned int total)
                    { 
                        String data = String(progress / (total / 100)) + "%";
                        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
                        lv_label_set_text(ui_progress_text, data.c_str());
                        data.remove(data.length() - 1); // remove the % sign
                        lv_bar_set_value(ui_progress_bar, data.toInt(), LV_ANIM_ON);
                        lv_handler(); })
        .onError([](ota_error_t error)
                 {
            Serial.printf("Error[%u]: ", error);
            if (error == OTA_AUTH_ERROR)
                Serial.println("Auth Failed");
            else if (error == OTA_BEGIN_ERROR)
                Serial.println("Begin Failed");
            else if (error == OTA_CONNECT_ERROR)
                Serial.println("Connect Failed");
            else if (error == OTA_RECEIVE_ERROR)
                Serial.println("Receive Failed");
            else if (error == OTA_END_ERROR)
                Serial.println("End Failed"); });

    ArduinoOTA.begin();

    Serial.println("\nConnected to: " + WiFi.SSID());
    Serial.println("IP address: " + WiFi.localIP().toString());
    Serial.println("Hostname: " + ArduinoOTA.getHostname());
}

void otaHandle()
{
    if (WiFi.status() == WL_CONNECTED)
        ArduinoOTA.handle();
}