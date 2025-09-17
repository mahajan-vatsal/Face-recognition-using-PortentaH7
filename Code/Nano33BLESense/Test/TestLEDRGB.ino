// file: TestLEDRGB

// Define the pins for the RGB LED
#define LEDR 22
#define LEDG 23
#define LEDB 24


void setup() {
  // Set the LED pins as outputs
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
}


void loop() {
    // Turn the red LED on
    digitalWrite(LEDR, HIGH);
    // Wait for one second
    delay(1000);
    // Turn the LED off
    digitalWrite(LEDR, LOW);
    // Turn the green LED on
    digitalWrite(LEDF, HIGH);
    // Wait for one second
    delay(1000);
    // Turn the LED off
    digitalWrite(LEDG, LOW);
    // Turn the blue LED on
    digitalWrite(LEDB, HIGH);
    // Wait for one second
    delay(1000);
    // Turn the LED off
    digitalWrite(LEDB, LOW);
    // Wait for one second
    delay(1000);
}
