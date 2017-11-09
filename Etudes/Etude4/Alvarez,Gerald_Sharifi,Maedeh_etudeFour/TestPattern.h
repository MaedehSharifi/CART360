/*----------------------------------------------------------------------------*/
/*-------------------------------- TEST PATTERN ------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------           DO NOT EDIT DO NOT ALTER DO NOT EDIT         ----------*/
/*----------------------------------------------------------------------------*/

#ifndef TESTPATTERN_H_
#define TESTPATTERN_H_

//#include <stdio.h>
//#include <stdlib.h>
#include <Arduino.h>
#include "Constants.h"



#define MAX_PATTERNS 16
//constant for max number of notes in array
#define MAX_NOTES 16

struct patternObj {
      int data;               // will store information
      int notes[MAX_NOTES];
      int durations[MAX_NOTES];
      int pauses[MAX_NOTES];
      int countNotes;
};

const struct patternObj * retrievePattern(int index);
const int * retrievePatternNotes(int index);
const int * retrievePatternDurations(int index);
const int * retrievePatternPauses(int index); 
void addPattern(const int * cNotes, const int * cDurations ,const int * cPauses, int countN);
int patternListIsEmpty();
int isValidIndex(int index);
int getNumberPatterns();
int getNumberNotesOfPattern(int index);

#endif /* TESTPATTERN_H_ */
