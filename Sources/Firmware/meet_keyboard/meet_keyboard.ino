//Elliotmade 4/27/2020
//https://elliotmade.com/2020/04/23/physical-mute-button-for-zoom-meetings/
//https://www.youtube.com/watch?v=apGbelheIzg
//Used a digispark clone

//this will switch to the zoom application and mute it or exit on long press
//momentary button on pin 0 with pullup resistor
//momentary button on pin 0 with pullup resistor


//Libraries
#include "OneButton.h"
#include "DigiKeyboard.h"
#include <Adafruit_NeoPixel.h>

//  Definitions, constants
#define MIC_ON    1
#define MIC_OFF   0
#define VID_ON    1
#define VID_OFF   0

#define PIN 1
#define STRIPSIZE 3

//set up leds
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIPSIZE, PIN, NEO_GRB + NEO_KHZ800);


//  strip.SetPixelColor(0, hslRed);
//  strip.Show();

// Variables
int button1pin = 2;
int button2pin = 0;
int button3pin = 0;

int mic_state = MIC_ON;
int vid_state = VID_ON;
int b=0;
int side=0;

//set up buttons
OneButton button1(button1pin, true);
OneButton button2(button2pin, true);
OneButton button3(button3pin, true);

void setup() {
  // set up leds
  strip.begin();
 // strip.setBrightness(25);  // Lower brightness and save eyeballs!
  strip.show(); // Initialize all pixels to 'off'
  //set up button functions

  button1.attachClick(click1);
  button2.attachClick(click2);
  button3.attachClick(click3);

  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.delay(500);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //monitor buttons
  switch(side){
    case 0:
      if(b<255){b++;}
      else{side = 1;}
    break;
    case 1:
      if(b>1){b--;}
      else{side = 0;}
    break;
    }
  b++;
  button1.tick();
  button2.tick();  
  button3.tick();
  strip.setPixelColor(1,strip.Color(0, 0, b));


}

// This function will be called when the button1 was pressed 1 time (and no 2. button press followed).
void click1() {
  switch(mic_state){
    case MIC_OFF:
        DigiKeyboard.sendKeyStroke(KEY_D, MOD_CONTROL_LEFT);
        strip.setPixelColor(0,strip.Color(64, 0, 0));
        mic_state = MIC_ON;
        break;
    case MIC_ON: 
        DigiKeyboard.sendKeyStroke(KEY_D, MOD_CONTROL_LEFT);
        strip.setPixelColor(0,strip.Color(64, 0, 0));
        mic_state = MIC_OFF;
        break;
    }
} // click1

// This function will be called when the button2 was pressed 1 time (and no 2. button press followed).
void click2() {
  switch(mic_state){
    case VID_OFF:
        DigiKeyboard.sendKeyStroke(KEY_E, MOD_CONTROL_LEFT);
        strip.setPixelColor(2,strip.Color(0, 64, 0));
        mic_state = MIC_ON;
        break;
    case VID_ON: 
        DigiKeyboard.sendKeyStroke(KEY_E, MOD_CONTROL_LEFT);
        strip.setPixelColor(2,strip.Color(0, 64,0));
        mic_state = MIC_OFF;
        break;
    }
} // click2

// This function will be called once, when the button1 is pressed for a long time.
void click3() {
   DigiKeyboard.sendKeyStroke(KEY_D, MOD_CONTROL_LEFT);  
} // longPressStart1
