#include <Wire.h>

#include "const.h"
#include "sens.h"

float acceleration[N_SENSORS][N_SENSOR_VALUES];

void setup() {
    initSens();

    delay(20);
}

void loop() {
    readSens(0, acceleration[0]);
    readSens(1, acceleration[1]);

    printSensValues(0);
    printSensValues(1);
    Serial.println();

    delay(250);
}

void printSensValues(int MPU_idx) {
    printSensIdx("ax", MPU_idx);
    Serial.print(acceleration[MPU_idx][0]);
    printSensIdx("ay", MPU_idx);
    Serial.print(acceleration[MPU_idx][1]);
    printSensIdx("ax", MPU_idx);
    Serial.print(acceleration[MPU_idx][2]);
}

void printSensIdx(char *varName, int MPU_idx) {
    Serial.print(" ");
    Serial.print(varName);
    Serial.print(MPU_idx);
    Serial.print(" ");
}
