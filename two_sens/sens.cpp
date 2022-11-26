#include <MPU6050.h>
#include <Wire.h>

#include "const.h"

int MPU_addr[N_SENSORS];

void initSensor(int MPU_idx)
{
    int sens_address = MPU_addr[MPU_idx];
    Serial.begin(9600);
    Wire.begin();
    Wire.beginTransmission(sens_address);
    Wire.write(PWR_MGMT_1);
    Wire.write(0); // set to zero (wakes up the MPU-6050)
    Wire.endTransmission(true);
}

void initSens()
{
    MPU_addr[0] = MPU_ADDR_0;
    MPU_addr[1] = MPU_ADDR_1;
    // MPU_addr[2] = MPU_ADDR_2; // later

    for (int sensor_idx = 0; sensor_idx < N_SENSORS; ++sensor_idx)
    {
        initSensor(sensor_idx);
    }
}

void readSens(int MPU_idx, float *save_to)
{
    int sens_address = MPU_addr[MPU_idx];
    Wire.beginTransmission(sens_address);
    Wire.write(ACCEL_XOUT_H); // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(sens_address, 6, true);                      // request a total of 14 registers
    save_to[0] = (Wire.read() << 8 | Wire.read()) / ACC_CONSTANT; // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    save_to[1] = (Wire.read() << 8 | Wire.read()) / ACC_CONSTANT; // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    save_to[2] = (Wire.read() << 8 | Wire.read()) / ACC_CONSTANT; // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
}
