#include <FastLED.h>
#define NUM_LEDS 99 // Make this an odd number
#define DATA_PIN 6
#define COLOR_1 Red
#define COLOR_2 Red
#define CHARGING_COLOR_1 Purple
#define CHARGING_COLOR_2 Yellow

CRGB leds[NUM_LEDS];
const int beam_length = 5;
const int initial_beam_speed = 60; // lower = faster
const int mid_pix = NUM_LEDS/2;
const int charge_length = 500;

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
    for (int k=NUM_LEDS+1;k>i;k--) {
      leds[k]=CRGB::Black;          // Set all the pixels behind to off
    }
  }
}

void initialize_beams() {
  for (int i=0;i<beam_length;i++){
    leds[i]=CRGB::COLOR_1;
    leds[NUM_LEDS-1-i]=CRGB::COLOR_2;
    FastLED.show();
    if (i<beam_length-1)
      delay(initial_beam_speed);
  }
}


// launch the initialized beams at center
void launch_at_center() {
  for (int l=0;l<=NUM_LEDS/2-beam_length;l++) {
    set_beam_length_ahead(l);
    set_beam_length_behind(NUM_LEDS-1-l);
    delay(initial_beam_speed);
    FastLED.show();
  }
}

void charge_center() {
  int a = beam_length;
  for (int i=0;i<charge_length;i++) {
    if (i%2==0) {
      leds[mid_pix]=CRGB::CHARGING_COLOR_1;
    }
    else {
      leds[mid_pix]=CRGB::CHARGING_COLOR_2;
    }
    delay(80);
    FastLED.show();
//    if (a>0) {
//      leds[mid_pix+a]=CRGB::Black;
//      leds[mid_pix-a]=CRGB::Black;
//      a--;
//    }
  }
}

void loop() {
  initialize_beams();
  launch_at_center();
  charge_center();
  delay(4000);
//  set_beam_length_behind(NUM_LEDS);
//  FastLED.show();
//  delay(1000);
  FastLED.clear();
}
