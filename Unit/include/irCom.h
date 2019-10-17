#include <Adafruit_MCP23008.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <Wire.h>
#include "defines.h"

typedef struct {
    int8_t values[4] ;
} irDir;

void setupIR(Adafruit_MCP23008 &mcp, IRrecv &irrecv, IRsend &irsend, irDir &irDir);

void loopIR(Adafruit_MCP23008 &mcp, IRrecv &irrecv, IRsend &irsend, irDir &irDir, uint8_t ID);