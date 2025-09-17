// file: TestLEDRGBBrightness.ino

// Define the pins for the RGB LED
#define RED_PIN 22
#define GREEN_PIN 23
#define BLUE_PIN 24
        
// Define the initial brightness values for each color (0-255)
int redBrightness = 0;
int greenBrightness = 0;
int blueBrightness = 0;
        
// Define the increment/decrement value for each color
int redStep = 5;
int greenStep = 3;
int blueStep = 7;
       
void setup() {
    // Set the LED pins as outputs
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);
}        
        
void loop() {
    // Write the PWM values to the LED pins
    analogWrite(RED_PIN, redBrightness);
    analogWrite(GREEN_PIN, greenBrightness);
    analogWrite(BLUE_PIN, blueBrightness);
           
    // Update the brightness values for each color
    redBrightness += redStep;
    greenBrightness += greenStep;
    blueBrightness += blueStep;
            
    // Check if the brightness values are out of range and reverse the direction
    if (redBrightness <= 0 || redBrightness >= 255) {
       redStep = -redStep;
    }
    if (greenBrightness <= 0 || greenBrightness >= 255) {
        greenStep = -greenStep;
    }
    if (blueBrightness <= 0 || blueBrightness >= 255) {
        blueStep = -blueStep;
    }
                    
    // Wait for 10 milliseconds
    delay(10);
}
