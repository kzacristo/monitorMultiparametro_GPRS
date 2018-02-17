#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS   1000

PulseOximeter spo;

uint32_t tslastReport = 0;

void onBeatDetected(){
    serial.print("Beat!");
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
    spoUpdate();
    lcd();
}

void spoUpdate(){
    spo.spoUpdate();

    if(millis() - tslastReport > REPORTING_PERIOD_MS){
       Serial.print("Heart rate:");
        Serial.print(pox.getHeartRate());
        Serial.print("bpm / SpO2:");
        Serial.print(pox.getSpO2());
        Serial.print("% / temp:");
        Serial.print(pox.getTemperature());
        Serial.println("C");

        tsLastReport = millis();

    }

void lcd(){
    
}

}