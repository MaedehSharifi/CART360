/*----------------------------------------------------------------------------*/
/*------------------------------------ TIMER ---------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------           DO NOT EDIT DO NOT ALTER DO NOT EDIT         ----------*/
/*----------------------------------------------------------------------------*/

#ifndef TIMER_H_
#define TIMER_H_

#include <Arduino.h>
#include "Constants.h"


class Timer
{
  private:
    unsigned long startTime;
    unsigned long timePassed;
    unsigned int interval;

  public:
    Timer();
    Timer(int t_interval);
    void startUpTimer();
    // general function to update the time passed
    void updateTimer();

    // general function to check if we have passed the first interval
    boolean passedInterval();
    unsigned long getTimePassed(){return timePassed;}
    void setTimePassed(unsigned long n){timePassed =n;}
};
#endif /* TIMER_H_ */
