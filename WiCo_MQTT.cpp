#include "WiCo.h"

void WiCo::connectMQTT(String server, int port)
{
    mqtt_server = server.c_str();
    mqtt_port = port;

    connectMQTT();
}

void WiCo::connectMQTT()
{
    client.setClient(espClient);
    client.setBufferSize(1024);
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback([this](char *topic, byte *payload, unsigned int length)
                       { handleInMQTT(topic, payload, length); });

    if (mqtt_user == "" || mqtt_pass == "")
    {
        client.connect(mqtt_id);
    }
    else
    {
        Serial.println("Connecting...");
        Serial.print("Id: ");
        Serial.println(mqtt_id);
        Serial.print("User: ");
        Serial.println(mqtt_user);
        Serial.print("Pass: ");
        Serial.println(mqtt_pass);

        client.connect(mqtt_id, mqtt_user, mqtt_pass);
    }
}

void WiCo::handleInMQTT(char *topic, byte *payload, unsigned int length)
{
    std::string message;
    for (int i = 0; i < length; i++)
    {
        message += static_cast<char>(payload[i]);
    }

    for (size_t i = 0; i < mqtt_topics.size(); ++i)
    {
        if (strcmp(topic, mqtt_topics[i]) == 0)
        {
            mqtt_subscribers[i](topic, message.c_str());
        }
    }

    /*
     Serial.print("Message arrived [");
     Serial.print(topic);
     Serial.print("] ");
     for (int i = 0; i < length; i++)
     {
         Serial.print((char)payload[i]);
     }
     Serial.println();*/
}

void WiCo::reconnectMQTT()
{
    // Loop until we're reconnected
    while (!client.connected())
    {
        connectMQTT();
        if (!client.connected())
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(3000);
        }
    }
}

void WiCo::publishMQTT(const char *topic, const char *message, bool persistent)
{
    client.publish(topic, message, persistent);
}

void WiCo::subscribeMQTT(const char *topic, void (*callback)(const char *, const char *))
{
    client.subscribe(topic);
    mqtt_topics.push_back(topic);
    mqtt_subscribers.push_back(callback);
}

void WiCo::runMQTT()
{
    if (!client.connected())
    {
        reconnectMQTT();
    }
    client.loop();
}

void WiCo::setMQTTId(const char *id)
{
    mqtt_id = id;
}

void WiCo::setMQTTAuth(const char *user, const char *pass)
{
    mqtt_user = user;
    mqtt_pass = pass;
}