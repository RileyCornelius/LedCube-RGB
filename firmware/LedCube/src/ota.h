#include <WiFi.h>
#include <ArduinoOTA.h>
#include "secret.h" // This file is not included in the repository it contains the WiFi credentials

// Enter your WiFi credentials here
const char *ssid;
const char *pass;

void otaBegin()
{
#ifdef SECRET_H
    ssid = WIFI_SSID;
    pass = WIFI_PASS;
#endif

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);

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
    ArduinoOTA.setHostname("ledcube");

    ArduinoOTA
        .onStart([]()
                 { Serial.println("Start updating"); })
        .onEnd([]()
               { Serial.println("\nEnd"); })
        .onProgress([](unsigned int progress, unsigned int total)
                    { Serial.printf("Progress: %u%%\r", (progress / (total / 100))); })
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