#include "tests/irSendTest.h"

/* testa skicka 4 olika meddelande */

void irSendTest_setup(Adafruit_MCP23008 &mcp, IRsend &irsend)
{
    // put your setup code here, to run once:
    mcp.digitalWrite(irNorth, LOW);
    mcp.digitalWrite(irEast, LOW);
    mcp.digitalWrite(irSouth, LOW);
    mcp.digitalWrite(irWest, LOW);
    irsend.begin();
}

void irSendTest_loop(Adafruit_MCP23008 &mcp, IRsend &irsend)
{
    Serial.println("NORTH");
    mcp.digitalWrite(irNorth, HIGH);
    irsend.sendNEC(0x00000000UL);
    mcp.digitalWrite(irNorth, LOW);
    delay(500);
    Serial.println("EAST");
    mcp.digitalWrite(irEast, HIGH);
    irsend.sendNEC(0x11111111UL);
    mcp.digitalWrite(irEast, LOW);
    delay(500);
    Serial.println("SOUTH");
    mcp.digitalWrite(irSouth, HIGH);
    irsend.sendNEC(0x22222222UL);
    mcp.digitalWrite(irSouth, LOW);
    delay(500);
    Serial.println("WEST");
    mcp.digitalWrite(irWest, HIGH);
    irsend.sendNEC(0x33333333UL);
    mcp.digitalWrite(irWest, LOW);
    delay(500);
}