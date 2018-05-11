
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h" // legacy include: `#include "SSD1306.h"`
//oled 128 x 64

SSD1306Wire  display(0x3c, D3, D5);
int led = 16, smokeSensor = A0, smokeDigital = 4;

void setup() {
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  pinMode(led, OUTPUT);
  pinMode(smokeSensor, INPUT);
  pinMode(smokeDigital, INPUT);
  Serial.begin(9600);
  //startSensor();
}

void loop() {
  // put your main code here, to run repeatedly:
  display.clear();
  int analogSensor = analogRead(smokeSensor);
  display.setFont(ArialMT_Plain_10);
  display.drawString(32, 0, "BAFOMETRO");
  display.setFont(ArialMT_Plain_16);
  display.drawString(57, 28, String(analogSensor));
  Serial.println(analogSensor);
  Serial.println(digitalRead(smokeDigital));
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 54, "DRUNK");
  display.display();
  delay(0.02);
  digitalWrite(led, !digitalRead(led));
}

void startSensor() {
  int i, j, progress = 0, percentageInt = 0;
  float percentage = 0, contador = 0;
  display.drawString(32, 0, "AQUECENDO");
  display.drawProgressBar( 0 , 30, 128, 10, percentageInt );
  display.drawString(60, 50, String(percentageInt) + "%");
  display.display();
  for (i = 0; i < 15; i++) {
    for (j = 0; j < 60; j++) {
      delay(1000);
      display.clear();
      display.drawString(32, 0, "AQUECENDO");
      contador++;
      Serial.println(contador);
      percentage = (contador / 900) * 100;
      Serial.println(percentage);
      percentageInt = (int)percentage;
      Serial.println(percentageInt);
      display.drawProgressBar( 0 , 30, 128, 10, percentageInt );
      display.drawString(60, 50, String(percentageInt) + "%");
      display.display();
    }
  }
}

