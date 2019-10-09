#include <Arduino.h>
#include "Adafruit_MCP23008.h"
//#include "irTest1.h"
#include "irSendTest.h"
#include "irRecvTest.h"
#include "defines.h"

const uint16_t sendGPIO = 14; // D5
const uint16_t recvGPIO = 13; // D7

IRsend irsend(sendGPIO);
IRrecv irrecv(recvGPIO);
Adafruit_MCP23008 mcp;

void setup()
{
  Serial.begin(9600);
  mcp.begin();
  mcp.pinMode(irNorth, OUTPUT);
  mcp.pinMode(irEast, OUTPUT);
  mcp.pinMode(irSouth, OUTPUT);
  mcp.pinMode(irWest, OUTPUT);
  mcp.pinMode(recvNorth, OUTPUT);
  mcp.pinMode(recvEast, OUTPUT);
  mcp.pinMode(recvSouth, OUTPUT);
  mcp.pinMode(recvWest, OUTPUT);
  //irTest1_setup(mcp, irsend, irrecv);
  //irSendTest_setup(mcp, irsend);
  irRecvTest_setup(mcp, irrecv);
}

void loop()
{
  //irTest1_loop(mcp, irsend, irrecv);
  //irSendTest_loop(mcp, irsend);
  irRecvTest_loop(mcp, irrecv);
}