#include <Arduino.h>

void setup() {
  // initialize digital pins LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D1, OUTPUT);
  Serial.begin(9600);
  Serial.println("WAAAT");
  delay(10);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(D1, HIGH);
  Serial.println("High");
  delay(1000); // wait for a second
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(D1, LOW);
  Serial.println("Low");
  delay(1000); // wait for a second
}