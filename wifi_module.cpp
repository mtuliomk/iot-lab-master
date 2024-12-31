#include "wifi_module.h"
#include <WiFi.h>

void setupWiFi(const char* ssid, const char* password) {
  Serial.println("Conectando ao Wi-Fi...");
  WiFi.begin(ssid, password);

  // Aguarda até que a conexão seja estabelecida
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Conectado ao Wi-Fi.");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

