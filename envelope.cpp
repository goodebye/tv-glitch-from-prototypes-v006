#include "Arduino.h"
#include "envelope.h"

Envelope::Envelope(int attackTime, int decayTime, int sustainTime, int releaseTime, double _maxAmplitude, double _sustainAmplitude) {
  currentPhase = OFF;

  phaseTimes[ATTACK] = attackTime;
  phaseTimes[DECAY] = decayTime;
  phaseTimes[SUSTAIN] = sustainTime;
  phaseTimes[RELEASE] = releaseTime;

  maxAmplitude = _maxAmplitude;
  phaseAmplitudes[ATTACK] = _maxAmplitude;
  phaseAmplitudes[DECAY] = _sustainAmplitude;
  phaseAmplitudes[SUSTAIN] = _sustainAmplitude;
  phaseAmplitudes[RELEASE] = 0.0;

  currentAmplitude = 0.0;
  
  currentTime = millis();
  phaseStartTime = millis();
}

void Envelope::update() {
  if (currentPhase != OFF) {
    currentTime = millis();
  
    if (phaseTimeExceeded()) {
      currentAmplitude = phaseAmplitudes[currentPhase];
      nextPhase();
    }

    if (currentPhase == ATTACK) {
      currentAmplitude = ((double)(currentTime - phaseStartTime) / (double)phaseTimes[currentPhase]) * maxAmplitude;
    }
    else if (currentPhase == DECAY) {
      double normalizedAmplitude = (( ((double)(currentTime - phaseStartTime) / (double)phaseTimes[currentPhase])) );
      currentAmplitude = maxAmplitude - (maxAmplitude - phaseAmplitudes[currentPhase]) * normalizedAmplitude; 
    }
    else if (currentPhase == SUSTAIN) {
      // don't really need to do anything here
    }
    else if (currentPhase == RELEASE) {
      double sustainAmp = phaseAmplitudes[currentPhase - 1];
      currentAmplitude = sustainAmp - ((double)(currentTime - phaseStartTime) / (double)phaseTimes[currentPhase]) * sustainAmp;
    }
  }
}

void Envelope::trigger() {
  currentPhase = ATTACK;
  phaseStartTime = millis();
}

double Envelope::getCurrentAmplitude() {
  return currentAmplitude;
}

void Envelope::setTime(env_phase_t phase, int length) {
  phaseTimes[phase] = length;
}

bool Envelope::phaseTimeExceeded() {
  if (currentTime - phaseStartTime >= phaseTimes[currentPhase]) {
    return true;
  }
  return false;
}

void Envelope::nextPhase() {
  currentPhase = currentPhase + 1;
  phaseStartTime = millis();
}

env_phase_t Envelope::getCurrentPhase() {
  return currentPhase;
}
