// Settings
#define X_MID (-0.1)
#define X_LOW (0.35)
#define X_HIGH (0.35)

#define Y_MID (-0.1)
#define Y_LOW (0.35)
#define Y_HIGH (0.35)

#define Z_MID (2.2)
#define Z_LOW (100)
#define Z_HIGH (100)

// HC-05 Bluetooth module settings
#define BT_NAME ("HC-05")
#define BT_PASS ("1234")

#define BT_MSG_MAX_LENGTH (1)

// Architecture
#define N_SENSORS (2)        // later 3
#define N_SENSOR_VALUES (3)  // later 6

#define BUTTON_PIN (12)
#define BUTTON_MODE (INPUT_PULLUP)

#define SENSOR_PIN_0 (5)
#define SENSOR_PIN_1 (6)
#define SENSOR_PIN_2 (7)

#define BTTX (9) // Bluetooth transmit - connect to HC-05 RXD pin via converter
#define BTRX (8) // Bluetooth recieve - connect to HC-05 TXD pin via converter

#define LED (13)

// Sensor addresses
#define MPU_ADDR_0 (0x68)  // I2C address of the first MPU-6050
//#define MPU_ADDR_1 (0x69)  // I2C address of the second MPU-6050

// Registers
#define PWR_MGMT_1 (0x6B)  // PWR_MGMT_1 register

#define ACCEL_CONFIG (0x1C)  // set accelerometer range here with one of the following values
#define AFS_SEL_2G (0x00)    // +/- 2G
#define AFS_SEL_4G (0x08)    // +/- 4G
#define AFS_SEL_8G (0x10)    // +/- 8G
#define AFS_SEL_16G (0x18)   // +/- 16G

#define ACCEL_XOUT_H (0x3B)
#define ACCEL_XOUT_L (0x3C)
#define ACCEL_YOUT_H (0x3D)
#define ACCEL_YOUT_L (0x3E)
#define ACCEL_ZOUT_H (0x3F)
#define ACCEL_ZOUT_L (0x40)

// Numerical constants
#define ACC_CONSTANT (8192.0)
#define ITERATIONS (20)
