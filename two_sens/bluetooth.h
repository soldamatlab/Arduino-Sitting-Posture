/*
---------------------- HC05 ----------------------
Bluetooth name: HC05
password:       1234

LED blinking fast:      searching for connection
LED blinking slowly:    connected

----------------------- PC -----------------------
PuTTy (Software for using Bluetooth connection as COM port)

Serial line:        COM[X] (*)
Connection type:    Serial

(*) on Windows: Device Manager -> Ports (COM and LPT) -> try the listed Bluetooth ports
    HC05's state will change from "Paired" to "Connected" when the correct port is opened in PuTTy
*/

#include <SoftwareSerial.h>

extern SoftwareSerial Blue;

void initBluetooth(bool print_serial = true);
int readBluetooth(char* save_to);
int listenBluetooth(char* save_to);
