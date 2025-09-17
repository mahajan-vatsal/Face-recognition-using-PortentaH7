// Test of the seonsor APDS9960
// This sketch tests the gesture sensor
//
// filename: TestAPFD9960Gesture.ino

// Library for APDS9960 sensor
#include <Arduino_APDS9960.h>  


int proximity; // Measured value for the distance

void setup() 
{
  Serial.begin(9600);

  // initialze the sensor
  if (!APDS.begin()) {
    Serial.println("Error initializing APDS9960 sensor.");
  }
}

void loop() 
{
  // check whether distance measurement is available, if not 5 ms
  if (APDS.proximityAvailable()) 
  { 
    // read the Measured value 
    proximity = APDS.readProximity();
    // print the measured value
    if (proximity != -1) {
      Serial.print("Distance: ");
      Serial.println(proximity);
    }
  }
 
}