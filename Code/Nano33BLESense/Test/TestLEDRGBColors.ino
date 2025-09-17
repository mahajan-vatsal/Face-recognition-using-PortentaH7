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


void setRGB(int r, int g, int b)
{
    // Write the PWM values to the LED pins
    analogWrite(LEDR, r);
    analogWrite(LEDG, g);
    analogWrite(LEDB, b);
}


void loop() {
	// red
	setRGB(255,0,0);
    // Wait for one second
    delay(1000);
	// green
	setRGB(0,255,0);
    // Wait for one second
    delay(1000);
	// blue
	setRGB(0,0,255);
    // Wait for one second
    delay(1000);
	// yellow
	setRGB(255,255,0);
    // Wait for one second
    delay(1000);
	// cyan
	setRGB(0,255,255);
    // Wait for one second
    delay(1000);
	// magenta
	setRGB(255,0,255);
    // Wait for one second
    delay(1000);
	// white
	setRGB(255,255,255);
    // Wait for one second
    delay(1000);
	// black
	setRGB(0,0,0);
    // Wait for one second
    delay(1000);
	// orange
	setRGB(255,127,0);
    // Wait for one second
    delay(1000);
	// pink
	setRGB(255,192,203);
    // Wait for one second
    delay(1000);
	// purple
	setRGB(120,0,128);
    // Wait for one second
    delay(1000);
}
