#include <TimedAction.h>
#include "FastLED.h"
#define NUM_LEDS 24
#define BRIGHTNESS  77
#define LED_TYPE    NEOPIXEL
#define COLOR_ORDER RGB
int fb = 255;
CRGB main_sculpt[NUM_LEDS];
CRGB mid_sculpt[NUM_LEDS];
CRGB minor_sculpt[NUM_LEDS];

void setup() {
  delay(3000);
  FastLED.addLeds<LED_TYPE, 8>(main_sculpt, NUM_LEDS);
  FastLED.addLeds<LED_TYPE, 9>(mid_sculpt, NUM_LEDS);
  FastLED.addLeds<LED_TYPE, 10>(minor_sculpt, NUM_LEDS);
  Serial.begin(9600);
}

int clearLed(CRGB sculpt[]) {
  for (int i = 0; i < NUM_LEDS; i++) {
    sculpt[i] =  CRGB(0 , 0, 0);
  }
  FastLED.show();
}

int change_color (CRGB sculpt[], int r, int g, int b, int t, int h, int bright) {
  // Leds apagados, acendem um a um na cor branca com pouco brilho e ficam 1 segundo acesos
  FastLED.setBrightness(bright);
  for (int i = 0; i < NUM_LEDS; i++) {
    sculpt[i] =  CRGB(r , g, b);
    FastLED.show();
    delay(h);
  }
  delay(t);
}
int intensify(int b, int bright, int t, int h) {
  // Leds tem o brilho intensificados e ficam no estado de brilho máximo por 1 segundo
  for (int i = b; i < bright; i++) {
    FastLED.setBrightness(i);
    FastLED.show();
    delay(h);
  }
  delay(t);
}
int dimm(int b, int bright, int t, int h) {
  // Leds tem intensidade reduzida até apagarem e permancem apagados por 1 segundo
  for (int i = b; i >= bright; i--) {
    FastLED.setBrightness(i);
    FastLED.show();
  }
  delay(t);
}
int blink_leads(CRGB sculpt[], int r, int g, int b, int h, int bright) {
  // Leds piscam por 10 vezes e apagam por 1 segundo
  FastLED.setBrightness(bright);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < NUM_LEDS; j++) {
      sculpt[j] =  CRGB(r , g, b);
    }
    FastLED.show();
    delay(h);
    for (int j = 0; j < NUM_LEDS; j++) {
      sculpt[j] =  CRGB(0 , 0, 0);
    }
    FastLED.show();
    delay(h);
  }
}

int main_clear() {
  for (int i = 0; i < NUM_LEDS; i++) {
    main_sculpt[i] =  CRGB(0 , 0, 0);
  }
  FastLED.show();
}
int mid_clear() {
  for (int i = 0; i < NUM_LEDS; i++) {
    mid_sculpt[i] =  CRGB(0 , 0, 0);
  }
  FastLED.show();
}
int minor_clear() {
  for (int i = 0; i < NUM_LEDS; i++) {
    minor_sculpt[i] =  CRGB(0 , 0, 0);
  }
  FastLED.show();
}
int main() {
  clearLed(main_sculpt);
  change_color(main_sculpt, 255, 255, 255, 1000, 42, 77);
  intensify(77, 255, 2000, 200);
  change_color(main_sculpt, 112, 254, 255, 1000, 84, 77);
  change_color(main_sculpt, 255, 255, 255, 1000, 42, 255);
  dimm(255, 0, 1000, 200);
  blink_leads(main_sculpt, 255, 255, 255, 20, 77);
  clearLed(main_sculpt);
}
int mid() {
  clearLed(mid_sculpt);
  blink_leads(mid_sculpt, 255, 255, 255, 15, 77);
  intensify(254, 255, 1000, 200);
  dimm(255, 0, 1000, 200);
  intensify(254, 255, 0, 200);
  change_color(mid_sculpt, 142, 244, 68, 2000, 84, 255);
  dimm(255, 0, 1000, 200);
  change_color(mid_sculpt, 255, 255, 255, 2000, 42, 255);
  clearLed(mid_sculpt);
}
int minor() {
  clearLed(minor_sculpt);
  change_color(minor_sculpt, 142, 0, 255, 2000, 84, 255);
  change_color(minor_sculpt, 255, 255, 255, 2000, 84, 255);
  blink_leads(minor_sculpt, 255, 255, 255, 15, 255);
  change_color(minor_sculpt, 142, 0, 255, 3000, 125, 255);
  clearLed(minor_sculpt);
}

void loop() {
  if (Serial.available() > 0) {
    // read the incoming byte:
    char incomingByte = Serial.read();
    if (incomingByte == 'L') {
      mid();
      main();
      minor();
    }
    else if (incomingByte == 'R') {
      minor();
      main();
      mid();
    }
    else if (incomingByte == 'I') {
      mid();
    }
    else if (incomingByte == 'M') {
      main();
    }
    else if(incomingByte == 'A');
    minor();
  }
}
