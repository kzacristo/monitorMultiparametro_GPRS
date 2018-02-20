#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// pin 8 - Serial clock out (SCLK)
// pin 9 - Serial data out (DIN)
// pin 10 - Data/Command select (D/C)
// pin 11 - LCD chip select (CS/CE)
// pin 12 - LCD reset (RST)

Adafruit_PCD8544 display = Adafruit_PCD8544(8, 9, 10, 11, 12);

#define REPORTING_PERIOD_MS     1000

PulseOximeter spo;

uint32_t tsLastReport = 0;

void onBeatDetected(){
    Serial.print("Beat!");
}

void setup(){
    
    Serial.begin(115200);

    Serial.print("Inicializando oximetro de pulso ...");

    if(!spo.begin()){
        Serial.println("FAILED");
        for(;;);
    }
    else{
        Serial.println("SUCESS");
    }

     spo.setOnBeatDetectedCallback(onBeatDetected);
}
void loop(){
    spo.update();
    
    spoUpdate();
    
    hearMonitor();
}

void spoUpdate()
{
    
     if (millis() - tsLastReport > REPORTING_PERIOD_MS) 
     {
        Serial.print("Heart rate:");
        Serial.print(spo.getHeartRate());
        Serial.print("bpm / SpO2:");
        Serial.print(spo.getSpO2());
        Serial.print("% / temp:");
        Serial.print(spo.getTemperature());
        Serial.println("C");

        tsLastReport = millis();
    }
}

void hearMonitor()
{
    display.begin();
    display.setContrast(60); //ajusatr o contraste
    display.clearDisplay(); //apaga o buffer
    display.setTextSize(1); //seta o tamanho da fonte
    display.setTextColor(BLACK); //seta a cor da fonte
    display.setCursor(0,0); //seta a posiçãod o setCursor

    
    display.println("bpm");
    display.setCursor(5,5);
    display.println( spo.getHeartRate());
    display.setCursor(0,0);
    display.println("SpO2");
    display.setCursor(5,5);
    display.println( spo.getSpO2());

    delay(2000);
}


