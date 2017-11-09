/*----------------------------------------------------------------------------*/
/*------------------------------------ TIMER ---------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------           DO NOT EDIT DO NOT ALTER DO NOT EDIT         ----------*/
/*----------------------------------------------------------------------------*/

#include "Timer.h"



//DEFAULT CONSTRUCTOR
Timer::Timer() {};

// 1- ARG CONSTRUCTOR
Timer::Timer(int t_interval) {
  interval = t_interval;
}

void Timer::startUpTimer() {
  startTime = millis();
  timePassed = 0;
  //Serial.println(startTime);
}

void Timer:: updateTimer() {
  timePassed = millis() - startTime;
  //Serial.println(timePassed);
}

// general function to check if we have passed the first interval
boolean Timer:: passedInterval() {
  if (timePassed > interval) {
    startTime = millis();
    timePassed = 0;

    return ISTRUE;
  }
  return ISFALSE;
}
