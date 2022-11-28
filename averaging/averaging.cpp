#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>

using namespace std;
using namespace std::chrono;

// jak casto se to pocita a pridava do pole
int delay = 250;

// pole hodnot 3 osy, 20 = 5000/250 hodnot
float g[3][20];
float thresholds[3][2];

// hodnoty zrychleni a thr
float gx = 0, gy = 0, gz = 0;

void print();
float average(int axis);
int check_position();
int main()
{

	// timer, nahradi se millis()
	auto start = high_resolution_clock::now();
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);

	//thresholdy
	thresholds[0][0] = -15.;
	thresholds[0][1] = 15.;
	thresholds[1][0] = -5.;
	thresholds[1][1] = 5.;
	thresholds[2][0] = -2.;
	thresholds[2][1] = 2.;

	// ukazatel na osu, ktera je spatne, -1 je korektni stav = vsechny spravne
	int position_not_ok = -1;
	
	// ukazatel na pozici v poli
	int	last_value = 0;
	
	do {
		// duration.count() mi rika kolik milisekund ubehlo
		stop = high_resolution_clock::now();
		duration = duration_cast<milliseconds>(stop - start);
		
		// nejaky random pricitani
		gx += 0.000001;
		gy += 0.000005;
		gz -= 0.000005;

		// TODO: ukladani cisel do nejaky fronty, nebo tak, z ktery se to bude prumerovat
		//		 budu ukladat treba 4-5x za sekundu
		if (duration.count() % delay == 0) {
			cout << duration.count() << "\n";

			g[0][last_value] = gx;
			g[1][last_value] = gy;
			g[2][last_value] = gz;
			last_value++;
			if (last_value == 5000 / delay) {
				last_value = 0;
			}

			// to potrebuju aby mi while chvili spal, na arduino smazat
			this_thread::sleep_for(milliseconds(5));
		
		}

		// TODO: prumerovani poslednich 5s
		// TODO: if prumerovani za poslednich 5s > thrs => cout neco
		if (duration.count() % 250 == 0) {
			//print();
			position_not_ok = check_position();
		}
	
	} while (duration.count() < 2500);


}

void print() {
/*
* Informativni
* Funkce mi vytiskne pole, informativni.
*/
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5000 / delay; j++) {
			cout << g[i][j] << " ";
		}
		cout << "\n";
	}
}

float average(int axis) {
/*
* Funkce zprumeruje danou osu a vrati vyseledek.
*/
	float s = 0;
	for (int i = 0; i < 5000 / delay; i++) {
		s += g[axis][i];
	}
	return s / float(5000/delay);
}

int check_position() {
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
			cout << "Position on " << axes[i] << " OK!\n";
		}
		else {
			cout << "Change position on " << axes[i] << " axis!\n";
			return i;
		}
	}
	return -1;
}