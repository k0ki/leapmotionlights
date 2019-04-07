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

void change_color (int r, int g, int b, int t, int h, int bright) {
// Leds apagados, acendem um a um na cor branca com pouco brilho e ficam 1 segundo acesos
  FastLED.setBrightness(bright);
  for (int i=0; i<NUM_LEDS;i++){
      black_sculpt[i] =  CRGB(r ,g, b); 
      FastLED.show(); 
      delay(h);
  }
  delay(t);
}
void intensify(int b, int bright,int t,int h){
// Leds tem o brilho intensificados e ficam no estado de brilho máximo por 1 segundo
  for (int i=b; i<bright;i++){
     FastLED.setBrightness(i);
     FastLED.show();
     delay(h); 
  }
delay(t);
}
void dimm(int b,int bright,int t, int h){
// Leds tem intensidade reduzida até apagarem e permancem apagados por 1 segundo
  for (int i=b; i>=bright;i--){
     FastLED.setBrightness(i);
     FastLED.show(); 
  }
   delay(t);
}
void blink_leads(int r, int g, int b, int h, int bright){
// Leds piscam por 10 vezes e apagam por 1 segundo
  FastLED.setBrightness(bright);
  for (int i=0; i<10;i++){
     for (int j=0; j<NUM_LEDS;j++){
        black_sculpt[j] =  CRGB(r ,g, b);  
     }
     FastLED.show();
    delay(h);
       for (int j=0; j<NUM_LEDS;j++){
        black_sculpt[j] =  CRGB(0 ,0, 0);   
     }
     FastLED.show();
  delay(h);
  }
}
void clearLed() {
  for (int i = 0; i < NUM_LEDS; i++) {
    black_sculpt[i] =  CRGB(0 , 0, 0);
  }
  FastLED.show();
}
int main() {
    Serial.println("Motion detected!");
    intensify(70,255,1000,200);
    Serial.println("Motion detected!");
    blink_leads(255,255,255,30,255);
    Serial.println("Motion detected!");
    dimm(255,25,1000,200);
    Serial.println("Motion detected!");
    change_color(0,255,255,3000,42,25);
    Serial.println("Motion detected!");
    change_color(101,0,255,3000,42,25);
    Serial.println("Motion detected!");
    change_color(142,244,68,3000,42,25);
    Serial.println("Motion detected!");
    dimm(25,0,0,200);
    Serial.println("Motion detected!");
    intensify(254,255,2000,200);
    Serial.println("Motion detected!");
    change_color(0,0,0,0,42,255);
    Serial.println("Motion detected!");
}
