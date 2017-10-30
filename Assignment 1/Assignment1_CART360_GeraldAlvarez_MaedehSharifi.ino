//http://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
#include <toneAC.h>

//pressure sensors pins
#define BELLY_PIN A0
#define ARMRIGHT_PIN A1
#define ARMLEFT_PIN A2

//motion range sensor pins
#define TRIGGER_MOTION_PIN 13
#define ECCHO_MOTION_PIN 12


//buzzer pin
#define BUZZER_PIN 3


//number of running sample
const int RUNNING_SAMPLE = 10;

//Running average for distance motion
int averageDistanceArray [RUNNING_SAMPLE];
//distance array counter
int distanceCtr = 0;
//close range threshold by cm
int closeDistance = 50;
//max range threshhold by cm
int maxDistance = 120;
//var for previous distance for motion sensor
int prevDistance = 0;


//previous pressure value
int prevBellyPressure = 0;

//previous pressure value
int prevLeftPressure = 0;

//previous pressure value
int prevRightPressure = 0;

//freq range
int minBellyHz = 261;
int maxBellyHz = 329;

int minLeftHz = 329;
int maxLeftHz = 415;

int minRightHz = 415;
int maxRightHz = 523;

//Array for storing the notes
const int MAX_NOTES = 32;
int notesArray [MAX_NOTES];
int amplitudeArray[MAX_NOTES];
int notesCtr = 0;

//notes duration
//a whole, haft, quarter, eighth, and sixteenth
int durationsArray [] = {3000, 1500, 750, 375, 150};

//timer variables
unsigned long startTime;
const int goalTime = 1000;

//var to keep track of the pleasure meter
int pleasureMeter = 20;
//maximun pleasure
int maxPleasure = 50;
//pleasure's step
int stepPleasure = 1;
//variable for the range of pleasure spots
int lowestPleasure = 350;
int highestPleasure = 650;

//mode of the bear
int mode = 0;


void setup() {
  Serial.begin(9600);
  //set motion sensor
  pinMode(TRIGGER_MOTION_PIN, OUTPUT);
  pinMode(ECCHO_MOTION_PIN, INPUT);
  //pre-fill the arrays

  for (int i = 0; i < RUNNING_SAMPLE; i++) {
    averageDistanceArray[i] = getDistance();
  }

  //start the timer
  resetTimer();
}
void loop() {

  selectMode();
  //dataSensors();

}


//Print the sensors values
void dataSensors() {

  Serial.print("Left");
  Serial.println(getLeftPressure());


  Serial.print("Belly");
  Serial.println(getBellyPressure());


  Serial.print("RIght");
  Serial.println(getRightPressure());
  Serial.println();

  //delay(100);
}


//Mode selector function
void selectMode() {
  if (mode == 0) {
    Serial.println("waiting");
    waiting();
  }
  else if (mode == 1) {
    interactive();
  }
  else if (mode == 2) {
    Serial.println("playback");
    playback();
  }
  else if (mode == 3) {
    Serial.println("sleep");
    sleep();
  }
}


//Waiting Mode, where the object wait for range detection and physical interaction.
void waiting() {

  //sensitivity of movement/noise
  int noiseOffset = 3;

  //check if average distance is within the max distance
  if (getAverageDistance() <= maxDistance ) {

    //check for movement or change in the distance.
    //check if the prevDistance is less than current distance plus noise
    //and if the prevDistance is also greater than current distance plus noise.
    if (prevDistance < getDistance() + noiseOffset &&
        prevDistance > getDistance() - noiseOffset) {
      //Do nothing due to no movement
    } else {
      if (getDistance() >= closeDistance) {
        //store 100hz + current distance
        int freq = 100 + getDistance();
        //play tone with 10 amplitude and 200 ms duration
        toneAC(freq, 10 , 200);
      }
      else {
        //turn off the tone
        toneAC();
      }
    }

    //check if average distance is within closeDistance
    if (getAverageDistance() <= closeDistance) {
      //check if the value of the pressure is greater than the threshold
      if (getBellyPressure() > 512 ) {
        //play a tone according to the pressure's value
        toneAC(getBellyPressure());
        Serial.println("Next Mode - Interactive");
        //next mode
        mode = 1;
        //start the timer
        resetTimer();
      }

      //check if the value of the pressure is greater than the threshold
      if (getLeftPressure() > 512 ) {
        Serial.println("Next Mode - Interactive");
        //play a tone according to the pressure's value
        toneAC(getLeftPressure());
        //next mode
        mode = 1;
        //start the timer
        resetTimer();
      }

      //check if the value of the pressure is greater than the threshold
      if (getRightPressure() > 512 ) {
        //play a tone according to the pressure's value
        toneAC(getRightPressure());
        Serial.println("Next Mode - Interactive");
        //next mode
        mode = 1;
        //start the timer
        resetTimer();
      }
    }
  }
}

//interactive mode where the user physically interacts with the object.
void interactive() {

  //variable for filtering noise value
  int noiseOffset = 3;

  //placeholder for a frequency
  int freq = 0;

  //placeholder for an amplitude
  int amp = 0;

  //check if the pleasure meter is within 0 to 100
  if (pleasureMeter < maxPleasure && pleasureMeter > 0) {

    //CHECK THE RIGHT ARM SENSOR
    //cut off noise by checking if the previous value of pressure sensor is around the range of the current value
    //also ensure that the user inputs different pressure values
    if (prevRightPressure <= getRightPressure() + noiseOffset &&
        prevRightPressure >= getRightPressure() - noiseOffset ) {

      //do nothing due to the value is within range of noise filter
      //prevent accidental or noise input

    } else {
      //else: the current value of the sensor exceed the noise; thus, indicating a spike change of the value

      //check if the average right arm value is within the pleasure's range
      if (lowestPleasure < getRightPressure()
          && highestPleasure > getRightPressure()) {

        //set the frequency by invoking the getOffsetFrequency
        freq = getOffsetFrequency(getRightPressure(), maxRightHz, minRightHz);

        //set the amplitude
        amp = getAmplitude(getRightPressure(), highestPleasure);

        //update the array
        updateNotesArray(freq, amp);


        toneAC(freq, 10, 100);
        //increment the pleasure meter
        pleasureMeter += stepPleasure;


      } else {

        if (getRightPressure() < lowestPleasure) {
          toneAC(2000, 10, 100);
          Serial.println("To strong");
        }
        if (getRightPressure() > highestPleasure) {
          toneAC(100, 10, 100);
          Serial.println("To weak");
        }
        //running timer that checks if timer passes the setGoal
        if (getTimePassed() >= goalTime) {
          //decrease pleasure meter
          pleasureMeter -= stepPleasure;
          //reset timer
          resetTimer();
        }

      }
    }



    //CHECK THE LEFT ARM SENSOR
    //cut off noise by checking if the previous value of pressure sensor is around the range of the current value
    //also ensure that the user inputs different pressure values
    if (prevLeftPressure <= getLeftPressure() + noiseOffset &&
        prevLeftPressure >= getLeftPressure() - noiseOffset ) {
      //do nothing due to the value is within range of noise filter
      //prevent accidental or noise input
    } else {
      //else: the current value of the sensor exceed the noise; thus, indicating a spike change of the value
      //check if the average right arm value is within the pleasure's range
      if (lowestPleasure < getLeftPressure()
          && highestPleasure > getLeftPressure()) {


        //set the frequency by invoking the getOffsetFrequency
        freq = getOffsetFrequency(getLeftPressure(), maxRightHz, minRightHz);

        //set the amplitude
        amp = getAmplitude(getRightPressure(), highestPleasure);

        //update note array
        updateNotesArray(freq, amp);

        Serial.println("ON POINT");
        toneAC(freq, 10, 100);
        //increment the pleasure meter
        pleasureMeter +=  stepPleasure;


      } else {

        if (getLeftPressure() < lowestPleasure) {
          toneAC(2000, 10, 100);
          Serial.println("To strong");
        }
        if (getLeftPressure() > highestPleasure) {
          toneAC(100, 10, 100);
          Serial.println("To weak");
        }

        //running timer that checks if timer passes the setGoal
        if (getTimePassed() >= goalTime) {
          //decrease pleasure meter
          pleasureMeter -= stepPleasure;
          //reset timer
          resetTimer();
        }

      }
    }


    //CHECK THE LEFT ARM SENSOR
    //cut off noise by checking if the previous value of pressure sensor is around the range of the current value
    //also ensure that the user inputs different pressure values
    if (prevBellyPressure <= getBellyPressure() + noiseOffset &&
        prevBellyPressure >= getBellyPressure() - noiseOffset ) {
      //do nothing due to the value is within range of noise filter
      //prevent accidental or noise input
    } else {
      //else: the current value of the sensor exceed the noise; thus, indicating a spike change of the value
      //check if the average right arm value is within the pleasure's range
      if (lowestPleasure < getBellyPressure()
          && highestPleasure > getBellyPressure()) {


        //set the frequency by invoking the getOffsetFrequency
        freq = getOffsetFrequency(getBellyPressure(), maxRightHz, minRightHz);

        //set the amplitude
        amp = getAmplitude(getRightPressure(), highestPleasure);

        //update the note array
        updateNotesArray(freq, amp);

        //play the tone
        toneAC(freq, 10, 100);
        //increment the pleasure meter
        pleasureMeter += stepPleasure;


      } else {

        if (getBellyPressure() < lowestPleasure) {
          toneAC(2000, 10, 100);
          Serial.println("To strong");
        }
        if (getBellyPressure() > highestPleasure) {
          toneAC(100, 10, 100);
          Serial.println("To weak");
        }

        //running timer that checks if timer passes the setGoal
        if (getTimePassed() >= goalTime) {
          //decrease pleasure meter
          pleasureMeter -= stepPleasure;
          //reset timer
          resetTimer();
        }
      }
    }

  } else {
    //check if the pleasureMeter is max
    if (pleasureMeter >= maxPleasure) {
      //next mode
      mode = 2;
    }
    //check if the pleasure when down
    if (pleasureMeter <= 0) {
      //jump to sleep mode
      mode = 3;
      Serial.println("GameOver");
    }
    //reset the notes counter
    notesCtr = 0;
    //reset timer
    resetTimer();
  }

  //turn off tone
  toneAC();

  Serial.print("PleasureMeter");
  Serial.println(pleasureMeter);

  delay(100);

}
void playback() {
  if (notesCtr < MAX_NOTES) {
    int randomNum = random(5);
    toneAC(notesArray[notesCtr], 10, durationsArray[randomNum]);//make the musical notes
    notesCtr++;
  } else {
    mode = 3;
  }
}

//sleep mode function that delay the mode loop for a certain time
void sleep() {

  int snoreFreq = 0;
  int durationSleep = 0;

  if (pleasureMeter >= 100) {
    snoreFreq = 100;
    durationSleep = 5000;
  } else {
    if (pleasureMeter <= 0) {
      snoreFreq = 1000;
      durationSleep = 10000;
    }
  }

  //if time passed the duration sleep
  if (getTimePassed() >= durationSleep) {
    //if the distance is greter than max distance
    //no one interacting it
    if (getAverageDistance() > maxDistance)
      //switch mode
      mode = 0;
  } else {
    //play the tone message
    toneAC(snoreFreq);
    //delay for tone to play
    delay(1);
  }

  //reset the pleasure meter
  int pleasureMeter = 20;

}

//Resets the timer.
void resetTimer()
{
  //assign the current time (millis()) to startTime var; hence, resetting the timer's starting time.
  startTime = millis();
}

//Getter function that returns the time passed.
long getTimePassed()
{
  //return running time millis minus the startTime
  return  millis() - startTime;

}

//sote the note and amplitude in the array
void updateNotesArray(int freq, int amp) {

  //check if the counter is less than the max note
  if (notesCtr < MAX_NOTES) {

    //assign the frequency given in the function parameter
    notesArray[notesCtr] = freq;

    //assign the amp to the amplitudeArray
    amplitudeArray[notesCtr] = amp;

    //increament counter
    notesCtr++;
  } else {

    //reset counter
    notesCtr = 0;
  }
}


//calculate the offset frequency needed in ration with maxHz and minHz
int getOffsetFrequency(int senAvgVal, int maxVal, int minVal) {

  //offset frequency
  int offsetHz = 0;

  //restrict distance to closeDistance
  if (getDistance() <=  closeDistance) {
    //calculate an offset frequency in ratio to minVal to maxVal accoding to the distance
    offsetHz = (getDistance() / closeDistance) * maxVal - minVal;
  }

  //return the average pressure val + offset
  return senAvgVal + offsetHz;
}

//map the amplidtude according to the pressure sensor's value and scale it to the min hz and max hz of each pressure's hz setting
int getAmplitude(int senVal, int maxVal) {
  //check if the senVal is greater than maxVal
  //ensure not give higher than 10
  if (senVal > maxVal) {
    return 10;
  }
  else {
    //return the scaled  pressure val in the range of 5 10
    return map(senVal, 0, maxVal, 0, 10);
  }
}

//Getter function that reads the belly section pressure sensor.
int getBellyPressure() {
  return analogRead(BELLY_PIN);
}


//Getter function that reads the left arm section pressure sensor.
int getLeftPressure() {
  return analogRead(ARMLEFT_PIN);
}


//Getter function that reads the right arm section pressure sensor.
int getRightPressure() {
  return analogRead(ARMRIGHT_PIN);
}



//Getter function that triggers pulse and receives distance of the motion sensor
int getDistance() {
  //local var for distance and duration
  long distance, duration;
  //clear trigger
  digitalWrite(TRIGGER_MOTION_PIN, LOW);
  //delay
  delayMicroseconds(2);
  //set the trigger High for 10 micro seconds
  digitalWrite(TRIGGER_MOTION_PIN, HIGH);
  //delay
  delayMicroseconds(10);
  //tigger the pulse
  digitalWrite(TRIGGER_MOTION_PIN, LOW);
  //getting the duration| receiving the eccho
  duration = pulseIn(ECCHO_MOTION_PIN, HIGH);
  //calculating distance in CM and make sure it is positive
  distance = abs(duration * 0.034 / 2);

  //saving the raw current distance for prevDistance
  prevDistance = distance;

  //weight filtering
  int currEst = 0.5 * distance + 0.5 * prevDistance;

  return  currEst;
}


//Function that calculates the average distance of the received distance. Serve to filter noise
int getAverageDistance() {
  int totalAverage = 0;
  if (distanceCtr < RUNNING_SAMPLE) {
    averageDistanceArray[distanceCtr] = getDistance();
    distanceCtr++;
  } else {
    distanceCtr = 0;
  }
  for (int i = 0; i < RUNNING_SAMPLE; i++) {
    totalAverage += averageDistanceArray[i];
  }
  return totalAverage / RUNNING_SAMPLE;
}

