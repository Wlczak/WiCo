#include "WiCo.h"

void WiCo::connectMQTT(String server, int port)
{
    mqtt_server = server.c_str();
    mqtt_port = port;

    connectMQTT();
}

void WiCo::connectMQTT(){
    client.setClient(espClient);
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(WiCo::handleInMQTT);

    if (mqtt_user == "" || mqtt_pass == "")
    {
        client.connect(mqtt_id);
    }
    else
    {
        client.connect(mqtt_id, mqtt_user, mqtt_pass);
    }
}

void WiCo::handleInMQTT(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

void WiCo::reconnectMQTT()
{
    // Loop until we're reconnected
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        // Create a random client ID
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);
        // Attempt to connect
        Serial.println("Connecting...");
        if (connectMQTT())
        {
            Serial.println("connected");
            // Once connected, publish an announcement...
            client.publish("4hs1/vlceka/wemos/hello", "hello world");
            // ... and resubscribe
            client.subscribe("4hs1/vlceka/wemos/led");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void WiCo::runMQTT()
{
    if (!client.connected())
    {
        reconnectMQTT();
    }
    client.loop();
}

void WiCo::setMQTTId(String id)
{
    mqtt_id = id.c_str();
}

void WiCo::setMQTTAuth(String user, String pass){
    mqtt_user = user.c_str();
    mqtt_pass = pass.c_str();
}