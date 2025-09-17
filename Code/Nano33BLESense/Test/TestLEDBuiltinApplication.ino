// How to control the built-in LED of the Arduino Nano 33 BLE Sense
//
// file: TestLEDBuiltinApplication.ino
//
// The LED is switched on for 1 second and switched off 
// for 29 second so that the LED flashes accordingly.

// Define the pin for the built-in LED
#define LED_BUILTIN 13 
        
// Stores the last time the LED was turned on		
usigned long currentMillis = 0;  
// Stores the last time the LED was turned on		
usigned long previousMillis = 0;  
// Duty cycle
#define CycleTimeOn 1000
// Switch-off time
#define CycleTimeOff 29000
// state: true - LED on
//        false - LED off
bool SignsOfLifeState = false;



void setup() {
    // Initialize the pin as an output
    pinMode(LED_BUILTIN, OUTPUT);
}
 
// This function checks the elapsed time.
// According the eplapsed time the LED is switched on or off 
void SignsOfLife() {
  // Check if CycleTimeOff have passed since the last LED turn on
  currentMillis = millis();
  if (SignsOfLifeState == true){
    if (currentMillis - previousMillis >= CycleTimeOn) {
      digitalWrite(ledPin, LOW);   // Turn LED on
      previousMillis = currentMillis;
	  SignsOfLifeState = false;
    }
  }
  else {
    if (currentMillis - previousMillis >= CycleTimeOff) {
      digitalWrite(ledPin, HIGH);   // Turn LED on
      previousMillis = currentMillis;
	  SignsOfLifeState = true;
    }
  }
}

   
   
void loop() {
	// Switch builtin LED on/off
	SignsOfLife();
	
	// Application
}