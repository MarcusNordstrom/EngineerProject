#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint16_t kIrLed = 14;
IRsend irsend(kIrLed);

void setup() {
  // put your setup code here, to run once:
  irsend.begin();
  Serial.begin(9600, SERIAL_8N1, SERIAL_TX_ONLY);
}

void loop() {
  // put your main code here, to run repeatedly:
  irsend.sendNEC(0x00FFE01FUL);
  delay(2000);
}