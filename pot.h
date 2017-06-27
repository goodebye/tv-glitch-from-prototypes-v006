/*
  pot.h - short n sweet library for U/D style digital potentiometers
  created by goode bye, 2016.
  no warranty expressed or implied, please don't use this to accidentally kill yourself, thanks
  all copyrot rejected by the author
*/

#ifndef pot.h
#define pot.h

class Pot {
  public:
    Pot(int _udPin, int _incPin, int _taps);
    void on();
    void off();
    void forceOff();
    int getValue();
    int getTaps();
    void setValue(int _targetValue);
    void setPercent(double targetPercent);
  private:
    int udPin;
    int incPin;
    int value;
    int taps;
};

#endif
