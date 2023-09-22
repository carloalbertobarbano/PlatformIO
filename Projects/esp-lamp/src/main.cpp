#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

const uint8_t NUMPIXELS = 17;
const uint8_t headlights_pin = 4;
const uint8_t PIXELS_OFFSET = 0;


Adafruit_NeoPixel pixels(NUMPIXELS, headlights_pin, NEO_GRB + NEO_KHZ800);
                                              
                                              
void setup() {
  pinMode(headlights_pin, OUTPUT);
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_BUILTIN_AUX, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(LED_BUILTIN_AUX, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(LED_BUILTIN_AUX, LOW);
  delay(1000);

  uint8_t brightness = 255;
  pixels.setBrightness(brightness);
  pixels.rainbow((uint16_t)(millis() * 100)); //, 1, 255, brightness);
  // pixels.fill((uint32_t)(millis() * 100));
  pixels.show();
}