// file: TestLEDBrightness.ino

// Define the pin for the external LED
#define LED_EXT 21
        
// Define the initial brightness values (0-255)
int ledBrightness = 0;
        
// Define the increment/decrement value 
int ledStep = 5;
       
void setup() {
    // Set the LED pin as output
    pinMode(LED_EXT, OUTPUT);
}        
        
void loop() {
    // Write the PWM value to the LED pin
    analogWrite(LED_EXT, ledBrightness);
           
    // Update the brightness value
    ledBrightness += ledStep;
            
    // Check if the brightness value is out of range and reverse the direction
    if (ledBrightness <= 0 || ledBrightness >= 255) {
       ledStep = -ledStep;
    }
    // Wait for 10 milliseconds
    delay(10);
}
