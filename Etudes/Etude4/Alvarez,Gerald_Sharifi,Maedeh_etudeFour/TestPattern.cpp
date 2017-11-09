/*----------------------------------------------------------------------------*/
/*-------------------------------- TEST PATTERN ------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------           DO NOT EDIT DO NOT ALTER DO NOT EDIT         ----------*/
/*----------------------------------------------------------------------------*/

#include "TestPattern.h"


int numberPatterns = 0;
struct patternObj * patterns [MAX_PATTERNS];

const int * retrievePatternNotes( int index) {
  const struct  patternObj * p = retrievePattern(index);
  return p->notes;
}

const int * retrievePatternDurations(int index ) {
  const struct  patternObj * p = retrievePattern(index);
  return p->durations;
}

const int * retrievePatternPauses(int index ) {
  const struct  patternObj * p = retrievePattern(index);
  return p->pauses;
}
const struct patternObj * retrievePattern(int index) {

  return patterns[index];
}

int patternListIsEmpty() {
  if (numberPatterns == 0)
  {
    return ISTRUE;
  }
  return ISFALSE;
}

int isValidIndex(int index) {
  if (index >= numberPatterns)
  {
    return ISFALSE;
  }
  return ISTRUE;
}

void addDataToPatternObj(const int * cNotes, const int * cDurations, const int * cPauses, struct patternObj* p) {
  for (int i = 0; i < p->countNotes; i++) {
    p ->notes[i] = cNotes[i];
    p ->durations[i] = cDurations[i];
    p ->pauses[i] = cPauses[i];
  }
}

void addPattern(const int * cNotes, const int * cDurations, const int * cPauses, int numberNotes) {

  if (numberPatterns < MAX_PATTERNS) {
    patterns [numberPatterns] =  malloc(sizeof(struct patternObj)) ;
    patterns [numberPatterns]->countNotes = numberNotes;
    addDataToPatternObj(cNotes, cDurations, cPauses, patterns[numberPatterns]);
    numberPatterns++;
  }
}

int getNumberPatterns() {
  return numberPatterns;
}

int getNumberNotesOfPattern(int index) {
  const struct  patternObj * p = retrievePattern(index);
  return p->countNotes;
}









