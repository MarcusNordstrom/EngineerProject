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
        case NORTH: //North
            Serial.print("NORTH ");
            mcp.digitalWrite(recvNorth, HIGH);
            mcp.digitalWrite(recvEast, LOW);
            mcp.digitalWrite(recvSouth, LOW);
            mcp.digitalWrite(recvWest, LOW);
            break;
        case EAST: //East
            Serial.print("EAST ");
            mcp.digitalWrite(recvNorth, LOW);
            mcp.digitalWrite(recvEast, HIGH);
            mcp.digitalWrite(recvSouth, LOW);
            mcp.digitalWrite(recvWest, LOW);
            break;
        case SOUTH: //South
            Serial.print("SOUTH ");
            mcp.digitalWrite(recvNorth, LOW);
            mcp.digitalWrite(recvEast, LOW);
            mcp.digitalWrite(recvSouth, HIGH);
            mcp.digitalWrite(recvWest, LOW);
            break;
        case WEST: //West
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
        if ((results.value & 0xFF0F0FFF) == 0xFF0F0FFF)
        {
            Serial.print("MESSAGE ID = ");
            uint16_t recvID = (results.value & 0x0000F000) >> 12;
            uint16_t recvDIR = (results.value & 0x00F00000) >> 20;
            Serial.print(unsigned(recvID));
            Serial.print(" DIR = ");
            Serial.print(unsigned(recvDIR));
            if (recvState == recvDIR)
            {
                Serial.println(" CORRECT SIDE ");
            }
        }
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