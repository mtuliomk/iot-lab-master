#include "iot_aws_module.h"

#include <WiFiClientSecure.h>
WiFiClientSecure wifiClient;

void setupIoT(PubSubClient& client, const char* mqtt_server, int mqtt_port) {

  wifiClient.setCACert(CA_CERT);
  wifiClient.setCertificate(CLIENT_CERT);
  wifiClient.setPrivateKey(CLIENT_KEY);

  // Associa o WiFiClientSecure ao PubSubClient
  client.setClient(wifiClient);
  client.setServer(mqtt_server, mqtt_port);
  client.setBufferSize(1024);
  Serial.println("Conectando ao AWS IoT...");
  reconnectMQTT(client);
}

void reconnectMQTT(PubSubClient& client) {
  while (!client.connected()) {
    Serial.print("Tentando se conectar ao AWS IoT...");
    Serial.println(THING);
    if (client.connect(THING)) {
      Serial.println("Conectado ao AWS IoT");
    } else {
      Serial.print("Falha ao conectar. Código de erro: ");
      Serial.println(client.state());
      Serial.println("Tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}

void publishToThing(PubSubClient& client, const char* thingName, const char* powerState) {
  String topic = String("$aws/things/") + thingName + "/shadow/update";
  String payload = String("{\"state\":{\"desired\":{\"powerState\":\"") + powerState + "\"}}}";

  Serial.print("Publicando em: ");
  Serial.println(topic);

  Serial.print("Payload: ");
  Serial.println(payload);

  if (client.publish(topic.c_str(), payload.c_str())) {
    Serial.println("Publicado com sucesso!");
  } else {
    Serial.println("Falha ao publicar!");
  }
}


