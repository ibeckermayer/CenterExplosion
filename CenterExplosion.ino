#include <FastLED.h>
#define NUM_LEDS 100
#define DATA_PIN 6
#define COLOR_1 Blue
#define COLOR_2 Red

CRGB leds[NUM_LEDS];
const int beam_length = 10;
const int delay_time = 100;

void setup() { 
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(9600);
}

// Set "beam_length" pixels ahead of the input integer to COLOR_1
void set_beam_length_ahead(int i) {
  for (int j=i;j<i+beam_length;j++) {
    leds[j]=CRGB::COLOR_1;          // Set the beam_length pixels ahead to COLOR_1
    for (int k=0;k<i;k++) {
      leds[k]=CRGB::Black;          // Set all the pixels behind to off
    }
  }
}

void set_beam_length_behind(int i) {
  for (int j=i;j>i-beam_length;j--) {
    leds[j]=CRGB::COLOR_2;          // Set the beam_length pixels behind to COLOR_2
    for (int k=NUM_LEDS;k>i;k--) {
      leds[k]=CRGB::Black;          // Set all the pixels behind to off
    }
  }
}

void launch_at_center() {
  for (int l=0;l<NUM_LEDS/2-beam_length+1;l++) {
    set_beam_length_ahead(l);
    set_beam_length_behind(NUM_LEDS-l);
    delay(delay_time);
    FastLED.show();
  }
}

void loop() {
  launch_at_center();
  FastLED.clear();


  
//  for (int j=NUM_LEDS; j>0; j--) {
//    for (int k=NUM_LEDS;k>=j;k--) {
//      leds[k]=CRGB::Black;
//    }
//    leds[j]=CRGB::Purple;
//    FastLED.show(); 
//    delay(3);
//  }
//
//  for (int l=0;l<NUM_LEDS;l++) {
//    for (int f=0;f<=l;f++) {
//      leds[f]=CRGB::Black;
//    }
//    leds[l]=CRGB::Purple;
//    FastLED.show();
//    delay(3);
//  }
  
}
