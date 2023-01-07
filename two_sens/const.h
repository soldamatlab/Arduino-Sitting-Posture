// Settings

// Arm sensor
// Tolerance ~ 0.25 outside of ok values
#define ARM_X_MID (0.65)
#define ARM_X_LOW (0.4)
#define ARM_X_HIGH (0.4)

#define ARM_Y_MID (1.85)
#define ARM_Y_LOW (0.3)
#define ARM_Y_HIGH (0.3)

#define ARM_Z_MID (0.85)
#define ARM_Z_LOW (0.3)
#define ARM_Z_HIGH (0.3)

// Leg senzor
#define LEG_X_MID (0.32)
#define LEG_X_LOW (0.27)
#define LEG_X_HIGH (0.27)

#define LEG_Y_MID (1.9)
#define LEG_Y_LOW (0.3)
#define LEG_Y_HIGH (0.3)

#define LEG_Z_MID (-0.5)
#define LEG_Z_LOW (0.25)
#define LEG_Z_HIGH (0.25)

// Neck senzor
// sETTINGS FOR NOTEBOOK
#define NECK_X_MID (0.6)
#define NECK_X_LOW (0.25)
#define NECK_X_HIGH (0.25)

#define NECK_Y_MID (-1)
#define NECK_Y_LOW (0.25)
#define NECK_Y_HIGH (0.25)

#define NECK_Z_MID (-1.5)
#define NECK_Z_LOW (0.25)
#define NECK_Z_HIGH (0.25)

// HC-05 Bluetooth module settings
#define BT_NAME ("HC-05")
#define BT_PASS ("1234")

#define BT_MAX_INCOMING_MSG_LENGTH (1)

// Bluetooth commands
#define BT_OFF '0'
#define BT_ON '1'
#define BT_RESET_SENS_VALUES 'r'
#define BT_MUTE_BUZZER 'm'

// Architecture
#define N_SENSORS (3)
#define N_AXIS (3)

#define SENSOR_ARM_PIN (5)
#define SENSOR_LEG_PIN (6)
#define SENSOR_NECK_PIN (7)

#define BTTX (9) // Bluetooth transmit - connect to HC-05 RXD pin via converter
#define BTRX (8) // Bluetooth recieve - connect to HC-05 TXD pin via converter

#define BUTTON_PIN (12)
#define BUTTON_MODE (INPUT_PULLUP)

#define LED (13)
#define BUZZER (4)

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

// Algorithm
#define SENSOR_ARM_IDX (0)
#define SENSOR_LEG_IDX (1)
#define SENSOR_NECK_IDX (2)

#define AXIS_X_IDX (0)
#define AXIS_Y_IDX (1)
#define AXIS_Z_IDX (2)

// Numerical constants
#define ACC_CONSTANT (8192.0)
#define N_ITERATIONS (20)

#define ON_DELAY (250) // [ms]
#define OFF_DELAY (50) // [ms]
