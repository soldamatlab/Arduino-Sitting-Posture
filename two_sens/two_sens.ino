#include <MPU6050.h>

#include<Wire.h>
const int MPU_addr_1 = 0x68; // I2C address of the first MPU-6050
const int MPU_addr_2 = 0x69; // I2C address of the second MPU-6050
float AcX1, AcY1, AcZ1, AcX2, AcY2, AcZ2; // definition of variables


void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_addr_1);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  
  Wire.begin();
  Wire.beginTransmission(MPU_addr_2);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);



  delay (20);
}

void loop() {
  Wire.beginTransmission(MPU_addr_1);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr_1, 6, true); // request a total of 14 registers
  
  AcX1 = (Wire.read() << 8 | Wire.read()) / 8192.0; // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY1 = (Wire.read() << 8 | Wire.read()) / 8192.0; // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ1 = (Wire.read() << 8 | Wire.read()) / 8192.0; // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  
  Wire.beginTransmission(MPU_addr_2);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr_2, 6, true); // request a total of 14 registers
  AcX2 = (Wire.read() << 8 | Wire.read()) / 8192.0; // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY2= (Wire.read() << 8 | Wire.read()) / 8192.0; // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ2 = (Wire.read() << 8 | Wire.read()) / 8192.0; // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

  Serial.print("ax1 "); 
  Serial.print(AcX1);
  Serial.print(" ay1 ");
  Serial.print(AcY1);
  Serial.print(" az1 ");
  Serial.print(AcZ1);

  Serial.print(" ax2 "); 
  Serial.print(AcX2);
  Serial.print(" ay2 ");
  Serial.print(AcY2);
  Serial.print(" az2 ");
  Serial.println(AcZ2);
  delay(250);
}
