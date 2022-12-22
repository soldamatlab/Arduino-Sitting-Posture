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
readBluetooth with BT_MSG_MAX_LENGTH and no memory allocation
*/
int readBluetooth(char* save_to) {
    int written = 0;
    char c;
    while(Blue.available()) {
        if (written == BT_MSG_MAX_LENGTH) {
            // Discard the rest of the message
            while(Blue.available()) {
                Blue.read();
            }
            break;
        }
        save_to[written++] = Blue.read();
    }
    save_to[written] = NULL;
    return written;
}
