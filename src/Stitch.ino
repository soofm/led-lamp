#include <FastLED.h>

#define NUM_LEDS 29
#define DATA_PIN 3
#define MAX_POWER_MILLIAMPS 500
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];
uint8_t whichPalette = 0;
uint8_t offset = 0;
CRGBPalette16 purple_palette = { 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000020, 0x000020,
                                 0x00008B, 0x00008B, 0x720752, 0x80095B, 0x980084, 0x9C0090, 0x604618, 0x808078 };

void setup() {
  delay(3000);
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS)
    .setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(255);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, MAX_POWER_MILLIAMPS);
}

void loop() {
  fill_solid(leds, NUM_LEDS, CRGB(2, 2, 10));
  
  for (int i = 0; i < NUM_LEDS; i++) {
    // adds a slow spinning effect
    uint32_t offset = NUM_LEDS - ((millis() / 500) % NUM_LEDS);
    // use a noise function to sample random values from the palette
    uint8_t index = inoise8((i + offset) * 24, millis() / 10);
    CRGB color = ColorFromPalette(purple_palette, index);
    leds[i] += color;
  }

  FastLED.show();
}