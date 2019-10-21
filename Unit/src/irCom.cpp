#include "irCom.h"

void setupIR(Adafruit_MCP23008 &mcp, IRrecv &irrecv, IRsend &irsend)
{
    mcp.begin();
    //Set all output
    mcp.pinMode(irNorth, OUTPUT);
    mcp.pinMode(irEast, OUTPUT);
    mcp.pinMode(irSouth, OUTPUT);
    mcp.pinMode(irWest, OUTPUT);
    mcp.pinMode(recvNorth, OUTPUT);
    mcp.pinMode(recvEast, OUTPUT);
    mcp.pinMode(recvSouth, OUTPUT);
    mcp.pinMode(recvWest, OUTPUT);
    //Set all low
    //mcp.writeGPIO(0x00);
    mcp.digitalWrite(irNorth, LOW);
    mcp.digitalWrite(irEast, LOW);
    mcp.digitalWrite(irSouth, LOW);
    mcp.digitalWrite(irWest, LOW);
    mcp.digitalWrite(recvNorth, LOW);
    mcp.digitalWrite(recvEast, LOW);
    mcp.digitalWrite(recvSouth, LOW);
    mcp.digitalWrite(recvWest, LOW);

    irsend.begin();

    irrecv.enableIRIn();
}

uint8_t dir = 0;
irDir prevValue;
irDir confirmedValues;
bool loopIR(Adafruit_MCP23008 &mcp, IRrecv &irrecv, IRsend &irsend, irDir& irdir, uint8_t ID)
{
    //GPIO
    mcp.digitalWrite(irNorth, LOW);
    mcp.digitalWrite(irEast, LOW);
    mcp.digitalWrite(irSouth, LOW);
    mcp.digitalWrite(irWest, LOW);
    mcp.digitalWrite(recvNorth, LOW);
    mcp.digitalWrite(recvEast, LOW);
    mcp.digitalWrite(recvSouth, LOW);
    mcp.digitalWrite(recvWest, LOW);

    switch (dir)
    {
    case WEST:
        //Serial.print("WEST (0): ");
        mcp.digitalWrite(irWest, HIGH);
        mcp.digitalWrite(recvWest, HIGH);
        break;
    case EAST:
        //Serial.print("EAST (1): ");
        mcp.digitalWrite(irWest, HIGH);
        mcp.digitalWrite(recvWest, HIGH);
        break;
    default:
        break;
    }
    //SEND
    uint64_t sendValue = 0xFF0F0FFFUL;
    sendValue |= (uint64_t)ID << 12;
    sendValue |= (uint64_t)dir << 20;
    for (size_t o = 0; o < 3; o++)
    {
        irsend.sendNEC(sendValue, kNECBits, 3); //irsend.sendNEC(sendValue);
        delay(10);
    }

    //recive
    delay(500);
    decode_results results;
    if (irrecv.decode(&results, NULL))
    {
        Serial.print("  ");
        serialPrintUint64(results.value, HEX);
        Serial.print(" ");
        if ((results.value & 0xFF0F0FFF) == 0xFF0F0FFF)
        {
            Serial.print("MESSAGE ID = ");
            uint8_t recvID = (results.value  & 0x0000F000) >> 12;
            uint8_t recvDIR = (results.value & 0x00F0000) >> 20;
            Serial.print(unsigned(recvID) + " DIR = " + unsigned(recvDIR));
            if(dir == recvDIR)
            {
                Serial.println("CORRECT SIDE");
            }
            //TODO: lägg in om det är uppdaterade ID från grannar så return true;

        }
        results.value = 0;
        irrecv.resume(); // Receive the next value
    }
    Serial.println();
    //Loop
    if (++dir == 2) //only loop west/east
    {
        dir = 0;
    }
    return false;
}