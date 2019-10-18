#include <ESP8266WiFi.h>

#include "defines.h"

void setupWiFi(void);
void getWiFi(uint8_t& id, String& letter);
void sendNeighborsWiFi(uint8_t id, irDir neighbors);
bool sendWordWiFi(void);