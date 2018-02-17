#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// pin 8 - Serial clock out (SCLK)
// pin 9 - Serial data out (DIN)
// pin 10 - Data/Command select (D/C)
// pin 11 - LCD chip select (CS/CE)
// pin 12 - LCD reset (RST)

Adafruit_PCD8544 lcd = Adafruit_PCD8544(8, 9, 10, 11, 12);
#define REPORTING_PERIOD_MS   1000

PulseOximeter spo;

uint32_t tslastReport = 0;

void onBeatDetected(){
    serial.print("Beat!");
}

void setup(){
    Serial.begin(9600);

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
        Serial.print(spo.getHeartRate());
        Serial.print("bpm / SpO2:");
        Serial.print(spo.getSpO2());
        Serial.print("% / temp:");
        Serial.print(spo.getTemperature());
        Serial.println("C");

        tsLastReport = millis();

    }

void lcd(){
    lcd.begin();
    lcd.setContrast(60); //ajusatr o contraste
    lcd.clearDisplay(); //apaga o buffer
    lcd.setTextSize(2); //seta o tamanho da fonte
    lcd.setTextColor(BLACK); //seta a cor da fonte
    lcd.setCursor(0,0); //seta a posiçãod o setCursor

    lcd.println("bpm / SpO2");
    lcd.println(" % ");

    delay(2000);
}

}