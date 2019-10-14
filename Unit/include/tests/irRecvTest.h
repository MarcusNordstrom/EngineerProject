#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <Wire.h>
#include "defines.h"
#include "Adafruit_MCP23008.h"

void irRecvTest_setup(Adafruit_MCP23008 &mcp, IRrecv &irrecv);
void irRecvTest_loop(Adafruit_MCP23008 &mcp, IRrecv &irrecv);