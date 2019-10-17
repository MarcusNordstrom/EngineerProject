#include "irCom.h"

void setupIR(Adafruit_MCP23008 &mcp, IRrecv &irrecv, IRsend &irsend, irDir &irdir)
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

int dir = 0;
void loopIR(Adafruit_MCP23008 &mcp, IRrecv &irrecv, IRsend &irsend, irDir &irdir, uint8_t ID)
{
    mcp.digitalWrite(recvNorth, LOW);
    mcp.digitalWrite(recvEast, LOW);
    mcp.digitalWrite(recvSouth, LOW);
    mcp.digitalWrite(recvWest, LOW);

    //Send part
    uint64_t sendValue = 0xFFFF0FFFUL;
    sendValue |= (uint64_t)ID << 12;
    mcp.digitalWrite(irNorth, HIGH);
    mcp.digitalWrite(irEast, HIGH);
    mcp.digitalWrite(irSouth, HIGH);
    mcp.digitalWrite(irWest, HIGH);
    for (size_t o = 0; o < 3; o++)
    {
        irsend.sendNEC(sendValue);
        delay(10);
    }
    mcp.digitalWrite(irNorth, LOW);
    mcp.digitalWrite(irEast, LOW);
    mcp.digitalWrite(irSouth, LOW);
    mcp.digitalWrite(irWest, LOW);
    //Recv part
    //irDir raw_data[2];
    switch (dir)
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
        if (!((results.value xor 0xFFFF0FFF) % 0x1000))
        {
            Serial.print("MESSAGE");
        }
        //Serial.print(resultToHumanReadableBasic(&results));
        results.value = 0;
        irrecv.resume(); // Receive the next value
    }

    Serial.println("");
    ++dir;
    if (dir == 4)
    {
        dir = 0;
    }
}
