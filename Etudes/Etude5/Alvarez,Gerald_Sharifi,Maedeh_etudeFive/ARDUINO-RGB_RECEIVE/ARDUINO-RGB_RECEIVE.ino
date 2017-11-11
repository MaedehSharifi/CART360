#define LED 3
#define COLOR_PIN 6

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
byte incomingByte = 255;
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      8

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, COLOR_PIN, NEO_GRB + NEO_KHZ800);

int r, g, b;
int currentId = 0;

void setup() {
  // initialize the button pin as an input:

  // initialize serial communication:
  Serial.begin(9600);
  pixels.begin(); // This initializes the NeoPixel library.

}


void loop() {
  while (Serial.available() > 0)
  {
    incomingByte = Serial.read(); // read it
    
      if (incomingByte == 'A' ) {
        int colours[3] = {0};
        
        while(currentId < 3) {
          delay(100);
          colours[currentId++] = Serial.read();
          }
        
  
          pixels.setPixelColor(0, pixels.Color(colours[0], colours[1], colours[2])); // Moderately bright green color.
          pixels.show(); // This sends the updated pixel color to the hardware.
          delay(1000);
          pixels.setPixelColor(0, pixels.Color(0, 0, 0));
          pixels.show();
        }

        else if (incomingByte == 'B' ) {
        int colours[3] = {0};
        
        while(currentId < 3) {
          delay(100);
          colours[currentId++] = Serial.read();
          }
        
  
          pixels.setPixelColor(1, pixels.Color(colours[0], colours[1], colours[2])); // Moderately bright green color.
          pixels.show(); // This sends the updated pixel color to the hardware.
          delay(1000);
          pixels.setPixelColor(1, pixels.Color(0, 0, 0));
          pixels.show();
        } 

        else  if (incomingByte == 'C' ) {
        int colours[3] = {0};
        
        while(currentId < 3) {
          delay(100);
          colours[currentId++] = Serial.read();
          }
        
  
          pixels.setPixelColor(2, pixels.Color(colours[0], colours[1], colours[2])); // Moderately bright green color.
          pixels.show(); // This sends the updated pixel color to the hardware.
          delay(1000);
          pixels.setPixelColor(2, pixels.Color(0, 0, 0));
          pixels.show();
        }
        else  if (incomingByte == 'D' ) {
        int colours[3] = {0};
        
        while(currentId < 3) {
          delay(100);
          colours[currentId++] = Serial.read();
          }
        
  
          pixels.setPixelColor(3, pixels.Color(colours[0], colours[1], colours[2])); // Moderately bright green color.
          pixels.show(); // This sends the updated pixel color to the hardware.
          delay(1000);
          pixels.setPixelColor(3, pixels.Color(0, 0, 0));
          pixels.show();
        }
        else  if (incomingByte == 'E' ) {
        int colours[3] = {0};
        
        while(currentId < 3) {
          delay(100);
          colours[currentId++] = Serial.read();
          }
        
  
          pixels.setPixelColor(4, pixels.Color(colours[0], colours[1], colours[2])); // Moderately bright green color.
          pixels.show(); // This sends the updated pixel color to the hardware.
          delay(1000);
          pixels.setPixelColor(4, pixels.Color(0, 0, 0));
          pixels.show();
        }
        else  if (incomingByte == 'F' ) {
        int colours[3] = {0};
        
        while(currentId < 3) {
          delay(100);
          colours[currentId++] = Serial.read();
          }
        
  
          pixels.setPixelColor(5, pixels.Color(colours[0], colours[1], colours[2])); // Moderately bright green color.
          pixels.show(); // This sends the updated pixel color to the hardware.
          delay(1000);
          pixels.setPixelColor(5, pixels.Color(0, 0, 0));
          pixels.show();
        }
        else  if (incomingByte == 'G' ) {
        int colours[3] = {0};
        
        while(currentId < 3) {
          delay(100);
          colours[currentId++] = Serial.read();
          }
        
  
          pixels.setPixelColor(6, pixels.Color(colours[0], colours[1], colours[2])); // Moderately bright green color.
          pixels.show(); // This sends the updated pixel color to the hardware.
          delay(1000);
          pixels.setPixelColor(6, pixels.Color(0, 0, 0));
          pixels.show();
        }
        else  if (incomingByte == 'H' ) {
        int colours[3] = {0};
        
        while(currentId < 3) {
          delay(100);
          colours[currentId++] = Serial.read();
          }
        
  
          pixels.setPixelColor(7, pixels.Color(colours[0], colours[1], colours[2])); // Moderately bright green color.
          pixels.show(); // This sends the updated pixel color to the hardware.
          delay(1000);
          pixels.setPixelColor(7, pixels.Color(0, 0, 0));
          pixels.show();
        }
        else  if (incomingByte == 'I' ) {
        int colours[3] = {0};
        
        while(currentId < 3) {
          delay(100);
          colours[currentId++] = Serial.read();
          }
        
  
          pixels.setPixelColor(8, pixels.Color(colours[0], colours[1], colours[2])); // Moderately bright green color.
          pixels.show(); // This sends the updated pixel color to the hardware.
          delay(1000);
          pixels.setPixelColor(8, pixels.Color(0, 0, 0));
          pixels.show();
        }

        currentId = 0;
      }
}










