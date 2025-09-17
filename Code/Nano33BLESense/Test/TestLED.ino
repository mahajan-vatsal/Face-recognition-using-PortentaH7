// How to control an external LED with the Arduino Nano 33 BLE Sense
//
// file: TestLED.ino
//
// The LED is switched on for 1 second and switched off 
// for 1 second so that the LED flashes accordingly.

// Define the pin for the LED
#define LED_EXT 14 
        
void setup() {
    // Initialize the pin as an output
    pinMode(LED_EXT, OUTPUT);
}
        
void loop() {
    // Turn the LED on
    digitalWrite(LED_EXT, HIGH);
    // Wait for one second
    delay(1000);
    // Turn the LED off
    digitalWrite(LED_EXT, LOW);
    // Wait for one second
    delay(1000);
}