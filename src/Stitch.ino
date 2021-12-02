#include <FastLED.h>

#define NUM_LEDS 29
#define DATA_PIN 3

DEFINE_GRADIENT_PALETTE( blue_gp ) {
  0, 0, 39, 144,
  85, 78, 188, 255,
  170, 41, 114, 182,
  255, 0, 39, 144
};

DEFINE_GRADIENT_PALETTE( purple_gp ) {  
  0, 0, 39, 144,
  85, 0, 29, 79,
  170, 148, 92, 180,
  255, 0, 39, 144
};

CRGB leds[NUM_LEDS];
uint8_t whichPalette = 0;
uint8_t offset;
CRGBPalette16 currentPalette(blue_gp);
CRGBPalette16 targetPalette(purple_gp);

void setup() { 
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);
  offset = 0;
}

void loop() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette(currentPalette, (offset + i * 2) % 256);
  }

  nblendPaletteTowardPalette(currentPalette, targetPalette, 10);

  targetPalette = (whichPalette == 0) ? purple_gp : blue_gp;

  EVERY_N_SECONDS(5) {
    whichPalette = 1 - whichPalette;
  }

  EVERY_N_MILLISECONDS(5) {
    offset = (offset + 1) % 256;
  }

  FastLED.show();
}
