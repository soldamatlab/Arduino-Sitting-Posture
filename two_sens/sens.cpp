#include <MPU6050.h>
#include <Wire.h>

#include "const.h"

int MPU_addr[N_SENSORS];

void initSensor(int MPU_idx) {
    //int sens_address = MPU_addr[MPU_idx];
    Wire.begin();
    Wire.beginTransmission(MPU_ADDR_0);
    Wire.write(PWR_MGMT_1);
    Wire.write(0x00);  // set to zero (wakes up the MPU-6050)
    Wire.endTransmission(true);
    delay (50);

}

void initSens() {
    MPU_addr[0] = MPU_ADDR_0;
    initSensor(0);
    /*MPU_addr[1] = MPU_ADDR_1;
    // MPU_addr[2] = MPU_ADDR_2; // later
    initSensor(sensor_idx);

    for (int sensor_idx = 0; sensor_idx < N_SENSORS; ++sensor_idx) {
        initSensor(sensor_idx);
    }*/
}

void readSens(int sensor, float *save_to) {
    if (sensor == 0) {
      sensor = SENSOR_ARM_PIN;
    } else if (sensor == 1) {
      sensor = SENSOR_LEG_PIN;
    } else if (sensor == 2) {
      sensor = SENSOR_NECK_PIN;
    }
    digitalWrite(sensor, LOW);
    delay(100);

    Wire.beginTransmission(MPU_ADDR_0);
    Wire.write(ACCEL_XOUT_H);  // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDR_0, 6, true);                       // request a total of 14 registers
    save_to[0] = (Wire.read() << 8 | Wire.read()) / ACC_CONSTANT;  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    save_to[1] = (Wire.read() << 8 | Wire.read()) / ACC_CONSTANT;  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    save_to[2] = (Wire.read() << 8 | Wire.read()) / ACC_CONSTANT;  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

    digitalWrite(sensor, HIGH);

}
