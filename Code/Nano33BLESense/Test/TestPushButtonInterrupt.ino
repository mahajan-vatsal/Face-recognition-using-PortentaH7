// How to control an external LED 
// and using the builtin button 
// with the Arduino Nano 33 BLE Sense
//
// file: TestPushButtonInterrupt.ino
//
// If the builtin button is pressed, the LED is switched on 
// for 2 second and switched off agin

// Define the pin for the LED
#define LED_EXT 14 
// Use the onboard push button (BUTTON_B)
#define BUTTON_PIN  BUTTON_B
 
// Initialize variables
// Flag, whether the button is pressed
// Declare as volatile for interrupt safety
volatile bool pushPressed = false; 
// LED-Status zur Verarbeitng 
int ledState = 0;
 
void setup() {
  // Initialize the pin as an output
  pinMode(LED_EXT, OUTPUT);
  // Initialize the pin as an input
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  // Initialize the interrupt function    
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonPressed, FALLING);
}
        

// Interrupt function
// as short as possible
void buttonPressed() 
{
  if (pushPressed == false) 
  {
    pushPressed = true;
  }	
}

void loop() 
{
  if (pushPressed)
  {
    // Turn the LED on
    digitalWrite(LED_EXT, HIGH);
    // Wait for one second
    delay(2000);
    // Turn the LED off
    digitalWrite(LED_EXT, LOW);
    pushPressed = false;	  
  }	
}