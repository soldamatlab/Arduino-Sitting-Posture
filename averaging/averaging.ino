/*
* Definice globalnich promennych
*/
// Pole zrychleni
// [osy] = [3] (xyz), [hodnoty] = [20] (hodnoty za 5s merene jednou za 250ms)
// last_value je ukazatel na pole
float g[3][20];
int	last_value = 0;

// [osy] = [3] (xyz), [hodnoty] = [2] (spdni mez a horni mez)
float thresholds[3][2];

// zrychleni v x,y,z
float gx = 0, gy = 0, gz = 0;

// checker spravne pozice
bool position_ok = true;

float average(int axis);
bool check_position();
  
void setup() {
  // Nastavit thresholdy pro porovnani - vyzkousime
  thresholds[0][0] = -15.;
  thresholds[0][1] = 15.;
  thresholds[1][0] = -5.;
  thresholds[1][1] = 5.;
  thresholds[2][0] = -2.;
  thresholds[2][1] = 2.;
}

void loop() {
  // nejaka random iterace gcek
	gx += 0.000001;
	gy += 0.000005;
  gz -= 0.000005;

  // takhle se prepisuje pole   
	g[0][last_value] = gx;
	g[1][last_value] = gy;
	g[2][last_value] = gz;
	last_value++;
  // pokud lastvalue dojde na konec, skocim s nim na prvni pozici
	if (last_value == 20) {
	  last_value = 0;
	}
  
  // kontrola vsech os, jestli splnuji nejaky thrs
  position_ok = check_position();  
  if(!position_ok){
    printf("Change position!");
  }

  delay(250);  

}

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
* Funkce projde vsechny radky pole a zkontroluje jestli prumer kazdeho radku lezi v thrs.
* Pokud prumer nejakeho radku lezi mimo, vrati [0,1,2] podle osy, ktera je spatne [x,y,z].
* 	+ chybove hlaseni
* Pokud vsechny prumery odpovidaji thrs, vrati -1.
*/
	char axes[4] = "xyz";
	for (int i = 0; i < 3; i++) {
		float curr_av = average(i);
		//cout << curr_av << " ";

		if (curr_av > thresholds[i][0] && curr_av < thresholds[i][1]) {
			//cout << "Position on " << axes[i] << " OK!\n";
		}
		else {
			//cout << "Change position on " << axes[i] << " axis!\n";
			return false;
		}
	}
	return true;
}