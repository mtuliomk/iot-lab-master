#define MQTT_MAX_PACKET_SIZE 1024

#include <stdint.h>
#include <RCSwitch.h>
#include <ArduinoJson.h>

#include "wifi_module.h"
#include "things.h"
#include "iot_aws_module.h"

RCSwitch mySwitch = RCSwitch();

// Credenciais de Wi-Fi
const char* ssid = "Tulio-AP";
const char* password = "F54$iatr*2863";

const char* mqttServer = "a2hrfsgkuw6dwa-ats.iot.us-east-1.amazonaws.com";
const int mqttPort = 8883;

uint16_t thingStates = 0b0000000000000000;  // Inicialmente, todos os 16 bits desligados
struct ThingInfo {
  String slug;
  uint8_t bitPosition;
  int frequency;
};
ThingInfo things[] = {
  { "FirstTestDevice", 0, 2565608 },
  { "SecondTestDevice", 1, 6460648 }
};

ThingInfo* getThingInfo(String slug) {
  for (int i = 0; i < sizeof(things) / sizeof(things[0]); i++) {
    if (things[i].slug == slug) {
      return &things[i];  // Retorna o endereço da ThingInfo encontrada
    }
  }
  return nullptr;  // Retorna nullptr se não encontrar
}

ThingInfo* getThingInfo(int frequency) {
  for (int i = 0; i < sizeof(things) / sizeof(things[0]); i++) {
    if (things[i].frequency == frequency) {
      return &things[i];  // Retorna o endereço da ThingInfo encontrada
    }
  }
  return nullptr;  // Retorna nullptr se não encontrar
}

const int ledPin = 2;  // GPIO do LED interno

// Inicializa o cliente MQTT
PubSubClient client;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  Serial.begin(115200);
  Serial.println("Starting...");

  mySwitch.enableReceive(15);  // Configura o receptor no GPIO15

  // Conecta ao Wi-Fi
  setupWiFi(ssid, password);

  setupIoT(client, mqttServer, mqttPort);
  client.setCallback(callback);

  subscribeAll();
}

void subscribeTopic(String topic) {
  String acceptedTopic = "$aws/things/" + topic + "/shadow/get/accepted";
  String deltaTopic = "$aws/things/" + topic + "/shadow/update/delta";
  String getTopic = "$aws/things/" + topic + "/shadow/get";

  if (client.subscribe(acceptedTopic.c_str())) {
    Serial.println("Inscrito no tópico accepted");
  } else {
    Serial.println("Falha ao se inscrever no tópico accepted");
  }
  delay(100);

  if (client.subscribe(deltaTopic.c_str())) {
    Serial.println("Inscrito no tópico delta");
  } else {
    Serial.println("Falha ao se inscrever no tópico delta");
  }
  delay(100);

  if (client.publish(getTopic.c_str(), "{}")) {
    Serial.println("Solicitação publicada no tópico get");
  } else {
    Serial.println("Falha ao publicar no tópico get");
  }
}

void subscribeAll() {
  subscribeTopic("SecondTestDevice");
  digitalWrite(ledPin, LOW);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("TOPIC: ");
  Serial.println(topic);

  // Copiar o payload para uma string
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("MESSAGE: ");
  Serial.println(message);

  // Parse do JSON
  JsonDocument doc;  // Ajuste o tamanho conforme necessário
  DeserializationError error = deserializeJson(doc, message);

  if (error) {
    Serial.println("Erro ao processar JSON:");
    Serial.println(message);
    return;
  }

  String powerState;
  if (String(topic).endsWith("/get/accepted")) {
    powerState = doc["state"]["reported"]["powerState"] | "";
  }

  if (String(topic).endsWith("/update/delta")) {
    powerState = doc["state"]["powerState"] | "";
  }

  String slug;
  int start = String(topic).indexOf("things/") + 7;
  int end = String(topic).indexOf("/shadow");
  if (start > 0 && end > start) {
    slug = String(topic).substring(start, end);
  }

  Serial.print("Mudando o status de: ");
  Serial.println(slug);

  ThingInfo* thing = getThingInfo(slug);
  thingStates ^= (1 << thing->bitPosition);  // alterna o status
}

void loop() {
  client.loop();
  if (!client.connected()) {
    digitalWrite(ledPin, HIGH);
    reconnectMQTT(client);
    subscribeAll();
  }
  if (mySwitch.available()) {
    int receivedValue = mySwitch.getReceivedValue();
    if (receivedValue == 0) {
      Serial.println("Nenhum código recebido.");
    } else {
      Serial.println(receivedValue);
      switchPressed(receivedValue);
    }
    mySwitch.resetAvailable();
  }
}

void switchPressed(int code) {
  Serial.print("Código recebido: ");
  Serial.println(code);
  switchThing(code);
  delay(2000);
}

void switchThing(int receivedFrequency) {
  ThingInfo* thing = getThingInfo(receivedFrequency);
  if (thing != nullptr) {
    Serial.print("Pressionando ");
    Serial.println(thing->slug);

    if (thingStates & (1 << thing->bitPosition)) {  // ligado
      publishToThing(client, thing->slug.c_str(), "OFF");
      Serial.println("Desligando");
    } else {
      publishToThing(client, thing->slug.c_str(), "ON");
      Serial.println("Ligando");
    }
  }
}
