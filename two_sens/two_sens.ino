#include <MPU6050.h>
#include <Wire.h>

// Architecture
#define N_SENSORS (2)       // later 3
#define N_SENSOR_VALUES (3) // later 6

// Sensor addresses
#define MPU_ADDR_0 (0x68) // I2C address of the first MPU-6050
#define MPU_ADDR_1 (0x69) // I2C address of the second MPU-6050

// Registers
#define PWR_MGMT_1 (0x6B) // PWR_MGMT_1 register

#define ACCEL_CONFIG (0x1C) // set accelerometer range here with one of the following values
#define AFS_SEL_2G (0x00)   // +/- 2G
#define AFS_SEL_4G (0x08)   // +/- 4G
#define AFS_SEL_8G (0x10)   // +/- 8G
#define AFS_SEL_16G (0x18)  // +/- 16G

#define ACCEL_XOUT_H (0x3B)
#define ACCEL_XOUT_L (0x3C)
#define ACCEL_YOUT_H (0x3D)
#define ACCEL_YOUT_L (0x3E)
#define ACCEL_ZOUT_H (0x3F)
#define ACCEL_ZOUT_L (0x40)

// Numerical constants
#define ACC_CONSTANT (8192.0)

const int *MPU_addr[2];
float acceleration[N_SENSORS][N_SENSOR_VALUES]; // definition of variables

void setup()
{
  initGlobalVars();
  
  initSens(0);
  initSens(1);

  delay(20);
}

void loop()
{
  readSens(0);
  readSens(1);

  printSensValues(0);
  printSensValues(1);
  Serial.println();

  delay(250);
}

void initGlobalVars() {
  MPU_addr[0] = MPU_ADDR_0;
  MPU_addr[1] = MPU_ADDR_1;
}

void initSens(int MPU_idx) {
  int sens_address = MPU_addr[MPU_idx];
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(sens_address);
  Wire.write(PWR_MGMT_1);
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

void readSens(int MPU_idx)
{
  int sens_address = MPU_addr[MPU_idx];
  Wire.beginTransmission(sens_address);
  Wire.write(ACCEL_XOUT_H); // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(sens_address, 6, true);                                    // request a total of 14 registers
  acceleration[MPU_idx][0] = (Wire.read() << 8 | Wire.read()) / ACC_CONSTANT; // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  acceleration[MPU_idx][1] = (Wire.read() << 8 | Wire.read()) / ACC_CONSTANT; // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  acceleration[MPU_idx][2] = (Wire.read() << 8 | Wire.read()) / ACC_CONSTANT; // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
}

void printSensValues(int MPU_idx)
{
  printSensIdx("ax", MPU_idx);
  Serial.print(acceleration[MPU_idx][0]);
  printSensIdx("ay", MPU_idx);
  Serial.print(acceleration[MPU_idx][1]);
  printSensIdx("ax", MPU_idx);
  Serial.print(acceleration[MPU_idx][2]);
}

void printSensIdx(char *varName, int MPU_idx)
{
  Serial.print(" ");
  Serial.print(varName);
  Serial.print(MPU_idx);
  Serial.print(" ");
}
