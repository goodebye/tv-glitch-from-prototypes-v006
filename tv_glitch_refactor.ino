#include <MIDI.h>
#include "pot.h"
#include "envelope.h"

MIDI_CREATE_DEFAULT_INSTANCE();

Pot pot1(2, 3, 100);
Pot pot2(4, 5, 100);
Envelope env1(10, 0, 30, 10, 1, 1);
Envelope env2(10, 0, 30, 10, 1, 1);

boolean learning = true;
int targetDrums = 2;
int numOfDrums = 0;
byte drumNote1 = 71;
byte drumNote2 = 69;

const int debugPin = 6;

void setup() {
  
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  pinMode(debugPin, OUTPUT);

  MIDI.begin();
}

void loop() {
  MIDI.read();
  env1.update();
  env2.update();
  double amp1 = env1.getCurrentAmplitude();
  pot1.setPercent(amp1);
  double amp2 = env2.getCurrentAmplitude();
  pot2.setPercent(amp2);
}

void blinkLoop() {
  pot1.off();
  delay(1000);
  pot1.on();
  delay(500);
}


void handleNoteOn(byte channel, byte pitch, byte velocity) {
    if (pitch == drumNote1) {
      env1.trigger();
    }
    else if (pitch == drumNote2) {
      env2.trigger();
    }
}

void handleNoteOff(byte channel, byte pitch, byte velocity) {

}
