// Test of the seonsor APDS9960
// This sketch tests the color sensor
//
// filename: TestAPFD9960Color.ino

// Library for APDS9960 sensor
#include <Arduino_APDS9960.h>  


int r; // Measured value for red
int g; // Measured value for green
int b; // Measured value for blue

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

  // check whether color detection is available
  if(APDS.colorAvailable()) 
  {  
    // read the measured values
    APDS.readColor(r, g, b);  
    // print the measured values
    Serial.println("Red = ",r, ", Green = ",g, ", BLUE = ", b );
 	
  }  
}