#include <Wire.h>

#include "averaging.h"
#include "bluetooth.h"
#include "const.h"
#include "sens.h"

float acceleration[N_SENSORS][N_AXIS];
char bt_msg[BT_MAX_INCOMING_MSG_LENGTH + 1];
bool on = true;
bool muted = false;

void setup() {
    Serial.begin(9600);
    initSens();
    initAveraging();
    initBluetooth();

    pinMode(BUTTON_PIN, BUTTON_MODE);
    pinMode(LED, OUTPUT);
    pinMode(BUZZER, OUTPUT);

    pinMode(SENSOR_ARM_PIN, OUTPUT);
    pinMode(SENSOR_LEG_PIN, OUTPUT);
    pinMode(SENSOR_NECK_PIN, OUTPUT);
    digitalWrite(SENSOR_ARM_PIN, HIGH);
    digitalWrite(SENSOR_LEG_PIN, HIGH);
    digitalWrite(SENSOR_NECK_PIN, HIGH);
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

    case BT_RESET_SENS_VALUES:
        resetValues();
        return;

    case BT_MUTE_BUZZER:
        muteBuzzer();
        return;
    
    default:
        return;
    }
}

void measure() {
    for (int sensor = 0; sensor < N_SENSORS; ++sensor) {
        readSens(sensor, acceleration[sensor]);
        updateValues(acceleration[sensor], sensor);
    }
    printSens();
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
        if (!muted) tone(BUZZER, 1000);
        Blue.println("Wrong position");
    }
}

void muteBuzzer() {
    if (muted) {
        muted = false;
        Serial.println("Buzzer unmuted.");
    } else {
        muted = true;
        noTone(BUZZER);
        Serial.println("Buzzer muted.");
    }
}

// -- debug ------------------------------------------------------------------
void printSens() {
    for (int sensor = 0; sensor < N_SENSORS; ++sensor) {
        printSensValues(sensor);
        Serial.print(" ");
    }
}

void printSensValues(int MPU_idx) {
    printSensIdx("ax", MPU_idx);
    Serial.print(acceleration[MPU_idx][AXIS_X_IDX]);
    printSensIdx("ay", MPU_idx);
    Serial.print(acceleration[MPU_idx][AXIS_Y_IDX]);
    printSensIdx("az", MPU_idx);
    Serial.print(acceleration[MPU_idx][AXIS_Z_IDX]);
}

void printSensIdx(char* varName, int MPU_idx) {
    Serial.print(" ");
    Serial.print(varName);
    Serial.print(MPU_idx);
    Serial.print(" ");
}

void printPosture(bool rightPosture) {
    Serial.print(" Posture: ");
    Serial.println(rightPosture);
}

bool checkPositionDummy() {
    return acceleration[SENSOR_NECK_IDX][AXIS_X_IDX] >= -0.25;
}
