#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <Wire.h>
#include "Adafruit_MCP23008.h"

void irTest1_setup(Adafruit_MCP23008 &mcp, IRsend &irsend, IRrecv &irrecv);
void irTest1_loop(Adafruit_MCP23008 &mcp, IRsend &irsend, IRrecv &irrecv);