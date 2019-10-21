#include <Arduino.h>
#include "Adafruit_MCP23008.h"
#include "LOLIN_I2C_BUTTON.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_GFX.h"

#include "defines.h"
#include "letterDisplay.h"
#include "irCom.h"
#include "wifiCom.h"

#include "tests/irTest1.h"
#include "tests/irSendTest.h"
#include "tests/irRecvTest.h"

const uint16_t sendGPIO = 14; // D5
const uint16_t recvGPIO = 13; // D7

IRsend irsend(sendGPIO);
IRrecv irrecv(recvGPIO);
Adafruit_MCP23008 mcp;
Adafruit_SSD1306 display(-1); //64x48 pixlar
I2C_BUTTON button(DEFAULT_I2C_BUTTON_ADDRESS);

irDir currentDir;

void setup()
{
  Serial.begin(9600);
  setupWiFi();
  setupDisplay(display);
  setupIR(mcp, irrecv, irsend);
  //irTest1_setup(mcp, irsend, irrecv);
  //irSendTest_setup(mcp, irsend);
  //irRecvTest_setup(mcp, irrecv);
}

void loop()
{
  //irDir irdir;
  //irTest1_loop(mcp, irsend, irrecv);
  //irSendTest_loop(mcp, irsend);
  //irRecvTest_loop(mcp, irrecv);
  uint8_t id;
  String letter;
  getWiFi(id, letter);
  Serial.println("ID ");
  Serial.print(unsigned(id));
  Serial.println("letter " + letter);
  while (1)
  {
    printLetter(display, letter);
    if(loopIR(mcp, irrecv, irsend, currentDir, id))
    {
      sendNeighborsWiFi(id, currentDir);
    }
    delay(30);
    if(button.get() == 0)
    {
      if(button.BUTTON_A || button.BUTTON_B)  //Inlagd så att vi kan lägga till olika händelser för A/B knappen, just nu funkar båda likadant
      {
        bool result = sendWordWiFi(id);
        if(result) {
          printLetter(display, letter, RIGHT);
        } else {
          printLetter(display, letter, WRONG);
        }
        uint64_t now = millis();
        while(millis() < now + 4000) {  //Håller right/wrong på skärmen i 1s medans den ändå loopar IR
          if(loopIR(mcp, irrecv, irsend, currentDir, id))
          {
            sendNeighborsWiFi(id, currentDir);
          }
        }
      }
    }
  }
}