#include "const.h"

// Global vars
// TODO use constants instead of literals


float g[N_SENSORS][N_SENSOR_VALUES][ITERATIONS];  // [osy] = [3] (xyz), [hodnoty] = [20] (hodnoty za 5s merene jednou za 250ms 20k/250)
int last_value = 0;         // last_value je ukazatel na pole
float thresholds[N_SENSORS][3][2];     // [osy] = [3] (xyz), [hodnoty] = [2] (spdni mez a horni mez)
// end globalni promenne

float average(int sensor, int axis) {
    /*
     * Funkce zprumeruje danou osu a vrati vyseledek.
     */
    float s = 0;
    for (int i = 0; i < ITERATIONS; i++) {
        s += g[sensor][axis][i];
    }
    return s / ITERATIONS;
}

bool checkPosition() {
    /*
     * Function iterates through all rows of accelerations.
     * If any average lies outside of thrs, returns false.
     * 	+ Outputs Error message.
     * If all averages are accepted by thresholding, returns true.
     */

    for (int sensor = 0; sensor < N_SENSORS; ++sensor) {
      for (int i = 0; i < 3; i++) {
          float curr_av = average(sensor, i);
          if (curr_av < thresholds[sensor][i][0] || curr_av > thresholds[sensor][i][1]) {
            return false;
          }
      }
    }
    return true;
}

void initThresholds() {
    /*
     * Function links thresholds from const.h to global var thresholds used in function check positions.
     */
    // Prepsat tyhle random hodnoty na nejake realne
    thresholds[0][0][0] = HAND_X_MID - HAND_X_LOW;
    thresholds[0][0][1] = HAND_X_MID + HAND_X_HIGH;
    thresholds[0][1][0] = HAND_Y_MID - HAND_Y_LOW;
    thresholds[0][1][1] = HAND_Y_MID + HAND_Y_HIGH;
    thresholds[0][2][0] = HAND_Z_MID - HAND_Z_LOW;
    thresholds[0][2][1] = HAND_Z_MID + HAND_Z_HIGH;
// sensor 2 - ten naplacato
    thresholds[1][0][0] = LEG_X_MID - LEG_X_LOW;
    thresholds[1][0][1] = LEG_X_MID + LEG_X_HIGH;
    thresholds[1][1][0] = LEG_Y_MID - LEG_Y_LOW;
    thresholds[1][1][1] = LEG_Y_MID + LEG_Y_HIGH;
    thresholds[1][2][0] = LEG_Z_MID - LEG_Z_LOW;
    thresholds[1][2][1] = LEG_Z_MID + LEG_Z_HIGH;

// sensor 3 - ten co je navolno
    thresholds[2][0][0] = NECK_X_MID - NECK_X_LOW;
    thresholds[2][0][1] = NECK_X_MID + NECK_X_HIGH;
    thresholds[2][1][0] = NECK_Y_MID - NECK_Y_LOW;
    thresholds[2][1][1] = NECK_Y_MID + NECK_Y_HIGH;
    thresholds[2][2][0] = NECK_Z_MID - NECK_Z_LOW;
    thresholds[2][2][1] = NECK_Z_MID + NECK_Z_HIGH;

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
    if (last_value == 20) {
        last_value = 0;
    }
}
