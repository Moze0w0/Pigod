#include <Arduino.h>
#include <SPI.h>
#include <BleGamepad.h>

const int dataPin = 19;   /* Q7 */
const int clockPin = 18;  /* CP */
const int latchPin = 21;  /* PL */

const int numBits = 16;   /* Set to 8 * number of shift registers */

void setup() {
  Serial.begin(115200);
  pinMode(dataPin, INPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
}

void loop() {
  // Step 1: Sample
  digitalWrite(latchPin, LOW);
  digitalWrite(latchPin, HIGH);

  // Step 2: Shift
  Serial.print("Bits: ");
  for (int i = 0; i < numBits; i++) {
    int bit = digitalRead(dataPin);
    if (bit == HIGH) {
      Serial.print("1");
    } else {
      Serial.print("0");
    }
    digitalWrite(clockPin, HIGH); // Shift out the next bit
    digitalWrite(clockPin, LOW);
  }

  Serial.println();
  delay(1000);
}