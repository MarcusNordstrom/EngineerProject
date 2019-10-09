#include "irRecvTest.h"

/* testa ta emot meddelande från alla håll */

void irSendTest_setup(Adafruit_MCP23008 &mcp, IRrecv &irrecv)
{
    // put your setup code here, to run once:
    mcp.digitalWrite(recvNorth, LOW);
    mcp.digitalWrite(recvEast, LOW);
    mcp.digitalWrite(recvSouth, LOW);
    mcp.digitalWrite(recvWest, LOW);
    irrecv.enableIRIn();
    Serial.begin(9600);
}

int recvState = 0;

void irSendTest_loop(Adafruit_MCP23008 &mcp, IRrecv &irrecv)
{
    switch (recvState)
    {
        {
        case 0: //North
            Serial.println("NORTH");
            mcp.digitalWrite(recvNorth, HIGH);
            mcp.digitalWrite(recvEast, LOW);
            mcp.digitalWrite(recvSouth, LOW);
            mcp.digitalWrite(recvWest, LOW);
            break;
        case 1: //East
            Serial.println("EAST");
            mcp.digitalWrite(recvNorth, LOW);
            mcp.digitalWrite(recvEast, HIGH);
            mcp.digitalWrite(recvSouth, LOW);
            mcp.digitalWrite(recvWest, LOW);
            break;
        case 2: //South
            Serial.println("SOUTH");
            mcp.digitalWrite(recvNorth, LOW);
            mcp.digitalWrite(recvEast, LOW);
            mcp.digitalWrite(recvSouth, HIGH);
            mcp.digitalWrite(recvWest, LOW);
            break;
        case 3: //West
            Serial.println("WEST");
            mcp.digitalWrite(recvNorth, LOW);
            mcp.digitalWrite(recvEast, LOW);
            mcp.digitalWrite(recvSouth, LOW);
            mcp.digitalWrite(recvWest, HIGH);
            break;
        default:
            break;
        }
    }
    delay(50);
    decode_results results;
    if (irrecv.decode(&results, NULL))
    {
        // print() & println() can't handle printing long longs. (uint64_t)
        serialPrintUint64(results.value, HEX);
        Serial.println("  ");
        irrecv.resume(); // Receive the next value
    }
    ++recvState;
    if (recvState == 4)
    {
        recvState = 0;
    }
    delay(500);
}