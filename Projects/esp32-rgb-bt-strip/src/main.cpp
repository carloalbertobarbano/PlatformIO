#define FASTLED_ESP8266_RAW_PIN_ORDER

#include <FastLED.h>
#include <EEPROM.h>

#undef MS_COUNTER
#define MS_COUNTER timer0_millis_count


#define LED_PIN     13
#define NUM_LEDS    14
#define LED_TYPE WS2811
#define BRIGHTNESS 60
CRGB leds[NUM_LEDS];

#ifndef MCUSR
    int MCUSR = 2;
#endif

void red_stripe() {
    for(int dot = 0; dot < NUM_LEDS; dot++) { 
        leds[dot] = CRGB::Red;
        FastLED.show();
        delay(35);
    }
    FastLED.clear(true);
}

void red_chaser() {
    for(int dot = 0; dot < NUM_LEDS; dot++) { 
        leds[dot] = CRGB::Red;
        FastLED.show();
        // clear this led for the next time around the loop
        leds[dot] = CRGB::Black;
        delay(20);
    }

    FastLED.clear(true);
}

void white_stripe() {
    for(int dot = 0; dot < NUM_LEDS; dot++) { 
        leds[dot] = CRGB::White;
        FastLED.show();
        delay(35);
    }
    FastLED.clear(true);
}

void blink_red() {
    FastLED.showColor(CRGB::Red);
    delay(500);
    FastLED.clear(true);
    delay(500);
}

void blink_white() {
    FastLED.showColor(CRGB::White);
    delay(500);
    FastLED.clear(true);
    delay(500);
}

void breath_red() {
    fill_solid(leds, NUM_LEDS, CRGB::Red);
    static const float q = 0.367879441171;
    static const float eminusq = 2.71828182846 - q;
    float breath = (exp(sin(millis()/250.0)) - q)/(eminusq) * 128 - 1;

    FastLED.setBrightness((int)breath);
    FastLED.show();
    delay(10);
}

void breath_red2() {
    fill_solid(leds, NUM_LEDS, CRGB::Red);

    float scale_factor = 0.00001;
    float scale_pow = 0.001;
    static float start = millis();
    static float tick = 0;
    float breath = 0;

    if (tick*scale_factor <= 1.0) {
        breath = pow(tick*scale_pow, 0.7) * BRIGHTNESS;    
    } else {
        breath = (sin(tick*scale_pow + PI/2. - 1)/2. + 0.5) * BRIGHTNESS;
    }
    
    FastLED.setBrightness((int)breath);
    FastLED.show();
    delay(500);
    
    Serial.println(breath);
    tick += millis() - start;
    if (tick*scale_factor >= 4) {
        start = millis();
        tick = 0;
    }
}

void (*animation_fn[])() = { red_stripe, red_chaser, white_stripe, blink_red, blink_white, breath_red };
const unsigned int animation_num = 6;
const unsigned int eeprom_register = 0;
unsigned int animation_idx = 5;

void setup() {
    FastLED.addLeds<LED_TYPE, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.clear(true);
    // delay(1000);

    Serial.begin(9600);
    
    if (MCUSR == 2) { 
        Serial.println("Reset button was pressed, incrementing animation_idx");
        animation_idx = EEPROM.read(eeprom_register);
        animation_idx = (animation_idx + 1) % animation_num;
        EEPROM.write(eeprom_register, animation_idx);
    } else {
        Serial.println("Power was interuppted");
        animation_idx = EEPROM.read(eeprom_register);
    }
    
    MCUSR = 0;
    Serial.print("Selected animation: ");
    Serial.println(animation_idx);
}


void loop() { 
   (*animation_fn[animation_idx])();
}