/*----------------------------------------------------------------------------*/
/*--------------------------------- CONSTANTS --------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------           DO NOT EDIT DO NOT ALTER DO NOT EDIT         ----------*/
/*----------------------------------------------------------------------------*/

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#define ISTRUE  1
#define ISFALSE 0

#define BUTTON_MODE_PIN  2
#define BUTTON_STORE_PIN 3

// constants for RGB LED
#define LED_PIN_R 11 // R PIN
#define LED_PIN_G 10 // G PIN
#define LED_PIN_B 9  // B PIN

// a constant for duration
#define DURATION 250

// constant for pin to output for buzzer
#define BUZZER_PIN 5 // PWM

// constant for input from photo cell
#define PHOTO_PIN A0
// constant for input from potentiometer
#define POT_PIN A1
// constant for note in (button-resistor ladder on breadboard)
# define NOTE_IN_PIN A2

// constant for size of running samples array (for averging)
#define RUNNING_SAMPLES 16

// max pressing time
#define MAX_PRESS_TIME 5000

#endif /* CONSTANTS_H_ */
