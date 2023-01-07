#include <Wire.h>

#include "averaging.h"
#include "bluetooth.h"
#include "const.h"
#include "sens.h"

float acceleration[N_SENSORS][N_SENSOR_VALUES];
char bt_msg[BT_MAX_INCOMING_MSG_LENGTH + 1];
bool on = true;

void setup() {
    Serial.begin(9600);
    initSens();
    initThresholds();
    initBluetooth();

    pinMode(BUTTON_PIN, BUTTON_MODE);
    pinMode(LED, OUTPUT);
    pinMode(BUZZER, OUTPUT);

    pinMode(SENSOR_PIN_0, OUTPUT);
    pinMode(SENSOR_PIN_1, OUTPUT);
    pinMode(SENSOR_PIN_2, OUTPUT);

    digitalWrite(SENSOR_PIN_0, HIGH);
    digitalWrite(SENSOR_PIN_1, HIGH);
    digitalWrite(SENSOR_PIN_2, HIGH);
}

void loop() {
    if (listenBluetooth(bt_msg)) bluetoothCommand(bt_msg[0]);

    // OFF (rest of 'loop()' will be skipped when OFF)
    if (digitalRead(BUTTON_PIN) || !on) {
        delay(OFF_DELAY);
        return;
    }

    measure();

    bool rightPosture = evaluatePosture();

    userFeedback(rightPosture);

    delay(ON_DELAY);
}

// -- functions --------------------------------------------------------------
void bluetoothCommand(char cmd) {
    switch (cmd)
    {
    case BT_OFF:
        on = false;
        return;

    case BT_ON:
        on = true;
        return;
    
    default:
        return;
    }
}

void measure() {
    for (int sensor = 0; sensor < N_SENSORS; ++sensor) {
        readSens(sensor, acceleration[sensor]);
        updateValues(acceleration[sensor], sensor);
        printSensValues(sensor);
        Serial.print(" ");
    }
    Serial.println();
}

bool evaluatePosture() {
    bool rightPosture = checkPosition();
    // bool rightPosture = checkPositionDummy();
    printPosture(rightPosture);
    return rightPosture;
}

void userFeedback(bool rightPosture) {
    if (rightPosture) {
        digitalWrite(LED, 0);
        noTone(BUZZER);
        Blue.println("Correct position");
    } else {
        digitalWrite(LED, 1);
        tone(BUZZER, 1000);
        Blue.println("Wrong position");
    }
}

// -- debug ------------------------------------------------------------------
void printSensValues(int MPU_idx) {
    printSensIdx("ax", MPU_idx);
    Serial.print(acceleration[MPU_idx][0]);
    printSensIdx("ay", MPU_idx);
    Serial.print(acceleration[MPU_idx][1]);
    printSensIdx("az", MPU_idx);
    Serial.print(acceleration[MPU_idx][2]);
}

void printSensIdx(char* varName, int MPU_idx) {
    Serial.print(" ");
    Serial.print(varName);
    Serial.print(MPU_idx);
    Serial.print(" ");
}

void printPosture(bool rightPosture) {
    Serial.print(" Posture:");
    Serial.print(rightPosture);
}

bool checkPositionDummy() {
    return acceleration[2][0] >= -0.25;
}
