#include <Wire.h>

#include "const.h"
#include "sens.h"

float acceleration[N_SENSORS][N_SENSOR_VALUES];

void setup() {
    Serial.begin(9600);
    initSens();
    pinMode(BUTTON_PIN, BUTTON_MODE);

    delay(20);
}

void loop() {
    bool on = !digitalRead(BUTTON_PIN);
    if (on) {
        measure();
        bool rightPosture = evaluatePosture();
        userFeedback(rightPosture);
    }

    delay(250);
}

void measure() {
    readSens(0, acceleration[0]);
    readSens(1, acceleration[1]);

    printSensValues(0);
    printSensValues(1);
    Serial.println();
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

bool evaluatePosture() {
    if (acceleration[0][0] < -0.25) {
        return false;
    }
    return true;
}

void userFeedback(bool rightPosture) {
    if (rightPosture) {
        digitalWrite(LED, 0);
    } else {
        digitalWrite(LED, 1);
    }
}
