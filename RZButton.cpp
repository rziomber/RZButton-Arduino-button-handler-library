#include "RZButton.h"

RZButton::RZButton(uint8_t _buttonPin, int _pull_mode) {
	buttonPin = _buttonPin;
	mode = _pull_mode;
	lastStatus = 0;
	lastChange = 0;
	firstPress = 0;
	lastPress = 0;
	multiclickCounter = 0;
	pinMode(buttonPin, mode);
}

bool RZButton::isPressed() {
	if (mode == INPUT_PULLUP) {
		return !digitalRead(buttonPin);
	} else {
		return digitalRead(buttonPin);
	}
}

bool RZButton::wasPressed() {
	return lastStatus;
}

bool RZButton::stateChanged() {
	bool currentStatus = isPressed();
	if (currentStatus != lastStatus && millis() - lastChange > 15) {
		lastStatus = currentStatus;
		lastChange = millis();
		return 1;
	}

	return 0;
}

bool RZButton::uniquePress() {
	return stateChanged() && lastStatus;
}

bool RZButton::uniqueRelease(){
	return stateChanged() && !lastStatus;
}

bool RZButton::longPress() {
	bool currentStatus = isPressed();
	if (currentStatus && firstPress == 0)
		firstPress = millis();
	if (!currentStatus && firstPress != 0 && millis() - firstPress > longPressTimeThreshold) {
		firstPress = lastPress = multiclickCounter = 0;
		return 1;
	}
	if (!currentStatus) firstPress = 0;
	return 0;
}

unsigned char RZButton::multiclick() {
	unsigned char returnThis = 0;
	if (uniquePress()) {
		lastPress = millis();
		multiclickCounter++;
	}
	if (multiclickCounter != 0 && lastPress != 0 && millis() - lastPress > multiclickTimeThreshold && !wasPressed() && firstPress == 0) {
		returnThis = multiclickCounter;
		lastPress = multiclickCounter = 0;
	}
	return returnThis;
}

unsigned long RZButton::continuousPressTime() {
  if (isPressed()) {
    if (firstPress == 0) {
      firstPress = millis();
    }
    return millis() - firstPress;
  } else {
    firstPress = 0;
  }
  return 0;
}

void RZButton::clearFirstPress() {
	firstPress = multiclickCounter = 0;
}

void RZButton::setMulticlickTimeThreshold(unsigned int time_threshold_milliseconds){
	multiclickTimeThreshold = time_threshold_milliseconds;
}
void RZButton::setLongPressTimeThreshold(unsigned int time_threshold_milliseconds){
	longPressTimeThreshold = time_threshold_milliseconds;
}
