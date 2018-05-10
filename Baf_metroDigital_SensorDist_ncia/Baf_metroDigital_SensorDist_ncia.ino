
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h" // legacy include: `#include "SSD1306.h"`

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
 
}

void loop() {
  // put your main code here, to run repeatedly:
  int analogSensor = analogRead(smokeSensor);
  display.clear();
  display.drawString(0, 0, "Bafômetro SmokingHookah!!!"); 
  display.drawString(0, 14, "Embriagez: " + String(map(constrain(analogSensor, 200, 1024), 200, 1024, 0, 100)) + "%");
  Serial.println(analogSensor);
  Serial.println(digitalRead(smokeDigital));
  display.drawString(0,28, "Digital Input: " + String(digitalRead(smokeDigital))); 
  display.display();
  delay(0.02);
  digitalWrite(led, !digitalRead(led));
}
