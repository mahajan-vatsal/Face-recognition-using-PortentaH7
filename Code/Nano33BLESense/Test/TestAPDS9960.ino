// Library for  sensor APDS9960
#include <Arduino_APDS9960.h>  

// Library SSD1306 for text-only output and connection 
// with cable via the I2C protocol
#include <SSD1306AsciiWire.h>  
// Enter the address of the OLED
#define I2C_ADDRESS 0x3C  

// Set the name of the OLED
SSD1306AsciiWire oled;  

// Initialization of the measurement button
const int TasterPin = 11;  
// Initialization of the LED pin
const int LedPin = 12;     


void setup() 
{
  Serial.begin(9600);

  // Define pin as INPUT and activate internal pull-up resistor
  pinMode(TasterPin, INPUT);   
  // Define pin as OUTPUT
  pinMode(LedPin, OUTPUT);           


  if (!APDS.begin()) {
    Serial.println("Error initializing APDS9960 sensor.");
  }


  // Arduino is hereby registered in the I2C bus, 
  // as it is to be registered as a master, 
  // the address SEARCH SOURCE!!!!! is omitted.
  Wire.begin();                              
  // Clock frequency in Hertz, 
  // Standard: 100,000
  // Fast mode:  400,000 
  Wire.setClock(400000L);                   
  // first screen size, then reference to I2C address  
  oled.begin(&Adafruit128x64, I2C_ADDRESS); 
  oled.setFont(System5x7);
  oled.setCursor(0, 40);
  oled.println("INITIALISIERUNG!\n");


  // External LED flashes 3 times during initialization
  for (int zaehler = 1; zaehler < 4; zaehler = zaehler + 1) 
  {  
    delay(2000);
    digitalWrite(LedPin, HIGH);
    delay(200);
    digitalWrite(LedPin, LOW);
    delay(200);
  }
  oled.clear();
}


void loop() 
{
  oled.println("READY!");

  // check whether color detection is available, 
  // if not wait 5 ms and repeat query
  while (!APDS.colorAvailable()) {  
    delay(5);
  }

  // Check whether distance measurement is available, 
  // if not wait 5 ms and repeat query
  while (!APDS.proximityAvailable()) {  
    delay(5);
  }

  // Create integer variables to save 
  // the measured values for red, green and blue
  int r, g, b, tasterCount{ 0 };  

  // Status query of the measurement button
  bool zustandTaster = digitalRead(TasterPin);  

  if (zustandTaster == 0) {
    tasterCount = 1;
  }

  // if clause switch to measuring mode when the button is pressed
  if (tasterCount == 1) 
  {  
    int proximity = APDS.readProximity();

    if (proximity != -1) {
      Serial.print("Abstand: ");
      Serial.println(proximity);

      if (proximity < 20) {
        oled.clear();
        digitalWrite(LedPin, HIGH);


        // 3x Color scan and save in the 3 variables r, g and b
        for (int i = 0; i < 3; i++) {
			
          APDS.readColor(r, g, b);  
          delay(1500);
        }


        // Display largest value via integrated RGB LED, 
		// option for troubleshooting
        if (r > g & r > b) {  
          digitalWrite(LEDR, LOW);
          digitalWrite(LEDG, HIGH);
          digitalWrite(LEDB, HIGH);
        } else if (g > r & g > b) {
          digitalWrite(LEDG, LOW);
          digitalWrite(LEDR, HIGH);
          digitalWrite(LEDB, HIGH);
        } else if (b > g & b > r) {
          digitalWrite(LEDB, LOW);
          digitalWrite(LEDR, HIGH);
          digitalWrite(LEDG, HIGH);
        } else {
          digitalWrite(LEDR, HIGH);
          digitalWrite(LEDG, HIGH);
          digitalWrite(LEDB, HIGH);
        }


        // Output values in the serial monitor 
		// for testing and error analysis
        Serial.print("Red light = ");  
        Serial.println(r);
        Serial.print("Green light = ");
        Serial.println(g);
        Serial.print("Blue light = ");
        Serial.println(b);
        Serial.println();

        
        if (r > g & r > b) {
          oled.println("Das Objekt ist rot!");
        } else if (g > r & g > b) {
          oled.println("Das Objekt ist gruen!");
        } else if (b > g & b > r) {
          oled.println("Das Objekt ist blau!");
        }


        delay(4000);
        oled.clear();
      }

      else {
        oled.clear();
        oled.println("Kein Objekt \nvorhanden!\n");
        oled.println("Halten Sie ein\nObjekt vor den \nSensor \noder veraendern Sie\ndie Position!");
        digitalWrite(LEDR, HIGH);
        digitalWrite(LEDG, HIGH);
        digitalWrite(LEDB, HIGH);
        delay(4000);
        oled.clear();
      }
    } else {
      oled.println("Abstandsmessung fehlgeschlagen!");
    }
  }

  else {
    // Switch off LED if not pressed	  
    digitalWrite(LedPin, LOW);  
	
    oled.setFont(System5x7);
    oled.setCursor(0, 40);
    oled.println("READY!");
	
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDB, HIGH);
  }
  
  // Set button to 0
  zustandTaster = 0;  
  
}