#include <Arduino.h>
#include <MIDI.h>
#include "SRManager.h"
MIDI_CREATE_DEFAULT_INSTANCE();
 
SRManager shiftManager;


/////////////////////////////////////////////
// midi
byte midiCh = 1;
byte note = 36;
byte cc = 1;

void handleControlChange(byte channel, byte number, byte value);

void setup() {
  shiftManager.begin();
  Serial.begin(31250); // 115200 for hairless - 31250 for MOCO lufa
  
  MIDI.turnThruOff();
  MIDI.setHandleControlChange(handleControlChange);

}

void loop() {
  MIDI.read();
}

void handleControlChange(byte channel, byte number, byte value) {
  if(channel == 2 && number == 0){
    shiftManager.setLevel(value);
  }
}