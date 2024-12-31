#ifndef IOT_MODULE_H
#define IOT_MODULE_H

#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include "things.h"


// Declarações das funções de configuração do IoT
void setupIoT(PubSubClient& client, const char* mqtt_server, int mqtt_port);
void reconnectMQTT(PubSubClient& client);

void publishToThing(PubSubClient& client, const char* thingName, const char* powerState);

#endif
