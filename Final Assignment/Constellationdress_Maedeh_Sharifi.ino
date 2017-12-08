/* Start of Code */

#include <Wire.h> //library for magnetometer

#define NUM_LEDS 8 // Number of constellations
#define DATA_PIN_X 2 // Pin 2 connected to RGB X
#define DATA_PIN_Y 3 // Pin 3 connected to RGB Y

// declare DS, STCP, and SHCP pin as numbers for the shift register
#define DS_pin 8
#define STCP_pin 9
#define SHCP_pin 10
#define lightSensor_pin A3

/* The I2C address of the module */
#define HMC5803L_Address 0x1E

/* Register address for the X Y and Z data of the magnetometer*/
#define X 3
#define Y 7
#define Z 5

boolean registers[8]; // array defined for the shift register. default values = false ( = 0 )
int time1 = 50;       // set delay time
int blinking=0;       // on and off variable of the LED (0= off, 1= on) 

//a subroutine that writes the values of the array registers[8] to the shift register
void writeReg() {
  digitalWrite(STCP_pin, LOW);      

  for (int i=7; i>=0; i--) // An array, register[8] for example, has 8 indexes noted as 0-7
  {
  digitalWrite(SHCP_pin, LOW); 
  digitalWrite(DS_pin, registers[i]);
  digitalWrite(SHCP_pin, HIGH); 
  }
  digitalWrite(STCP_pin, HIGH);   
}

void setup() 
{
  //define shift register pins
  pinMode(DS_pin, OUTPUT);
  pinMode(STCP_pin, OUTPUT);
  pinMode(SHCP_pin, OUTPUT);

  writeReg(); // write the default set of registers[] to DS_pin, one by one
    
  Serial.begin(9600); //serial data transfer rate
  Wire.begin(); //Initiate the Wire library

/* Initialise the module of the magnetometer */ 
   Init_HMC5803L();
}

void loop() 
{
/* Read each sensor axis data and output to the serial port */
//Serial.print(HMC5803L_Read(X));
//Serial.print(" ");
//Serial.print(HMC5803L_Read(Y));
//Serial.print(" ");
//Serial.println(HMC5803L_Read(Z));

//define the state of the LEDs
//lightstate1 determines the state of light outside (low = dark, high = bright)
//lightstate2 determined the state of the LEDs on the dress with respect to the outside light. 
boolean lightstate1, lightstate2; 
int outsidelight=analogRead(lightSensor_pin); //read the amount of light outside
Serial.println(outsidelight); //monitoring the value of light outside
//if it is dark outside
if (outsidelight < 30){ 
  lightstate1=LOW; 
  lightstate2=HIGH; //dress LEDs light up
}
else{
  lightstate1=LOW;
  lightstate2=LOW; //dress LEDs off
}


int xvalue = HMC5803L_Read(X); //reads magnetometer value
//maps the blinking of LEDs on the dress with repect to the magnetomer inclination
//scales -500 to 500 value to 0 to 7 (NUM_LEDS-1)
//LedsToLight presents the Leds poiting a given direction
int LedsToLight = map(xvalue, -500, 500, 0, NUM_LEDS-1); 

//produce the blinking of the LEDs
//blinking value changes from 0 to 1 or 1 to 0 (on and off)
if (blinking==0) 
    blinking=1;
  else
    blinking=0;

//completing the shift register array
for(int led = 0; led <NUM_LEDS; led++) { 
  //initialise register value with the variable inside lightstate2 (with repect to the outside light)
  registers[led]=lightstate2; 
  //blinking LEDs towards a given direction
  if(blinking==1)if(led == LedsToLight) registers[led]=lightstate1;
  //state of light of the LED which is adjacent to the blinking LED (it blinks at a different rate)
  if(led == LedsToLight-1) registers[led]=lightstate1;
}
//writing values to the shift register
writeReg();
  delay(50); //rate of blinking LED in a given direction
  for(int led = 0; led <NUM_LEDS; led++) { 
  //initialise register value with the variable inside lightstate2 (with repect to the outside light)
  registers[led]=lightstate2;
  //blinking LEDs towards a given direction
  if(blinking==1)if(led == LedsToLight) registers[led]=lightstate1;
  //state of light of the LED which is adjacent to the blinking LED (it blinks at a different rate)
  if(led == LedsToLight+1) registers[led]=lightstate1;
}

//writing values to the shift register
writeReg();
delay(time1); //rate of blinking LED in a given direction
}

/* This function will initialise the module and only needs to be run once
after the module is first powered up or reset */
void Init_HMC5803L(void)
{
/* Set the module to 8x averaging and 15Hz measurement rate */
Wire.beginTransmission(HMC5803L_Address);
Wire.write(0x00);
Wire.write(0x70);

/* Set a gain of 5 */
Wire.write(0x01);
Wire.write(0xA0);
Wire.endTransmission();
}

/* This function will read once from one of the 3 axis data registers
and return the 16 bit signed result. */
int HMC5803L_Read(byte Axis)
{
int Result;

/* Initiate a single measurement */
Wire.beginTransmission(HMC5803L_Address);
Wire.write(0x02);
Wire.write(0x01);
Wire.endTransmission();
delay(6);

/* Move modules the resiger pointer to one of the axis data registers */
Wire.beginTransmission(HMC5803L_Address);
Wire.write(Axis);
Wire.endTransmission();

/* Read the data from registers (there are two 8 bit registers for each axis) */ 
Wire.requestFrom(HMC5803L_Address, 2);
Result = Wire.read() << 8;
Result |= Wire.read();

return Result;
}

/* End of Code */
