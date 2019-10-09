#include "irTest1.h"

/* Snabbt test för att se om IR kommunikationen fungerar, skickar ett fast meddelande och skriver ut allt den får in till konsol*/


void irTest1_setup(Adafruit_MCP23008 &mcp, IRsend &irsend, IRrecv &irrecv) {
  // put your setup code here, to run once:
  irsend.begin();
  irrecv.enableIRIn();
  pinMode(D6, OUTPUT);
  Serial.begin(9600);
}

void irTest1_loop(Adafruit_MCP23008 &mcp, IRsend &irsend, IRrecv &irrecv) {
  irsend.sendNEC(0x89ABCDEFUL);
  decode_results results;
  if (irrecv.decode(&results)) {
    // print() & println() can't handle printing long longs. (uint64_t)
    serialPrintUint64(results.value, HEX);
    Serial.println("  ");
    irrecv.resume();  // Receive the next value
  }
  delay(500);
}