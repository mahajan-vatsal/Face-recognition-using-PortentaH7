#include <PDM.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int buttonPin = 11;
const int microphoneDataPin = 7;
const int microphoneClockPin = 9;

bool isMeasuring = false;
unsigned long startTime;
unsigned long endTime;

const int measureThresholdMilliseconds = 1200;

short sampleBuffer[256];
int maxValuesFromBuffer[9999];
int lastBufferIndex = 0;

volatile int samplesRead;
volatile int maxSampleValue;
float maxdBspl = 0.0; // Variable for the highest dB SPL value
bool isDelayOver = false; // Variable to check whether the start delay has expired

// Constants for dB SPL conversion
const float Vref = 3.3;     // Reference voltage of the microcontroller (in volts)
const float Vrms = 0.0036;  // RMS voltage corresponding to 94 dB SPL
const float sensitivity = 42.0;  // Microphone sensitivity (in dBV)

const int blueButtonPin = A6;
const int redButtonPin = A7;
  
// Variables for averaging over 200 ms
const unsigned long averagingTime = 200;  // Time in milliseconds to average the values
unsigned long averagingStartTime = 0;
int valueSum = 0;
int valueCount = 0;

float absoluteSum = 0.0;
int absoluteCount = 0;

int redButtonResult = 0;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);

  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);

  PDM.onReceive(onPDMdata);
}

void onPDMdata() {
  int bytesAvailable = PDM.available();
  PDM.read(sampleBuffer, bytesAvailable);
  samplesRead = bytesAvailable / 2;
}

void loop() {
  HandleInput();
  HandleUI();
}

void HandleInput() {
  bool blueButtonIsPressed = analogRead(blueButtonPin) == LOW;
  bool redButtonIsPressed = analogRead(redButtonPin) == LOW;

  if (blueButtonIsPressed)
    isMeasuring = true;

  if (redButtonIsPressed)
    isMeasuring = false;
    
  bool doNextStep = redButtonIsPressed || blueButtonIsPressed;
  if (doNextStep)
  {
    if (isMeasuring) 
    {
      StartSampling(); 
      absoluteSum = 0.0;
      absoluteCount = 0; 
      maxdBspl = 0.0; // Resetting the highest dB SPL value at the start of a new measurement
      isDelayOver = false; // Reset start delay
      startTime = millis(); // Record start time
    } 
    else 
    {
      StopSampling();
      if (redButtonResult == 0)
      {
        ShowMaxdBspl(); // Display of the highest dB SPL value at the end of the measurement
        redButtonResult = 1;
      }
      else
      {
        ShowAveragedBspl();
        redButtonResult = 0;
      }
    }
  }

  delay(50);
  
  // Check whether the start delay has expired
  bool isMeasureThresholdReached = (millis() - startTime) >= measureThresholdMilliseconds;
  if (isMeasuring && !isDelayOver && isMeasureThresholdReached) {
    isDelayOver = true;
  }
}

void StartSampling() {
  if (!PDM.begin(1, 16000)) {
    Serial.println("Failed to start Measurment!");
    while (1);
  }
}

void StopSampling() {
  PDM.end();
}

void ShowResult() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);

  float dBspl = getDbValueFromPMC(maxSampleValue);
  
  display.println("dBSPL:");
  display.setTextSize(3);
  display.setCursor(20, 32);
  display.println(dBspl);
  display.display();

  if (isDelayOver && dBspl > maxdBspl) { // Check for the highest dB SPL value after the start delay
    maxdBspl = dBspl;
  }
}

float getDbValueFromPMC(int pmcValue) {
  float maxSampleVoltage = maxSampleValue * Vref / 32767.0;
  float dBspl = 20.0 * log10(maxSampleVoltage / Vrms) + sensitivity;
  return dBspl;
}

void ShowMicrophoneValues() {
  if (samplesRead && isDelayOver) {
    maxSampleValue = 0;
    for (int i = 0; i < samplesRead; i++) {
      if (maxSampleValue < abs(sampleBuffer[i])) {
        maxSampleValue = abs(sampleBuffer[i]);
      }
    }
    samplesRead = 0;

    // Add current value to the sum
    valueSum += maxSampleValue;
    valueCount++;

    absoluteSum += getDbValueFromPMC(maxSampleValue);
    absoluteCount++;
    
    // Check if averaging time has elapsed
    unsigned long currentTime = millis();
    if (currentTime - averagingStartTime >= averagingTime) {
      // Calculate average value
      int averagedValue = valueSum / valueCount;

      if (lastBufferIndex == 9998)
        lastBufferIndex = 0;
      maxValuesFromBuffer[++lastBufferIndex] = averagedValue;

      averagingStartTime = currentTime;
      valueSum = 0;
      valueCount = 0;

      ShowResult();
    }
  }
}

void ShowdBValue(String title, float dbSpl) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);

  if (isDelayOver)
  {
    display.println(title);
    display.println(dbSpl);
  }
  else
  {
    display.println("Messung zu   kurz");
  }

  display.display();
}

void ShowMaxdBspl() {
  ShowdBValue("Max dBSPL:    ", maxdBspl);
}

void ShowAveragedBspl() {
  ShowdBValue("Average   dBSPL:             ", absoluteSum / absoluteCount);
}

void HandleUI() {
  if (isMeasuring) {
    ShowMicrophoneValues();
  } else {
    //display.clearDisplay();
    display.display();
  }
}
