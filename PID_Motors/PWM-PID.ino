// MPU-6050 Short Example Sketch
// By Arduino User JohnChi
// August 17, 2014
// Public Domain
#include<Wire.h>
#include "SSD1306Wire.h"

#define valorInicial 40;

const int MPU_addr = 0x68; // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
int Pitch, Roll;

SSD1306Wire  display(0x3c, D3, D5);

int pino_motor1 = D0, pino_motor2 = D1, pino_button = D2;
int PWM_Motor1 = valorInicial;
int PWM_Motor2 = valorInicial;

void setup() {

  //-----------------------------------------------
  Wire.begin(D3, D5);
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  //-----------------------------------------------
  display.init();
  //display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  //-----------------------------------------------
  Serial.begin(9600);
}
void loop() {
  //-----------------------------------------------
  // Mostra o valor no display
  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.drawString(16, 0, "Motor1:");
  display.drawString(68, 0, "Motor1:");
  display.setFont(ArialMT_Plain_16);
  display.drawString(24, 24, String(PWM_Motor1));
  display.drawString(72, 24, String(PWM_Motor2));
  display.display();
  //-----------------------------------------------
  //  Serial.print("PWM_M1: ");
  //  Serial.print(PWM_Motor1);
  //  Serial.print(" | PWM_M2: ");
  //  Serial.print(PWM_Motor2);
  //  Serial.print(" B1-: ");
  //  Serial.print(analogRead(D0));
  //  Serial.print(" B1+: ");
  //  Serial.print(analogRead(D1));
  //  Serial.print(" | B2-: ");
  //  Serial.print(analogRead(D7));
  //  Serial.print(" B2+: ");
  //  Serial.println(analogRead(D8));
  //-----------------------------------------------
  if (analogRead(D0) == 1023) {
    PWM_Motor1 --;
    delay(150);
  }
  if (analogRead(D1) == 1023) {
    PWM_Motor1 ++;
    delay(150);
  }
  if (analogRead(D7) == 1023) {
    PWM_Motor2 --;
    delay(150);
  }
  if (analogRead(D8) == 1023) {
    PWM_Motor2 ++;
    delay(150);
  }
  //-----------------------------------------------
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  //  Serial.print("AcX = "); Serial.print(AcX);
  //  Serial.print(" | AcY = "); Serial.print(AcY);
  //  Serial.print(" | AcZ = "); Serial.print(AcZ);
  //  Serial.print(" | Tmp = "); Serial.print(Tmp / 340.00 + 36.53); //equation for temperature in degrees C from datasheet
  //  Serial.print(" | GyX = "); Serial.print(GyX);
  //  Serial.print(" | GyY = "); Serial.print(GyY);
  //  Serial.print(" | GyZ = "); Serial.println(GyZ);

  Roll = FunctionsPitchRoll(AcX, AcY, AcZ);   //Calcolo angolo Roll
  Pitch = FunctionsPitchRoll(AcY, AcX, AcZ);  //Calcolo angolo Pitch

  int ServoRoll = map(Roll, -90, 90, 0, 179);
  int ServoPitch = map(Pitch, -90, 90, 179, 0);

  Serial.print("Pitch: "); Serial.print(Pitch);
  Serial.print("\t");
  Serial.print("Roll: "); Serial.print(Roll);
  Serial.print("\n");
  // delay(333);

}

double FunctionsPitchRoll(double A, double B, double C) {
  double DatoA, DatoB, Value;
  DatoA = A;
  DatoB = (B * B) + (C * C);
  DatoB = sqrt(DatoB);

  Value = atan2(DatoA, DatoB);
  Value = Value * 180 / 3.14;

  return (int)Value;
}
