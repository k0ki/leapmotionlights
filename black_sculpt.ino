#include "FastLED.h"
#define NUM_LEDS 144
#define BRIGHTNESS  77
#define LED_TYPE    WS2812
#define COLOR_ORDER RGB
int fb = 255;
int sensor = 2;
int state = LOW;
int val = 0;
CRGB black_sculpt[NUM_LEDS];

void setup() {
  delay(3000);
  FastLED.addLeds<LED_TYPE, 7,COLOR_ORDER>(black_sculpt, NUM_LEDS); 
  Serial.begin(9600);
  pinMode(sensor, INPUT);
}

void loop(){
  Serial.println("Motion detected!"); 
  val = digitalRead(sensor);   // read sensor value
  if (val == HIGH) {           // check if the sensor is HIGH
    main();   // turn LED ON
    delay(100);                // delay 100 milliseconds 
    
    if (state == LOW) {
      Serial.println("Motion detected!"); 
      state = HIGH;       // update variable state to HIGH
    }
  } 
  else {
      delay(200);             // delay 200 milliseconds 
      
      if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;       // update variable state to LOW
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

int main() {
  clearLed(black_sculpt);
  change_color(black_sculpt, 255, 255 , 255, 0, 2, 51);
  intensify(51, 255, 200, 0);
  change_color(black_sculpt, 0, 255, 255, 200, 2, 255);
  change_color(black_sculpt, 0, 0, 255, 200, 2, 255);
  change_color(black_sculpt, 255, 255, 255, 0, 2, 255);
  blink_leads(black_sculpt, 255, 255, 255, 10, 255);
  clearLed(black_sculpt);
}
