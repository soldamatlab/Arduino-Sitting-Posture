#include <Wire.h>

#include "averaging.h"
#include "bluetooth.h"
#include "const.h"
#include "sens.h"

float acceleration[N_SENSORS][N_AXIS];
bool posture[3];
char bt_msg[BT_MAX_INCOMING_MSG_LENGTH + 1];
bool on = true;
bool muted = false;
int feedback_mode = 0;

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
    evaluatePosture(posture);
    userFeedback();

    delay(ON_DELAY);
}

// -- functions --------------------------------------------------------------
void bluetoothCommand(char cmd) {
    switch (cmd) {
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

        case BT_SET_FB_MODE_BOOL:
            feedback_mode = FB_MODE_BOOL;
            printlnSerialBlue("Bluetooth feedback mode set to BOOL.");
            break;

        case BT_SET_FB_MODE_EVAL:
            feedback_mode = FB_MODE_EVAL;
            printlnSerialBlue("Bluetooth feedback mode set to EVAL.");
            break;

        case BT_SET_FB_MODE_VALUES:
            feedback_mode = FB_MODE_VALUES;
            printlnSerialBlue("Bluetooth feedback mode set to VALUES.");
            break;

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

void evaluatePosture(bool* save_to) {
    checkPosition(save_to);
    // bool rightPosture = checkPositionDummy();
    bool right_posture = posture[0] && posture[1] && posture[2];
    printPosture(right_posture);
}

void userFeedback() {
    bool all_correct = posture[0] && posture[1] && posture[2];
    if (all_correct) {
        digitalWrite(LED, 0);
        noTone(BUZZER);
    } else {
        digitalWrite(LED, 1);
        if (!muted) tone(BUZZER, 1000);
    }

    if (feedback_mode == FB_MODE_BOOL) {
        bt_feedback_bool(all_correct);
    } else if (feedback_mode == FB_MODE_EVAL) {
        bt_feedback_eval(all_correct);
    }
}

void bt_feedback_bool(bool all_correct) {
    if (all_correct) {
        Blue.println("Correct position");
    } else {
        Blue.println("Wrong position");
    }
}

void bt_feedback_eval(bool all_correct) {
    if (!posture[0]) Blue.print("Move your arm! ");
    if (!posture[1]) Blue.print("Move your leg! ");
    if (!posture[2]) Blue.print("Move your neck! ");
    if (all_correct) {
        Blue.println(":-)");
    } else {
        Blue.println("");
    }
}

void muteBuzzer() {
    if (muted) {
        muted = false;
        printlnSerialBlue("Buzzer unmuted.");
    } else {
        muted = true;
        noTone(BUZZER);
        printlnSerialBlue("Buzzer muted.");
    }
}

// -- feedback & debug --------------------------------------------------------
void printSerialBlue(char* str) {
    Serial.print(str);
    Blue.print(str);
}

void printlnSerialBlue(char* str) {
    Serial.println(str);
    Blue.println(str);
}

void printSens() {
    for (int sensor = 0; sensor < N_SENSORS; ++sensor) {
        printSensValues(sensor);
        Serial.print(" ");
        if (feedback_mode == FB_MODE_VALUES) Blue.print(" ");
    }
}

void printSensValues(int MPU_idx) {
    printSensIdx("ax", MPU_idx);
    Serial.print(acceleration[MPU_idx][AXIS_X_IDX]);
    if (feedback_mode == FB_MODE_VALUES) Blue.print(acceleration[MPU_idx][AXIS_X_IDX]);
    printSensIdx("ay", MPU_idx);
    Serial.print(acceleration[MPU_idx][AXIS_Y_IDX]);
    if (feedback_mode == FB_MODE_VALUES) Blue.print(acceleration[MPU_idx][AXIS_Y_IDX]);
    printSensIdx("az", MPU_idx);
    Serial.print(acceleration[MPU_idx][AXIS_Z_IDX]);
    if (feedback_mode == FB_MODE_VALUES) Blue.print(acceleration[MPU_idx][AXIS_Z_IDX]);
}

void printSensIdx(char* var_name, int MPU_idx) {
    Serial.print(" ");
    Serial.print(var_name);
    Serial.print(MPU_idx);
    Serial.print(" ");
    if (feedback_mode == FB_MODE_VALUES) {
        Blue.print(" ");
        Blue.print(var_name);
        Blue.print(MPU_idx);
        Blue.print(" ");
    }
}

void printPosture(bool right_posture) {
    Serial.print(" Posture: ");
    Serial.println(right_posture);
    if (feedback_mode == FB_MODE_VALUES) {
        Blue.print(" Posture: ");
        Blue.println(right_posture);
    }
}

bool checkPositionDummy() {
    return acceleration[SENSOR_NECK_IDX][AXIS_X_IDX] >= -0.25;
}
