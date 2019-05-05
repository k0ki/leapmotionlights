#include "FastLED.h"
#define NUM_LEDS 24
#define BRIGHTNESS  255
#define LED_TYPE    WS2812
#define COLOR_ORDER RGB
int fb = 255; 
CRGB main_sculpt[NUM_LEDS];
CRGB mid_sculpt[NUM_LEDS];
CRGB minor_sculpt[NUM_LEDS];

void setup() {
  delay(2000);
  clearLed(main_sculpt);
  clearLed(mid_sculpt);
  clearLed(minor_sculpt);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.setDither(0);
  FastLED.addLeds<LED_TYPE, 8,COLOR_ORDER>(main_sculpt, NUM_LEDS);
  FastLED.addLeds<LED_TYPE, 9,COLOR_ORDER>(mid_sculpt, NUM_LEDS);
  FastLED.addLeds<LED_TYPE, 10,COLOR_ORDER>(minor_sculpt, NUM_LEDS);
  Serial.begin(9600);
}

void loop() {
  clearLed(main_sculpt);
  clearLed(mid_sculpt);
  clearLed(minor_sculpt);
  if (Serial.available() > 0) {
    
    // read the incoming byte:
    char incomingByte = Serial.read();
    if (incomingByte == 'L') {
      mainr();
      midr();
      minorr();
    } 
    else if (incomingByte == 'R') {
      minorr();
      mainr();
      midr();
    }
    else if (incomingByte == 'I') {
      midr();
    }
    else if (incomingByte == 'M') {
      mainr();
    }
    else if(incomingByte == 'A'){
    minorr();
    }
  }
}

void clearLed(struct CRGB *leds) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] =  CRGB(0 , 0, 0);
  }
  FastLED.show();
}

void change_color (struct CRGB *leds, int r, int g, int b, int t, int h, int bright) {
  FastLED.setBrightness(bright);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] =  CRGB(r , g, b);
    FastLED.show();
    delay(h);
  }
  delay(t);
}
void intensify(int b, int bright, int t, int h) {
  // Leds tem o brilho intensificados e ficam no estado de brilho máximo por 1 segundo
  for (int i = b; i < bright; i++) {
    FastLED.setBrightness(i);
    FastLED.show();
    delay(h); 
  }
  delay(t);
}
void dimm(int b, int bright, int t, int h) {
  // Leds tem intensidade reduzida até apagarem e permancem apagados por 1 segundo
  for (int i = b; i >= bright; i--) {
    FastLED.setBrightness(i);
    FastLED.show();
    delay(h);
  }
  delay(t);
}
void blink_leads(CRGB *leds, int r, int g, int b, int h, int bright) {
  FastLED.setBrightness(bright);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < NUM_LEDS; j++) {
      leds[j] =  CRGB(r , g, b);
    }
    FastLED.show();
    delay(h);
    for (int j = 0; j < NUM_LEDS; j++) {
      leds[j] =  CRGB(0 , 0, 0);
    }
    FastLED.show();
    delay(h);
  }
}

void mainr() {
  clearLed(main_sculpt);
  change_color(main_sculpt, 255, 255 , 255, 0, 2, 51);
  intensify(51, 255, 200, 0);
  change_color(main_sculpt, 0, 255, 255, 200, 2, 255);
  change_color(main_sculpt, 0, 0, 255, 200, 2, 255);
  change_color(main_sculpt, 255, 255, 255, 0, 2, 255);
  blink_leads(main_sculpt, 255, 255, 255, 10, 255);
  clearLed(main_sculpt);
}
void midr() {
  clearLed(mid_sculpt);
  blink_leads(mid_sculpt, 255, 255, 255, 15, 255);
  change_color(mid_sculpt,143,0 ,255,200,2,255);
  change_color(mid_sculpt, 204, 0, 255, 200, 2, 255);
  change_color(mid_sculpt, 255, 255, 255, 100, 2, 255);
  clearLed(mid_sculpt);
}
void minorr() {
  clearLed(minor_sculpt);
  change_color(minor_sculpt, 255, 255, 255, 100, 2, 255);
  dimm(255,26,0,2);
  change_color(minor_sculpt, 102, 255, 0, 100, 2, 255);
  change_color(minor_sculpt, 0, 255, 255, 100, 2, 255);
  change_color(minor_sculpt, 255, 255, 255, 100, 2, 255);
  clearLed(minor_sculpt);
}
