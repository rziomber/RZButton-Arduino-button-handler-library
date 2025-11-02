#ifndef RZButton_h
#define RZButton_h
#include "Arduino.h"

class RZButton
{
public:
  RZButton(uint8_t _buttonPin, int _pull_mode = INPUT_PULLUP);
  bool isPressed();
  bool wasPressed();
  bool stateChanged();
  bool uniquePress();
  bool uniqueRelease();
  bool longPress();
  unsigned char multiclick();
  unsigned long continuousPressTime();
  void clearFirstPress();
  void setMulticlickTimeThreshold(unsigned int time_threshold_milliseconds);
  void setLongPressTimeThreshold(unsigned int time_threshold_milliseconds);

private:
  uint8_t buttonPin;
  bool lastStatus;
  int mode;
  unsigned long lastChange, firstPress, lastPress;
  unsigned char multiclickCounter;
  unsigned int multiclickTimeThreshold = 3000;
  unsigned int longPressTimeThreshold = 2000;
};

#endif
