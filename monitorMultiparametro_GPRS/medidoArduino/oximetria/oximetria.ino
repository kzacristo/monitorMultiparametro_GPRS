#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS     1000

// pin 8 - Serial clock out (SCLK)
// pin 9 - Serial data out (DIN)
// pin 10 - Data/Command select (D/C)
// pin 11 - LCD chip select (CS/CE)
// pin 12 - LCD reset (RST)

Adafruit_PCD8544 displayLCD = Adafruit_PCD8544(8, 9, 10, 11, 12);

// PulseOximeter is the higher level interface to the sensor
// it offers:
//  * beat detection reporting
//  * heart rate calculation
//  * SpO2 (oxidation level) calculation
PulseOximeter op;

uint32_t tsLastReport = 0;

// Callback (registered below) fired when a pulse is detected
void onBeatDetected()
{
  Serial.println("Beat!");
}

void setup()
{
  Serial.begin(115200);


  Serial.print("Initializing pulse oximeter..");

  // Initialize the PulseOximeter instance
  // Failures are generally due to an improper I2C wiring, missing power supply
  // or wrong target chip
  if (!op.begin()) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");
  }

  // The default current for the IR LED is 50mA and it could be changed
  //   by uncommenting the following line. Check MAX30100_Registers.h for all the
  //   available options.
  // op.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);

  // Register a callback for the beat detection
  op.setOnBeatDetectedCallback(onBeatDetected);
}

void loop()
{
  // Make sure to call update as fast as possible
  op.update();
  
  OximeterPulse();
}


void OximeterPulse()
{
  //Serial.begin(9600);

  float fc = op.getHeartRate();
  float SpO2 = op.getSpO2();
  float temp = op.getTemperature();

  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    displayLCD.begin();
    displayLCD.setContrast(60);
    displayLCD.clearDisplay();
    displayLCD.setTextSize(1);
    displayLCD.setTextColor(BLACK);
    displayLCD.setCursor(0, 0);
    displayLCD.println("Heart rate:");
    displayLCD.println();
    displayLCD.setCursor(0, 10);
    displayLCD.print("bpm: ");
    displayLCD.println(fc);
    displayLCD.println();
    displayLCD.setCursor(0, 20);
    displayLCD.print("SpO2: ");
    displayLCD.print(SpO2);
    displayLCD.println(" %");
    displayLCD.setCursor(0, 30);
    displayLCD.print("temp: ");
    displayLCD.println(temp);

    Serial.print("Heart rate:");
    Serial.print(op.getHeartRate());
    Serial.print("bpm / SpO2:");
    Serial.print(op.getSpO2());
    Serial.print("% / temp:");
    Serial.print(op.getTemperature());
    Serial.println("C");

    tsLastReport = millis();
  }

}
