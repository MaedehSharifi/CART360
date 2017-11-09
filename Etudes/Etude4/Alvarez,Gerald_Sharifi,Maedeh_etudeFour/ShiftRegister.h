/*----------------------------------------------------------------------------*/
/*------------------------------ SHIFT REGISTER ------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------      IMPLEMENT THE SHIFT REGISTER FUNCTIONALITY        ----------*/
/*----------          ******** ATTRIBUTE YOUR CODE ********         ----------*/
/*----------------------------------------------------------------------------*/

#ifndef SHIFTREGISTER_H_
#define SHIFTREGISTER_H_

#include "Constants.h"



/* SHIFT REGISTER IC PIN OUTS
        __
  Q1 -|    |- VCC
  Q2 -|    |- Q0
  Q3 -|    |- DS
  Q4 -|    |- OE
  Q5 -|    |- ST_CP
  Q6 -|    |- SH_CP
  Q7 -|    |- MR
 GND -| __ |- Q'

  Key:
  Q0 - Q7: Parallel Out Pins
  Q': Cascade Pin
  DS: Serial Data In Pin
  OE: Output Enable (GND)
  ST_CP: Latch Pin
  SH_CP: Clock Pin
  MR: Master Reset (VCC)
*/

/* PINS FOR SHIFT REG */
// ST_CP of 74HC595
#define LATCH_PIN 6
// SH_CP of 74HC595
#define CLOCK_PIN 8
// DS of 74HC595
#define DATA_PIN 7

/* CONSTANT FOR EMPTY*/
#define EMPTY B01111111

/* DEFINE AND INITIALIZE THE ARRAY WITH THE NECESSARY VALUES */
// Hex Character from 0 - F
byte hexArray[16] =
{
  // you have to implement the necessary values for each element
B10000000,//0
  B10011110,//1
  B01001000,//2
  B01100000,//3
  B00110010,//4
  B00100100,//5
  B00000100,//6
  B10110000,//7
  B00000000,//8
  B00100000,//9
  B00010000,//a
  B00000110,//b
  B10001100,//c
  B01000010,//d
  B00001100,//e
  B00011100,//f
};

void setupShiftRegister() {
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
}

/******************sendToShiftRegister *******************************
TODO:: IMPLEMENT THE FUNCTIONALITY TO SEND THE CORRECT DATA TO
SHIFT REG - BASED ON THE POT VAL
********************************************************************/
void sendToShiftRegister(int pot)
{
  // IMPLEMENT
  //close latch pin
  digitalWrite(LATCH_PIN, LOW);

  //shift out data using least significant first
  shiftOut(DATA_PIN, CLOCK_PIN,  MSBFIRST, hexArray[pot]);

  //open latch|serial
  digitalWrite(LATCH_PIN, HIGH);

}


//funtion to make the 7 segment display blink
void blinkSevenSegmentDisplay() {
  //close the latch
  digitalWrite(LATCH_PIN, LOW);

  //shift out data using least significant first | display empty
  shiftOut(DATA_PIN, CLOCK_PIN,  MSBFIRST, EMPTY);

  //open latch|serial
  digitalWrite(LATCH_PIN, HIGH);

  //delay for the dot 7-segment display
  delay(DURATION);

  digitalWrite(LATCH_PIN, LOW);

  //shift out data using least significant first | display empty
  shiftOut(DATA_PIN, CLOCK_PIN,  MSBFIRST, B11111111);

  //open latch|serial
  digitalWrite(LATCH_PIN, HIGH);

  //delay for the complete turn off 7-segment display
  delay(DURATION);

}

//function that turn off the 7-segment led light
void turnOffSevenSegmentDisplay() {
  //close latch
  digitalWrite(LATCH_PIN, LOW);
  //shift out data using least significant first | display empty
  shiftOut(DATA_PIN, CLOCK_PIN,  MSBFIRST, B11111111);
  //open latch|serial
  digitalWrite(LATCH_PIN, HIGH);
}

/******************READ FROM POT*********************************
TO DO:: GET VALUE FROM POT AND ENSURE THE VALUE RETURNED IS A VALID VALUE
********************************************************************/
int getAnalog() {

  //IMPLEMENT
  //place holder for pot value
  int potVal = analogRead(POT_PIN);

  //verify if the value in within the analog range
  if (potVal >= 0 && potVal <= 1023) {
    //return a mapped value to 0 - 16
    return potVal / (1023 / 16);
  } else {
    //return 0
    return 0;
  }

}

#endif /* SHIFTREGISTER_H_ */
