#include <Wire.h>

#include "const.h"
#include "sens.h"
#include "bluetooth.h"
#include "averaging.h"

float acceleration[N_SENSORS][N_SENSOR_VALUES];
char bt_msg[BT_MSG_MAX_LENGTH + 1];
int btRead;

void setup() {
  Serial.begin(9600);
  initSens();
  initBluetooth();
  initThresholds();
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
    // OFF button
    /*
    if (digitalRead(BUTTON_PIN)) {
        delay(250);
        return;
    }
    */

    // Bluetooth
    // TODO
    if (Blue.available()) {
        readBluetooth(bt_msg);
        Serial.println(bt_msg);
    }
    if (Serial.available()) {
        Blue.write(Serial.read());
    }

    // Measure
    for (int sensor = 0; sensor < N_SENSORS; ++sensor) {
        measure(sensor);
        updateValues(acceleration[sensor], sensor);
    }
    Serial.println();
    bool rightPosture = checkPosition();

    // Feedback
    userFeedback(rightPosture);

    delay(250);
}



void measure(int sensor) {
    readSens(sensor, acceleration[sensor]);
    //readSens(1, acceleration[1]);

    printSensValues(sensor);
    Serial.print(" ");
}

void printSensValues(int MPU_idx) {
    printSensIdx("ax", MPU_idx);
    Serial.print(acceleration[MPU_idx][0]);
    printSensIdx("ay", MPU_idx);
    Serial.print(acceleration[MPU_idx][1]);
    printSensIdx("az", MPU_idx);
    Serial.print(acceleration[MPU_idx][2]);
}

void printSensIdx(char *varName, int MPU_idx) {
    Serial.print(" ");
    Serial.print(varName);
    Serial.print(MPU_idx);
    Serial.print(" ");
}

// Dummy functions
bool evaluatePosture() {
    if (acceleration[2][0] < -0.25) {
        return false;
    }
    return true;
}

void userFeedback(bool rightPosture) {
    Serial.print(" Posture:");
    Serial.print(rightPosture);
    if (rightPosture) {
        digitalWrite(LED, 0);
        noTone(BUZZER);
    } else {
        digitalWrite(LED, 1);
        tone(BUZZER, 1000);
    }
}
