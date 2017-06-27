#include "Arduino.h"
#include "pot.h"

Pot::Pot(int _udPin, int _incPin, int _taps) {
  udPin = _udPin;
  incPin = _incPin;
  taps = _taps;

  pinMode(udPin, OUTPUT);
  pinMode(incPin, OUTPUT);
  
  forceOff();
}

void Pot::forceOff() {
  digitalWrite(udPin, LOW);

  for (int i = 0; i < taps; i++) {
    digitalWrite(incPin, HIGH);
    digitalWrite(incPin, LOW);
  }

  value = 0;
}

void Pot::setValue(int _targetValue) {
  const int targetValue = constrain(_targetValue, 0, taps);
  const int currentValue = value; // totally unnecessary, just for me to keep track
  
  if (targetValue == currentValue) {
    return;
  }
  else if (targetValue > currentValue) {
    digitalWrite(udPin, HIGH);
  }
  else if (targetValue < currentValue) {
    digitalWrite(udPin, LOW);
  }

  for (int val = 0; val < abs(targetValue - currentValue); val++) {
    digitalWrite(incPin, HIGH);
    digitalWrite(incPin, LOW);
  }

  value = targetValue;
}

void Pot::setPercent(double targetPercent) {
  setValue(round((double)taps * targetPercent));
}

int Pot::getValue() {
  return value;
}

int Pot::getTaps() {
  return taps;
}

void Pot::on() {
  setValue(taps);
}

void Pot::off() {
  setValue(0);
}
