/*----------------------------------------------------------------------------*/
/*--------------------------- INTERRUPT HANDLER ------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------           DO NOT EDIT DO NOT ALTER DO NOT EDIT         ----------*/
/*----------------------------------------------------------------------------*/

#ifndef INTERRUPTHANDLER_H_
#define INTERRUPTHANDLER_H_

#include "Constants.h"



volatile boolean modeChangeInterruptRequest = ISFALSE;
volatile boolean storePatternInterruptRequest = ISFALSE;
boolean storeOnce = ISFALSE;

void storePatternRequest() {
  storePatternInterruptRequest = ISTRUE;
}

void storePatternInterruptReset() {
  storePatternInterruptRequest = ISFALSE;
}

void modeChangeRequest() {
  modeChangeInterruptRequest = ISTRUE;
}

void setupInterruptHandler() {
  pinMode(BUTTON_STORE_PIN, INPUT_PULLUP);
  pinMode(BUTTON_MODE_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_MODE_PIN), modeChangeRequest, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_STORE_PIN), storePatternRequest, FALLING);
  }
#endif /* INTERRUPTHANDLER_H_ */
