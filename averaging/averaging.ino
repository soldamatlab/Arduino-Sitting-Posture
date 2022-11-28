/*
* Howto: do mainu
// global
  bool position_ok = true;
  
  iteration(); // Changes values in the stack of accelerations.
  position_ok = check_position(); // Checks all axes.
*/

// Global vars
float g[3][20]; // [osy] = [3] (xyz), [hodnoty] = [20] (hodnoty za 5s merene jednou za 250ms 20k/250)
int	last_value = 0; // last_value je ukazatel na pole
float thresholds[3][2]; // [osy] = [3] (xyz), [hodnoty] = [2] (spdni mez a horni mez)
//end globalni promenne

// Funkce:
float average(int axis);
bool check_position();
void init_thresholds();
void iteration();
//end funkce

float average(int axis) {
/*
* Funkce zprumeruje danou osu a vrati vyseledek.
*/
	float s = 0;
	for (int i = 0; i < 20; i++) {
		s += g[axis][i];
	}
	return s / 20.;
}

bool check_position() {
/*
* Function iterates through all rows of accelerations.
* If any average lies outside of thrs, returns false.
* 	+ Outputs Error message.
* If all averages are accepted by thresholding, returns true.
*/
	char axes[4] = "xyz";
	for (int i = 0; i < 3; i++) {
		float curr_av = average(i);
		
    Serial.println();
		if (curr_av > thresholds[i][0] && curr_av < thresholds[i][1]) {
			Serial.print("Position on axis ");
      Serial.print(axes[i]);
      Serial.print("OK!");       
		}
		else {
			Serial.print("Change position on ");
      Serial.print(axes[i]);
      Serial.print(" axis!");
			return false;
		}
	}
	return true;
}

void init_thresholds(){
/*
* Function links thresholds from const.h to global var thresholds used in function check positions.
*/  
Prepsat tyhle random hodnoty na nejake realne
  thresholds[0][0] = -15.;
  thresholds[0][1] = 15.;
  thresholds[1][0] = -5.;
  thresholds[1][1] = 5.;
  thresholds[2][0] = -2.;
  thresholds[2][1] = 2.;  
}

void iteration(){
/*
* Function rewrites values in stack of iterations.
*/
Prepsat gx, gy, gz na values ze senzoru.
	g[0][last_value] = gx;
	g[1][last_value] = gy;
	g[2][last_value] = gz;
	last_value++;
  if (last_value == 20) {
	  last_value = 0;
	}  
}
