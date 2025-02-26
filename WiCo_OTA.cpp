#include "WiCo.h"

void WiCo::startOTA()
{
    if (!isOTAActive)
    {
        if (ota_host != "")
        {
            ArduinoOTA.setHostname(ota_host.c_str());
        }
        if (ota_pass != "")
        {
            ArduinoOTA.setPassword(ota_pass.c_str());
        }
        if (ota_port != 0)
        {
            ArduinoOTA.setPort(ota_port);
        }

        ArduinoOTA.onStart([]()
                           { Serial.println("Start"); });
        ArduinoOTA.onEnd([]()
                         { Serial.println("\nEnd"); });
        ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
                              { Serial.printf("Progress: %u%%\r", (progress / (total / 100))); });
        ArduinoOTA.onError([](ota_error_t error)
                           {
            Serial.printf("Error[%u]: ", error);
            if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
            else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
            else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
            else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
            else if (error == OTA_END_ERROR) Serial.println("End Failed"); });

        ArduinoOTA.begin();
        isOTAActive = true;
    }
}

void WiCo::stopOTA()
{
    if (isOTAActive)
    {
        ArduinoOTA.end();
        isOTAActive = false;
    }
}

void WiCo::runOTA()
{
    if (isOTAActive)
    {
        ArduinoOTA.handle();
    }
}

void WiCo::setOTAsettings(String host = "", String password = "", int port = 0)
{
    if (host != "")
    {
        ota_host = host;
    }
    if (password != "")
    {
        ota_pass = password;
    }
    if (port != 0)
    {
        ota_port = port;
    }
}