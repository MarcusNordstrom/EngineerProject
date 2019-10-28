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
  for (size_t i = 0; i < 4; i++)
  {
    currentDir.values[i] = 0;
  }
  
  //test setups, avkommentera för att köra testen (avkommentera även matchande metod_loop i void loop())
  //irTest1_setup(mcp, irsend, irrecv);
  //irSendTest_setup(mcp, irsend);
  //irRecvTest_setup(mcp, irrecv);
}

void loop()
{
  //test loops
  //irTest1_loop(mcp, irsend, irrecv);
  //irSendTest_loop(mcp, irsend);
  //irRecvTest_loop(mcp, irrecv);
  uint8_t id = 0;
  String letter;
  getWiFi(id, letter); //hämtar id och bokstav av servern, returnerar 0 och "" om man inte får svar
  while(id == 0 && letter == "")
  {
    Serial.println("ID unavalible");
    printLetter(display, "!", currentDir);
    delay(10000);
    getWiFi(id, letter);
  }
  Serial.println("ID ");
  Serial.print(unsigned(id));
  Serial.println("letter " + letter);
  while (1) //main loop
  {
    sendIR(mcp, irsend, id);
    printLetter(display, letter, currentDir);
    if (loopIR(mcp, irsend, irrecv, currentDir, id))
    {
      sendNeighborsWiFi(id, currentDir);
    }
    delay(30);
    if (button.get() == 0)
    {
      if (button.BUTTON_A || button.BUTTON_B) //Inlagd så att vi kan lägga till olika händelser för A/B knappen, just nu funkar båda likadant
      {
        bool result = sendWordWiFi(id);
        if (result)
        {
          printLetter(display, letter, currentDir, RIGHT);
        }
        else
        {
          printLetter(display, letter, currentDir, WRONG);
        }
        uint64_t now = millis();
        while (millis() < now + 4000)
        { //Håller right/wrong på skärmen i 4s medans den ändå loopar IR
          sendIR(mcp, irsend, id);
          if (loopIR(mcp, irsend, irrecv, currentDir, id))
          {
            sendNeighborsWiFi(id, currentDir);
          }
        }
      }
    }
  }
}