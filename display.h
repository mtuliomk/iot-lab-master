#ifndef DISPLAY_H
#define DISPLAY_H

#include <TFT_eSPI.h>
#define CGRAM_OFFSET

void startDisplay();
void showStatusList();
void updateStatusList (int id, String text);
void updateStatusListHeader(bool wifiStatus, bool mqttStatud, bool rfStatus);
void drawLampIcon(int x, int y, int size, uint16_t color);
void monitorTouch();

#endif