#include "irCom.h"

/*  Sätter upp alla GPIO på expandern till output och gör dessa låga. 
    Startar Interupt-rutinen för att läsa och 
    irsend.begin ser till att lysdioden är av*/
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

irDir prevValue;
uint8_t dir = 0;
bool loopIR(Adafruit_MCP23008 &mcp, IRsend &irsend, IRrecv &irrecv, irDir &irdir, uint8_t id)
{
    bool ret = false;
    mcp.digitalWrite(recvWest, LOW);
    mcp.digitalWrite(recvEast, LOW);
    switch (dir)
    {
        {
        case WEST:
            Serial.print("West (0) ");
            mcp.digitalWrite(recvWest, HIGH);
            break;
        case EAST:
            Serial.print("East (1) ");
            mcp.digitalWrite(recvEast, HIGH);
            break;
        default:

            break;
        }
    }
    irrecv.resume(); // Receive the next value
    delay(2000);
    //unsigned long time = millis();
    //while(millis() < time + 1000)
    //{
    //    sendIR(mcp, irsend, id);
    //    delay(250);
    //}
    decode_results results;
    if (irrecv.decode(&results, NULL))
    {
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
            if (dir == recvDIR)
            {
                Serial.println(" CORRECT SIDE ");
                if (prevValue.values[dir] == recvID)
                {
                    Serial.print(" same as previous, send to server! ");
                    irdir.values[dir] = recvID;
                    ret = true;
                }
                else
                {
                    irdir.values[dir] = 0;
                }
                prevValue.values[dir] = recvID;
            }
            results.value = 0;
        }
    }
    else
    {
        if (prevValue.values[dir] == 0)
        {
            irdir.values[dir] = 0;
        }
        prevValue.values[dir] = 0;
    }
    if (++dir == 2)
    {
        dir = 0;
    }
    Serial.println();
    return ret;
}

void sendIR(Adafruit_MCP23008 &mcp, IRsend &irsend, uint8_t ID)
{
    uint64_t idMsg = 0xFF0F0FFFUL;
    idMsg |= (uint64_t)ID << 12;

    mcp.digitalWrite(irNorth, LOW);
    mcp.digitalWrite(irSouth, LOW);
    mcp.digitalWrite(irWest, LOW);

    mcp.digitalWrite(irEast, HIGH);
    delay(5);
    irsend.sendNEC((idMsg | ((uint64_t)WEST << 20)));
    mcp.digitalWrite(irEast, LOW);

    mcp.digitalWrite(irWest, HIGH);
    delay(5);
    irsend.sendNEC((idMsg | ((uint64_t)EAST << 20)));
    mcp.digitalWrite(irWest, LOW);
}