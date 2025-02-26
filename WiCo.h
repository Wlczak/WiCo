#ifndef WiCo_h
#define WiCo_h

#include <Arduino.h> // imports arduino stadard lib
#include <string>
#include <vector>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <ArduinoOTA.h>
#include <WiFiUdp.h>




class WiCo
{
public:
    // initialization
    WiCo();

    // AP methods
    void startAP();
    void stopAP();
    String getAPIP();

    // STA connect methods
    void connectSTA();
    void disconnectSTA();
    void setSTAtimeout(int timeout);
    void addSTA(const char *ssid, const char *psk);

    // webserver methods
    void startWebServer();
    void stopWebServer();
    void handleWebServer();
    void setWebStructure();

    // OTA
    void startOTA();
    void runOTA();
    void stopOTA();
    void setOTAsettings(String host, String password, int port);

private:
    // settings setting methods
    void setAPsettings();

    // checking variables
    bool isAPActive = false;
    bool isSTAActive = false;

public:
    bool isWebserverRunning = false;

private:
    // AP settings
    int ap_max_devices;
    String ap_ssid;
    String ap_psk;
    int ap_ch;
    bool ap_hide_ssid;

    // STA settings
    int sta_timeout = 0;
    std::vector<const char *> sta_ssid;
    std::vector<const char *> sta_psk;

    // OTA settings
    String ota_host = "";
    int ota_port = 0;
    String ota_pass = "";
    bool isOTAActive = false;

    // STA class
    ESP8266WiFiMulti wifiMulti;

    // web server
    ESP8266WebServer *server;
};

#endif
