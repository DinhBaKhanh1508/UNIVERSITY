#include "lib.h"


int main() {
	string tempMap[50][50] =
	  { {"","","","","","","","","",""},
		{"","","","","","","","","",""},
		{"","","","","","","","","",""},
		{"","","","","","","","","",""},
		{"","","","S","S","S","S","","",""},
		{"","","","","","O","","","",""},
		{"","","","","","","","","",""},
		{"","","","","","","","","",""},
		{"","","","","","","","","",""},
		{"","","","","","","","","",""}, };

	int r = 10;
	int c = 10;
	string** Map = new string * [r];
	for (int i = 0; i < r; i++) {
		Map[i] = new string[c];
		for (int j = 0; j < c; j++) {
			Map[i][j] = tempMap[i][j];
		}
	}
	gameMap gMap(Map, r, c);
	Game a(gMap);
	zodiac* k = new ox("H1", point(1, 3));
	zodiac* k2 = new rooster("B2", point(2, 4));
	zodiac* a2 = new dragon("R3", point(1, 1));
	zodiac* k3 = new monkey("M4", point(9, 9));
	zodiac* k4 = new boar("B3", point(8, 7));

	a.addZo(k);
	a.addZo(k2);
	a.addZo(a2);
	a.addZo(k3);
	a.addZo(k4);

	a.startGame(point(4,4), 1);
}