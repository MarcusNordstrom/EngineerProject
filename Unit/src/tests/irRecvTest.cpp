#include "tests/irRecvTest.h"

/* testa ta emot meddelande från alla håll */

void irRecvTest_setup(Adafruit_MCP23008 &mcp, IRrecv &irrecv)
{
    // put your setup code here, to run once:
    mcp.digitalWrite(recvNorth, LOW);
    mcp.digitalWrite(recvEast, LOW);
    mcp.digitalWrite(recvSouth, LOW);
    mcp.digitalWrite(recvWest, LOW);
    irrecv.enableIRIn();
}

int recvState = 0;

void irRecvTest_loop(Adafruit_MCP23008 &mcp, IRrecv &irrecv)
{
    mcp.digitalWrite(recvNorth, LOW);
    mcp.digitalWrite(recvEast, LOW);
    mcp.digitalWrite(recvSouth, LOW);
    mcp.digitalWrite(recvWest, LOW);
    switch (recvState)
    {
        {
        case 0: //North
            Serial.print("NORTH ");
            mcp.digitalWrite(recvNorth, HIGH);
            mcp.digitalWrite(recvEast, LOW);
            mcp.digitalWrite(recvSouth, LOW);
            mcp.digitalWrite(recvWest, LOW);
            break;
        case 1: //East
            Serial.print("EAST ");
            mcp.digitalWrite(recvNorth, LOW);
            mcp.digitalWrite(recvEast, HIGH);
            mcp.digitalWrite(recvSouth, LOW);
            mcp.digitalWrite(recvWest, LOW);
            break;
        case 2: //South
            Serial.print("SOUTH ");
            mcp.digitalWrite(recvNorth, LOW);
            mcp.digitalWrite(recvEast, LOW);
            mcp.digitalWrite(recvSouth, HIGH);
            mcp.digitalWrite(recvWest, LOW);
            break;
        case 3: //West
            Serial.print("WEST ");
            mcp.digitalWrite(recvNorth, LOW);
            mcp.digitalWrite(recvEast, LOW);
            mcp.digitalWrite(recvSouth, LOW);
            mcp.digitalWrite(recvWest, HIGH);
            break;
        default:
            break;
        }
    }
    delay(500);
    decode_results results;
    if (irrecv.decode(&results, NULL))
    {
        // print() & println() can't handle printing long longs. (uint64_t)
        Serial.print("  ");
        serialPrintUint64(results.value, HEX);
        Serial.print(" ");
        serialPrintUint64((results.value && 0xFFFF0FFFUL), HEX);
        //Serial.print(resultToHumanReadableBasic(&results));
        results.value = 0;
        irrecv.resume(); // Receive the next value
    }
    
    Serial.println("");
    ++recvState;
    if (recvState == 4)
    {
        recvState = 0;
    }
    delay(500);
}