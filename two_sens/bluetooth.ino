#include <Wire.h>

#include "const.h"

SoftwareSerial Blue(BTRX, BTTX);

void initBluetooth(bool msg = true) {
    Blue.begin(9600);
    if (msg) {
        printInitMessage();
    }
}

void printInitMessage() {
    Serial.print("The BlueTooth name is '");
    Serial.print(BT_NAME);
    Serial.print("'\nPassword is '");
    Serial.print(BT_PASS);
    Serial.println("'");

    Blue.println("Connection estabilished");
}

/*
readBluetooth with BT_MAX_INCOMING_MSG_LENGTH and no memory allocation
*/
int readBluetooth(char* save_to) {
    int written = 0;
    char c;
    while (Blue.available()) {
        if (written == BT_MAX_INCOMING_MSG_LENGTH) {
            // Discard the rest of the message
            while (Blue.available()) {
                Blue.read();
            }
            break;
        }
        save_to[written++] = Blue.read();
    }
    save_to[written] = NULL;
    return written;
}

int listenBluetooth(char* save_to) {
    if (!Blue.available()) return 0;
    int read = readBluetooth(save_to);
    Serial.println(save_to);
    return read;
}
