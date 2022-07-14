 /*
  Based on Sketch built by Gustavo Silveira (aka Music Nerd)
  Modified by Dolce Wang

  This code is only for Arduinos that use ATmega328 (like Uno, Mega, Nano, Beetle...)

*/


// Change values with //*** 


// LIBRARIES
#include <MIDI.h> // by Francois Best
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
MIDI_CREATE_DEFAULT_INSTANCE(); 


// BUTTONS
const int NButtons = 12; //***  total number of push buttons
const int buttonPin[NButtons] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}; //*** define digital pins connected from button to Arduino; (ie {10, 16, 14, 15, 6, 7, 8, 9, 2, 3, 4, 5}; 12 buttons)
                                        //** Button NOTE will go up chromatically.  ie. if button is digi pin 2, C; Pin 3, C#; Pin 3, D; etc
                                   
int buttonCState[NButtons] = {};        // stores the button current value
int buttonPState[NButtons] = {};        // stores the button previous value

const int pixelPin = A4;
const int noPixels = 66;
Adafruit_NeoPixel strip(noPixels, pixelPin, NEO_GRB + NEO_KHZ800);
uint32_t pixelColor[noPixels];
uint32_t black = strip.Color(0, 0, 0);
bool pixelOn[noPixels];

// debounce
unsigned long lastDebounceTime[NButtons] = {0};  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    //* the debounce time; increase if the output flickers

// POTENTIOMETERS
const int NPots = 4; //*** total numbers of pots (slide & rotary)
const int potPin[NPots] = {A3, A2, A1, A0}; //*** Analog pins of each pot connected straight to the Arduino i.e 4 pots, {A3, A2, A1, A0};
                                          // have nothing in the array if 0 pots {}

int potCState[NPots] = {0}; // Current state of the pot; delete 0 if 0 pots
int potPState[NPots] = {0}; // Previous state of the pot; delete 0 if 0 pots
int potVar = 0; // Difference between the current and previous state of the pot

int midiCState[NPots] = {0}; // Current state of the midi value; delete 0 if 0 pots
int midiPState[NPots] = {0}; // Previous state of the midi value; delete 0 if 0 pots
int octavePotPastState = 0;

const int TIMEOUT = 300; //** Amount of time the potentiometer will be read after it exceeds the varThreshold
const int varThreshold = 10; //** Threshold for the potentiometer signal variation
boolean potMoving[NPots]; // If the potentiometer is moving
unsigned long PTime[NPots] = {0}; // Previously stored time; delete 0 if 0 pots
unsigned long timer[NPots] = {0}; // Stores the time that has elapsed since the timer was reset; delete 0 if 0 pots


// MIDI
byte midiCh = 1; //** MIDI channel to be used; You can add more if you need to reorganize or have a billion buttons/pots
byte note = 60; //** First note to be used for digital buttons, then go up chromatically in scale according to the sequence in your "buttonPin" array
                // you can look up on a Midi Note chart; 36=C2; 60=Middle C
byte cc = 1; //** First MIDI CC to be used for pots on Analog Pins in order of the "potPin" array; then goes up by 1

byte commandByte;
byte noteByte;
byte velocityByte;

void checkMIDI(){
  do{
    if (Serial.available()){
       commandByte = Serial.read();//read first byte
       noteByte = Serial.read();//read next byte
       velocityByte = Serial.read();//read final byte
        if (commandByte == 144){//if note on message
         //check if note == 60 and velocity > 0
         uint16_t noteColor = map(noteByte, 36, 97, 0, 65535);
         uint32_t rgbcolor = strip.ColorHSV(noteColor, 123, 123);
         pixelColor[0] = rgbcolor;
         pixelOn[0] = true;
     }
    }
  }
  while (Serial.available() > 2);//when at least three bytes available
}

// SETUP
void setup() { 

  Serial.begin(115200); //**  Baud Rate 31250 for MIDI class compliant jack | 115200 for Hairless MIDI
  strip.begin();
  strip.setBrightness(200);
  strip.show();
  // Buttons
  // Initialize buttons with pull up resistors
  for (int i = 0; i < NButtons; i++) {
    pinMode(buttonPin[i], INPUT_PULLUP);
  }
  for(int i = 0; i < noPixels; i++)
  {
    pixelColor[i] = black;
    pixelOn[i] = false;
  }

}


// LOOP
void loop() {
  buttons();
  potentiometers();
  if(millis() % 20 == 0)
  {
    neopixels();
  }
  checkMIDI();
}

void neopixels()
{
  strip.setBrightness(200);
  for(int i = 0; i < noPixels; i++)
  {
    if(pixelOn)
    {
     strip.setPixelColor(i, pixelColor[i]);
    }
  }
  for(int i = noPixels-1; i >= 0; i--)
  {
     if(pixelOn[i])
     {
        if(i == noPixels-1)
        {
          pixelColor[i] = black;
        } else {
         pixelColor[i+1] = strip.getPixelColor(i);
         pixelOn[i+1] = true;
         pixelColor[i] = black;
         pixelOn[i] = false;
        }
     }
  }
  bool shouldShow = true;
  for(int i = 0; i < NPots; i++)
  {
    if(potMoving[i])
    {
      shouldShow = false;
    }
  }
  if(shouldShow)
  {
    strip.show();
  }
}

// BUTTONS
void buttons() {

  for (int i = 0; i < NButtons; i++) {

    buttonCState[i] = digitalRead(buttonPin[i]);  // read pins from arduino

    if ((millis() - lastDebounceTime[i]) > debounceDelay) {

      if (buttonPState[i] != buttonCState[i]) {
        lastDebounceTime[i] = millis();

        if (buttonCState[i] == LOW) {

          // Sends the MIDI note ON accordingly to the chosen board
          MIDI.sendNoteOn(note + i, 127, midiCh); // note, velocity, channel
          uint16_t noteColor = map(note + i, 36, 97, 0, 65535);
          uint32_t rgbcolor = strip.ColorHSV(noteColor, 123, 123);
          pixelColor[0] = rgbcolor;
          pixelOn[0] = true;
        }
        else {

          // Sends the MIDI note OFF accordingly to the chosen board

          MIDI.sendNoteOn(note + i, 0, midiCh); // note, velocity, channel
          
        }
        buttonPState[i] = buttonCState[i];
      }
    }
  }
}


// POTENTIOMETERS
void potentiometers() {


  for (int i = 0; i < NPots; i++) { // Loops through all the potentiometers

    potCState[i] = analogRead(potPin[i]); // reads the pins from arduino

    midiCState[i] = map(potCState[i], 0, 1023, 0, 127); // Maps the reading of the potCState to a value usable in midi

    uint16_t noteColor = map(potCState[i], 0, 1023, 0, 65535);
    uint32_t rgbcolor = strip.ColorHSV(noteColor, 123, 123);
    if(i == 0)
    {
      if(potCState[0] >= 0 && potCState[0] < 204)
      {
        if(!(octavePotPastState >= 0 && octavePotPastState < 204))
        {
          MIDI.sendControlChange(123,0,midiCh);
        }
        note = 36;
      }
      if(potCState[0] >= 204 && potCState[0] < 408)
      {
        if(!(octavePotPastState >= 204 && octavePotPastState < 408))
        {
          MIDI.sendControlChange(123,0,midiCh);
        }
        note = 48;
      }
      if(potCState[0] >= 408 && potCState[0] < 612)
      {
        if(!(octavePotPastState >= 408 && octavePotPastState < 612))
        {
          MIDI.sendControlChange(123,0,midiCh);
        }
        note = 60;
      }
      if(potCState[0] >= 612 && potCState[0] < 816)
      {
        if(!(octavePotPastState >= 612 && octavePotPastState < 816))
        {
          MIDI.sendControlChange(123,0,midiCh);
        }
        note = 72;
      }
      if(potCState[0] >= 816 && potCState[0] <= 1023)
      {
        if(!(octavePotPastState >= 816 && octavePotPastState <= 1023))
        {
          MIDI.sendControlChange(123,0,midiCh);
        }
        note = 84;
      }
      octavePotPastState = potCState[0];
    } else {
      potVar = abs(potCState[i] - potPState[i]); // Calculates the absolute value between the difference between the current and previous state of the pot

      if (potVar > varThreshold) { // Opens the gate if the potentiometer variation is greater than the threshold
        PTime[i] = millis(); // Stores the previous time
      }

      timer[i] = millis() - PTime[i]; // Resets the timer 11000 - 11000 = 0ms

      if (timer[i] < TIMEOUT) { // If the timer is less than the maximum allowed time it means that the potentiometer is still moving
       potMoving[i] = true;
      }
      else {
       potMoving[i] = false;
      }

      if (potMoving[i] == true) { // If the potentiometer is still moving, send the change control
        if (midiPState[i] != midiCState[i]) {

         // Sends the MIDI CC 
         MIDI.sendControlChange(cc + i, midiCState[i], midiCh); // cc number, cc value, midi channel
            

         potPState[i] = potCState[i]; // Stores the current reading of the potentiometer to compare with the next
         midiPState[i] = midiCState[i];
       }
     strip.setBrightness(20);
     strip.fill(rgbcolor, 0, noPixels);
     strip.show();
     }
    }
  }
}
