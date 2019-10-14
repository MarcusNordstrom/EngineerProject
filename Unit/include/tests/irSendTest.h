#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRutils.h>
#include <Wire.h>
#include "defines.h"
#include "Adafruit_MCP23008.h"

void irSendTest_setup(Adafruit_MCP23008 &mcp, IRsend &irsend);
void irSendTest_loop(Adafruit_MCP23008 &mcp, IRsend &irsend);