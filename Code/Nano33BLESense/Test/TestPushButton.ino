// How to read in the built-in button states. 
//
// file: TestPushButton.ino
//
// If the button is pressed, the the internal LED
// is turn on for 2 seconds

// Use the onboard push button (BUTTON_B)
#define BUTTON_PIN  BUTTON_B
// Define the pin for the built-in LED
#define LED_BUILTIN 13 
 
int buttonState = 0;
 
void setup() {
  // Initialize the pin as an output
  pinMode(LED_BUILTIN, OUTPUT);
  // Initialize the pin as an input
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

        
void loop() 
{
  buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == HIGH) 
  {	
    // Turn the LED on
    digitalWrite(LED_BUILTIN, HIGH);
    // Wait for two second
    delay(2000);
    // Turn the LED off
    digitalWrite(LED_BUILTIN, LOW);
    // Wait for one second
    delay(1000);
	buttonState = LOW;
  }	
}