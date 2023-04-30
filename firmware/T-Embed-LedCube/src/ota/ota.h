#include <WiFi.h>
#include <ArduinoOTA.h>
#include <Logger.h>
#include "ui/ui.h"
#include "ui/lv_setup.h"
#include "config.h"
#include "secret.h" // This file is not included in the repository it contains WiFi credentials

// Enter your WiFi credentials here
// #define WIFI_SSID ""
// #define WIFI_PASS ""

static const char *TAG = "[OTA]";

void otaBegin()
{
#if OTA_ENABLE
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    LOG_INFO(TAG, "WiFi connecting..");
    uint16_t timeout = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);

        timeout++;
        if (timeout > 30)
        {
            LOG_WARN(TAG, "WiFi connection failed!");
            return;
        }
    }

    // Host name to be used for OTA updates
    ArduinoOTA.setHostname("ledcube-display");

    ArduinoOTA
        .onStart([]()
                 { 
                    LOG_INFO(TAG, "Start updating");
                    lv_scr_load(ui_ota_screen);
                    lv_label_set_text(ui_ota_device_name_text, "Display");
                    lv_handler(); })
        .onEnd([]()
               { LOG_INFO(TAG, "End updating"); })
        .onProgress([](unsigned int progress, unsigned int total)
                    { 
                        LOG_INFO(TAG, "Progress: %u%%\r", (progress / (total / 100)));
                        String progressStr = String(progress / (total / 100));
                        lv_bar_set_value(ui_progress_bar, progressStr.toInt(), LV_ANIM_ON);
                        progressStr += "%";
                        lv_label_set_text(ui_progress_text, progressStr.c_str());
                        lv_handler(); })
        .onError([](ota_error_t error)
                 {
                LOG_ERROR(TAG, "Error[%u]: ", error);
            if (error == OTA_AUTH_ERROR)
                LOG_ERROR(TAG, "Auth Failed");
            else if (error == OTA_BEGIN_ERROR)
                LOG_ERROR(TAG, "Begin Failed");
            else if (error == OTA_CONNECT_ERROR)
                LOG_ERROR(TAG, "Connect Failed");
            else if (error == OTA_RECEIVE_ERROR)
                LOG_ERROR(TAG, "Receive Failed");
            else if (error == OTA_END_ERROR)
                LOG_ERROR(TAG, "End Failed"); });

    ArduinoOTA.begin();

    LOG_INFO(TAG, "Connected to: " + WiFi.SSID());
    LOG_INFO(TAG, "IP address: " + WiFi.localIP().toString());
    LOG_INFO(TAG, "Hostname: " + ArduinoOTA.getHostname());
#endif
}

void otaHandle()
{
#if OTA_ENABLE
    if (WiFi.status() == WL_CONNECTED)
        ArduinoOTA.handle();
#endif
}