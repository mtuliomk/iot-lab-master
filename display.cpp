// https://randomnerdtutorials.com/cheap-yellow-display-esp32-2432s028r/#config-file-mac-os
#include "display.h"
#include "TFT_eSPI.h"

#include <XPT2046_Touchscreen.h>
#include <Crypto.h>
#include <SHA256.h>


#define CGRAM_OFFSET


TFT_eSPI tft = TFT_eSPI();

// Touchscreen pins
#define XPT2046_IRQ 36   // T_IRQ
#define XPT2046_MOSI 32  // T_DIN
#define XPT2046_MISO 39  // T_OUT
#define XPT2046_CLK 25   // T_CLK
#define XPT2046_CS 33    // T_CS

#define SCREEN_WIDTH 240 
#define SCREEN_HEIGHT 320

SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

// Touchscreen coordinates: (x, y) and pressure (z)
int x, y, z;

// Print Touchscreen info about X, Y and Pressure (Z) on the Serial Monitor
void printTouchToSerial(int touchX, int touchY, int touchZ) {
  Serial.print("X = ");
  Serial.print(touchX);
  Serial.print(" | Y = ");
  Serial.print(touchY);
  Serial.print(" | Pressure = ");
  Serial.print(touchZ);
  Serial.println();
}

void startDisplay() {
  tft.init();  // Inicializa o display
  tft.invertDisplay(false);
  tft.setRotation(0);         // Ajusta a rotação (0 a 3)
  tft.fillScreen(TFT_BLACK);  // Limpa a tela com preto

  // tft.setFreeFont(&FreeSans9pt7b);  // Configura a fonte

  tft.setTextSize(2);                     // Define o tamanho do texto
  tft.setTextColor(TFT_CYAN, TFT_BLACK);  // Texto branco com fundo preto

  showStatusList();

  touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  touchscreen.begin(touchscreenSPI);
  // Set the Touchscreen rotation in landscape mode
  // Note: in some displays, the touchscreen might be upside down, so you might need to set the rotation to 3: touchscreen.setRotation(3);
  touchscreen.setRotation(0);
}

void monitorTouch() {
  // Checks if Touchscreen was touched, and prints X, Y and Pressure (Z) info on the TFT display and Serial Monitor
  if (touchscreen.tirqTouched() && touchscreen.touched()) {
    // Get Touchscreen points
    TS_Point p = touchscreen.getPoint();
    // Calibrate Touchscreen points with map function to the correct width and height
    x = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
    y = map(p.y, 240, 3800, 1, SCREEN_HEIGHT);
    z = p.z;

    printTouchToSerial(x, y, z);
    delay(100);
  }
}

// Lista de status
#define statusCount 10
String statusList[statusCount] = {
  "WiFi: OK",
  "MQTT: Conectado",
  "RF: Ativo"
};
String previousHash;

String calculateSHA256(String input) {
  SHA256 sha256;
  byte hash[32];
  sha256.reset();
  sha256.update(input.c_str(), input.length());
  sha256.finalize(hash, sizeof(hash));

  String hashString = "";
  for (int i = 0; i < sizeof(hash); i++) {
    if (hash[i] < 16) hashString += "0";
    hashString += String(hash[i], HEX);
  }
  return hashString;
}

String combineStatusList() {
  String combined = "";
  for (int i = 0; i < 10; i++) {
    if (statusList[i].length() > 0) {
      combined += statusList[i];
    }
  }
  return combined;
}

bool hasArrayChanged() {
  String combined = combineStatusList();
  String currentHash = calculateSHA256(combined);

  if (currentHash != previousHash) {
    previousHash = currentHash;  // Atualiza o hash anterior
    return true;                 // Alteração detectada
  }
  return false;  // Sem alterações
}

void updateStatusListHeader(bool wifiStatus, bool mqttStatus, bool rfStatus) {
  String ok = "OK";
  String nok = "Conectando...";
  statusList[0] = "WIFI: " + String(wifiStatus ? ok : nok);
  statusList[1] = "MQTT: " + String(mqttStatus ? ok : nok);
  statusList[2] = "RF: " + String(rfStatus ? ok : nok);
  showStatusList();
}

void updateStatusList(int id, String text) {
  int index = id + 3;
  if (id < 10) {
    statusList[index] = text;
  }
  showStatusList();
}

void showStatusList() {
  if (!hasArrayChanged()) {
    return;
  }

  tft.fillScreen(TFT_BLACK);  // Limpa a tela inteira com fundo preto

  int textHeight = 16 * 2;  // Altura do texto, depende de setTextSize (16px por tamanho)
  int yOffset = 0;
  int lastUsed = 0;

  for (int i = 0; i < statusCount; i++) {
    if (statusList[i].length() > 0) {
      yOffset = lastUsed * textHeight;
      tft.fillRect(0, yOffset, tft.width(), textHeight, TFT_BLACK);  // Limpa linha específica
      tft.setCursor(0, yOffset);
      tft.println(statusList[i]);  // Exibe o texto
      lastUsed++;
    }
  }
  drawLampIcon(180, 50, 30, TFT_YELLOW);  // Desenha o ícone no centro da tela
}

void drawLampIcon(int x, int y, int size, uint16_t color) {
  // Parte superior da lâmpada (cúpula)
  tft.fillCircle(x, y - size / 2, size / 2, color);

  // Parte inferior (haste)
  int baseWidth = size / 3;
  int baseHeight = size / 2;
  tft.fillRect(x - baseWidth / 2, y, baseWidth, baseHeight, TFT_WHITE);

  // Base da lâmpada (retângulo inferior)
  tft.fillRect(x - baseWidth / 2, y + baseHeight, baseWidth, baseHeight / 3, TFT_CYAN);

  // Linhas de "brilho"
  int rayLength = size / 2;
  tft.drawLine(x, y - size, x, y - size - rayLength, TFT_WHITE);
  tft.drawLine(x - size / 2, y - size / 2, x - size / 2 - rayLength, y - size / 2 - rayLength, TFT_WHITE);
  tft.drawLine(x + size / 2, y - size / 2, x + size / 2 + rayLength, y - size / 2 - rayLength, TFT_WHITE);
}
