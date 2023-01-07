#include "const.h"

// Global vars
// TODO use constants instead of literals


float g[N_SENSORS][N_AXIS][N_ITERATIONS];  // [osy] = [3] (xyz), [hodnoty] = [20] (hodnoty za 5s merene jednou za 250ms 20k/250)
int last_value = 0;         // last_value je ukazatel na pole
float thresholds[N_SENSORS][N_AXIS][2];     // [osy] = [3] (xyz), [hodnoty] = [2] (spdni mez a horni mez)
// end globalni promenne

float average(int sensor, int axis) {
    /*
     * Funkce zprumeruje danou osu a vrati vyseledek.
     */
    float s = 0;
    for (int i = 0; i < N_ITERATIONS; i++) {
        s += g[sensor][axis][i];
    }
    return s / N_ITERATIONS;
}

bool checkPosition() {
    /*
     * Function iterates through all rows of accelerations.
     * If any average lies outside of thrs, returns false.
     * If all averages are accepted by thresholding, returns true.
     */

    for (int sensor = 0; sensor < N_SENSORS; ++sensor) {
      for (int axis = 0; axis < N_AXIS; axis++) {
          float curr_av = average(sensor, axis);
          if ((curr_av < thresholds[sensor][axis][0]) || (curr_av > thresholds[sensor][axis][1])) return false;
      }
    }
    return true;
}

void initAveraging() {
    initThresholds();
    resetValues();
}

void initThresholds() {
    /*
     * Function links thresholds from const.h to global var thresholds used in function check positions.
     */
    // Prepsat tyhle random hodnoty na nejake realne
    thresholds[SENSOR_ARM_IDX][AXIS_X_IDX][0] = ARM_X_MID - ARM_X_LOW;
    thresholds[SENSOR_ARM_IDX][AXIS_X_IDX][1] = ARM_X_MID + ARM_X_HIGH;
    thresholds[SENSOR_ARM_IDX][AXIS_Y_IDX][0] = ARM_Y_MID - ARM_Y_LOW;
    thresholds[SENSOR_ARM_IDX][AXIS_Y_IDX][1] = ARM_Y_MID + ARM_Y_HIGH;
    thresholds[SENSOR_ARM_IDX][AXIS_Z_IDX][0] = ARM_Z_MID - ARM_Z_LOW;
    thresholds[SENSOR_ARM_IDX][AXIS_Z_IDX][1] = ARM_Z_MID + ARM_Z_HIGH;
// sensor 2 - ten naplacato
    thresholds[SENSOR_LEG_IDX][AXIS_X_IDX][0] = LEG_X_MID - LEG_X_LOW;
    thresholds[SENSOR_LEG_IDX][AXIS_X_IDX][1] = LEG_X_MID + LEG_X_HIGH;
    thresholds[SENSOR_LEG_IDX][AXIS_Y_IDX][0] = LEG_Y_MID - LEG_Y_LOW;
    thresholds[SENSOR_LEG_IDX][AXIS_Y_IDX][1] = LEG_Y_MID + LEG_Y_HIGH;
    thresholds[SENSOR_LEG_IDX][AXIS_Z_IDX][0] = LEG_Z_MID - LEG_Z_LOW;
    thresholds[SENSOR_LEG_IDX][AXIS_Z_IDX][1] = LEG_Z_MID + LEG_Z_HIGH;

// sensor 3 - ten co je navolno
    thresholds[SENSOR_NECK_IDX][AXIS_X_IDX][0] = NECK_X_MID - NECK_X_LOW;
    thresholds[SENSOR_NECK_IDX][AXIS_X_IDX][1] = NECK_X_MID + NECK_X_HIGH;
    thresholds[SENSOR_NECK_IDX][AXIS_Y_IDX][0] = NECK_Y_MID - NECK_Y_LOW;
    thresholds[SENSOR_NECK_IDX][AXIS_Y_IDX][1] = NECK_Y_MID + NECK_Y_HIGH;
    thresholds[SENSOR_NECK_IDX][AXIS_Z_IDX][0] = NECK_Z_MID - NECK_Z_LOW;
    thresholds[SENSOR_NECK_IDX][AXIS_Z_IDX][1] = NECK_Z_MID + NECK_Z_HIGH;

}

void updateValues(float *values, int sensor) {
    /*
     * Function rewrites values in stack of iterations.
     */
    // Prepsat gx, gy, gz na values ze senzoru.
    g[sensor][0][last_value] = values[0];
    g[sensor][1][last_value] = values[1];
    g[sensor][2][last_value] = values[2];
    last_value++;
    if (last_value == 20) last_value = 0;
}

void resetValues() {
    setValues(SENSOR_ARM_IDX, AXIS_X_IDX, ARM_X_MID);
    setValues(SENSOR_ARM_IDX, AXIS_Y_IDX, ARM_Y_MID);
    setValues(SENSOR_ARM_IDX, AXIS_Z_IDX, ARM_Z_MID);

    setValues(SENSOR_LEG_IDX, AXIS_X_IDX, LEG_X_MID);
    setValues(SENSOR_LEG_IDX, AXIS_Y_IDX, LEG_Y_MID);
    setValues(SENSOR_LEG_IDX, AXIS_Z_IDX, LEG_Z_MID);

    setValues(SENSOR_NECK_IDX, AXIS_X_IDX, NECK_X_MID);
    setValues(SENSOR_NECK_IDX, AXIS_Y_IDX, NECK_Y_MID);
    setValues(SENSOR_NECK_IDX, AXIS_Z_IDX, NECK_Z_MID);
}

void setValues(int sensor, int axis, float value) {
    for (int iter = 0; iter < N_ITERATIONS; ++iter) {
        g[sensor][axis][iter] = value;
    }
}
