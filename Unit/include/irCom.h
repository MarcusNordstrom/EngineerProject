#include <Adafruit_MCP23008.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <Wire.h>
#include "defines.h"

typedef struct {
    int8_t north;
    int8_t east;
    int8_t south;
    int8_t west;
} irDir;

void setupIR(Adafruit_MCP23008 &mcp, IRrecv &irrecv, IRsend &irsend, irDir &irDir);

void loopIR(Adafruit_MCP23008 &mcp, IRrecv &irrecv, IRsend &irsend, irDir &irDir, uint8_t ID);