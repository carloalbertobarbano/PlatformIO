#include <Arduino.h>


void setup() {
  pinMode(D2, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_BUILTIN_AUX, OUTPUT);
}

void loop() {
  digitalWrite(D2, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(LED_BUILTIN_AUX, HIGH);
  delay(1000);

  digitalWrite(D2, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(LED_BUILTIN_AUX, LOW);
  delay(1000);
}
