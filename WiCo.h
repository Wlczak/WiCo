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
#include <PubSubClient.h>

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

    // MQTT
    void connectMQTT(String server, int port);
    void handleInMQTT(char *topic, byte *payload, unsigned int length);
    void reconnectMQTT();
    void runMQTT();
    void publishMQTT(const char *topic, const char *message, bool persistent = false);
    void subscribeMQTT(const char *topic, void (*callback)(const char *, const char *));
    void setMQTTId(const char *id);
    void setMQTTAuth(const char *user, const char *pass);

private:
    void connectMQTT();

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

    // MQTT stuff
    WiFiClient espClient;

    PubSubClient client;

    const char *mqtt_server;
    int mqtt_port;
    const char *mqtt_id = String(random(0xffff), HEX).c_str();
    const char *mqtt_user = "";
    const char *mqtt_pass = "";

    std::vector<std::function<void(const char *, const char *)>> mqtt_subscribers;
    std::vector<const char *> mqtt_topics;

    unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
    char msg[MSG_BUFFER_SIZE];
    int value = 0;
};

#endif
