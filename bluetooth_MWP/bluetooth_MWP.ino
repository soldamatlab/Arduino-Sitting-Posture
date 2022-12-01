// Tutorial: https://create.arduino.cc/projecthub/electropeak/getting-started-with-hc-05-bluetooth-module-arduino-e0ca81

#include <SoftwareSerial.h>

#define TX (9)
#define RX (8)
#define LED (13)

SoftwareSerial Blue(RX, TX);
char btChar;
bool btAvailable = false;

void setup() {
    Serial.begin(9600);
    Blue.begin(9600);
    // Blue.begin(38400);  // Baud Rate for AT-command Mode.
    Serial.println("The BlueTooth name is 'HC-05'\nDefualt password is '1234'");
    Blue.println("Connection estabilished");

    pinMode(LED, OUTPUT);

    // delay(20);
}

void loop() {
    // from bluetooth to Terminal.
    if (Blue.available()) {
        btChar = Blue.read();
        Serial.print("Recieved char: ");
        Serial.println(btChar);

        if (btChar == '1') {
            digitalWrite(LED, HIGH);
            Serial.println("LED On");
        } else if (btChar == '0') {
            digitalWrite(LED, LOW);
            Serial.println("LED Off");
        }
    }

    // from termial to bluetooth
    if (Serial.available()) {
        Blue.write(Serial.read());
    }
}
