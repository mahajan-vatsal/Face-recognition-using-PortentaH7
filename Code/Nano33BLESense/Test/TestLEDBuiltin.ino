// How to control the built-in LED of the Arduino Nano 33 BLE Sense
//
// file: TestLEDBuiltin.ino
//
// The LED is switched on for 1 second and switched off 
// for 1 second so that the LED flashes accordingly.

// Define the pin for the built-in LED
#define LED_BUILTIN 13 
        
void setup() {
    // Initialize the pin as an output
    pinMode(LED_BUILTIN, OUTPUT);
}
        
void loop() {
    // Turn the LED on
    digitalWrite(LED_BUILTIN, HIGH);
    // Wait for one second
    delay(1000);
    // Turn the LED off
    digitalWrite(LED_BUILTIN, LOW);
    // Wait for one second
    delay(1000);
}