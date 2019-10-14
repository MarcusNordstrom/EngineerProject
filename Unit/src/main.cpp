#include <Arduino.h>
#include "Adafruit_MCP23008.h"
#include "LOLIN_I2C_BUTTON.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_GFX.h"

#include "defines.h"
#include "letterDisplay.h"
#include "irCom.h"

#include "tests/irTest1.h"
#include "tests/irSendTest.h"
#include "tests/irRecvTest.h"

const uint16_t sendGPIO = 14; // D5
const uint16_t recvGPIO = 13; // D7

IRsend irsend(sendGPIO);
IRrecv irrecv(recvGPIO);
Adafruit_MCP23008 mcp;
Adafruit_SSD1306 display(-1); //64x48 pixlar
//I2C_BUTTON button;

irDir irdir;

void setup()
{
  Serial.begin(9600);
  setupDisplay(display);
  setupIR(mcp, irrecv, irsend, irdir);
  //irTest1_setup(mcp, irsend, irrecv);
  //irSendTest_setup(mcp, irsend);
  //irRecvTest_setup(mcp, irrecv);
}

void loop()
{
  //irTest1_loop(mcp, irsend, irrecv);
  //irSendTest_loop(mcp, irsend);
  //irRecvTest_loop(mcp, irrecv);
  loopIR(mcp, irrecv, irsend, irdir, 2);
  delay(1000);
}