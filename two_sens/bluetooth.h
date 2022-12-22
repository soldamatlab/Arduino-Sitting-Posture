/*
---------------------- HC05 ----------------------
Bluetooth name: HC05
password:       1234

LED blinking fast:      searching for connection
LED blinking slowly:    connected

----------------------- PC -----------------------
PuTTy (Software for using Bluetooth connection as COM port)

Serial line:        COM[X] (trial and error method works fine)
Connection type:    Serial
*/

#include <SoftwareSerial.h>

extern SoftwareSerial Blue;

void initBluetooth(bool msg = true);
int readBluetooth(char* save_to);
