#include "lib.h"


// CLASS GAMEMAP
gameMap::gameMap() { col = 0; row = 0; mapMat = nullptr; }
gameMap::gameMap(string** inputMat, int r, int c) {
	row = r;
	col = c;
	mapMat = new string * [r];
	for (int i = 0; i < r; i++) {
		mapMat[i] = new string[c];
		for (int j = 0; j < c; j++) {
			mapMat[i][j] = inputMat[i][j];
		}
	}

}
void gameMap::printMap() {
	bool check = false;
	int r1 = 0, c1 = 0;
	cout << ' ' << setfill('_');
	cout << setw(8 * this->col - 1) << '_' << endl;
	cout << setfill(' ');
	for (int i = 0; i < 2 * this->row; i++) {
		if (i % 2 == 0) {
			for (int c = 0; c < this->col - 1; c++) {
				if (mapMat[r1][c].size() > 6) {
					check = true;
				}
			}
			if (check == true) {
				for (int j = 0; j < this->col + 1; j++) {
					if (j != this->col) {
						if (mapMat[r1][c1].size() > 6) {
							string a(mapMat[r1][c1], 0, 5);
							cout << '|' << a << "_ ";
							c1++;
						}
						else {
							cout << "|" << this->mapMat[r1][c1] << setw(8 - this->mapMat[r1][c1].size());
							c1++;
						}
					}
					else {
						cout << '|' << endl;
						c1 = 0;
					}
				}
				for (int j = 0; j < this->col + 1; j++) {
					if (j != this->col) {
						if (mapMat[r1][c1].size() > 6) {
							string a(mapMat[r1][c1], 5, mapMat[r1][c1].size() - 5);
							cout << '|' << a << setw(8 - a.size());
							c1++;
						}
						else {
							cout << "|" << setw(8);
							c1++;
						}

					}
					else {
						cout << '|' << endl;
						c1 = 0;
						r1++;
					}
				}

			}
			else {
				for (int j = 0; j < this->col + 1; j++) {
					if (j != this->col) {
						cout << "|" << this->mapMat[r1][c1] << setw(8 - this->mapMat[r1][c1].size());
						c1++;
					}
					else {
						cout << "|" << endl;
						r1++;
						c1 = 0;
					}
				}
			}
		}
		else {
			for (int j = 0; j < this->col + 1; j++) {
				if (j != this->col) cout << "|" << "_______";
				else cout << "|" << endl;
			}
		}
		check = false;
	}
}
gameMap::~gameMap() {}
string*&  gameMap:: operator[](int i) {
	return mapMat[i];
}


// CLASS POINT
point::point() {
	this->x = 0;
	this->y = 0;
}
point::point(int x, int y) {
	this->x = x;
	this->y = y;
}


//CLASS ZODIAC
string newStr(string str, string ID) {
	string newVe = str;
	size_t pos = newVe.find(ID);

	if (pos != string::npos) {
		newVe.erase(pos, ID.length());
	}

	return newVe;
}
zodiac::zodiac(string ID, point location) {
	this->ID = ID;
	this->location.x = location.x;
	this->location.y = location.y;
	this->status = "";

}
void zodiac:: printInfo() {
	cout << "zodiac " << ID << " at (" << location.x << "," << location.y << ")" << endl;
}
void zodiac:: move(point loc, gameMap mapMat) {}
zodiac:: ~zodiac() {}

//RAT
rat::rat(string ID, point location) : zodiac(ID, location) {}
void rat:: printInfo() {
	cout << "rat " << ID << " at (" << location.x << "," << location.y << ")" << endl;
}
void rat::move(point loc, gameMap mapMat) {
	int horz = abs(location.y - loc.y);
	int vert = abs(location.x - loc.x);
	if (horz >= vert) {
		int movH;
		(loc.y > location.y) ? movH = 1 : movH = -1;
		int movV;
		(loc.x > location.x) ? movV = 1 : movV = -1;
		size_t checkStoneH = mapMat[location.x][location.y + movH].find("S");
		size_t checkWaterH = mapMat[location.x][location.y + movH].find("W");

		size_t checkStoneV = mapMat[location.x + movV][location.y].find("S");
		size_t checkWaterV = mapMat[location.x + movV][location.y].find("W");

		if (checkStoneH != string::npos || checkWaterH != string::npos) {
			if (checkStoneV != string::npos || checkWaterV != string::npos) {
				this->status = "Stuck";
			}
			else {
				mapMat[location.x + movV][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "rat " << ID << " at (" << location.x + movV << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x = location.x + movV;
			}
		}
		else {
			mapMat[location.x][location.y + movH] += this->ID;
			mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
			cout << "rat " << ID << " at (" << location.x << "," << location.y + movH << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
			location.y = location.y + movH;
		}
	}
	else {
		int movH;
		(loc.y > location.y) ? movH = 1 : movH = -1;
		int movV;
		(loc.x > location.x) ? movV = 1 : movV = -1;
		size_t checkStoneH = mapMat[location.x][location.y + movH].find("S");
		size_t checkWaterH = mapMat[location.x][location.y + movH].find("W");

		size_t checkStoneV = mapMat[location.x + movV][location.y].find("S");
		size_t checkWaterV = mapMat[location.x + movV][location.y].find("W");

		if (checkStoneV != string::npos || checkWaterV != string::npos) {
			if (checkStoneH != string::npos || checkWaterH != string::npos) {
				this->status = "Stuck";
			}
			else {
				mapMat[location.x][location.y + movH] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "rat " << ID << " at (" << location.x << "," << location.y + movH << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y = location.y + movH;
			}
		}
		else {
			mapMat[location.x + movV][location.y] += this->ID;
			mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
			cout << "rat " << ID << " at (" << location.x + movV << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
			location.x = location.x + movV;
		}
	}
}

//OX
ox::ox(string ID, point location) : zodiac(ID, location) {}
void ox::printInfo() {
	cout << "ox " << ID << " at (" << location.x << "," << location.y << ")" << endl;
}
void ox::move(point loc, gameMap mapMat) {
	size_t stone = mapMat[location.x][location.y].find("S");
	size_t water = mapMat[location.x][location.y].find("W");
	if (stone != string::npos) {
		int horz = abs(location.y - loc.y);
		int vert = abs(location.x - loc.x);
		mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], "S");
		if (horz >= vert) {
			if (loc.y > location.y) {
				int mov;
				abs(loc.y - location.y) == 1 ? mov = 1 : mov = 2;
				mapMat[location.x][location.y + 1] = newStr(mapMat[location.x][location.y + 1], "S");
				mapMat[location.x][location.y + mov] = newStr(mapMat[location.x][location.y + mov], "S");
				mapMat[location.x][location.y + mov] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "ox " << ID << " at (" << location.x << "," << location.y + mov << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y = location.y + mov;
			}
			else if (loc.y < location.y) {
				int mov;
				abs(loc.y - location.y) == 1 ? mov = 1 : mov = 2;
				mapMat[location.x][location.y - 1] = newStr(mapMat[location.x][location.y - 1], "S");
				mapMat[location.x][location.y - mov] = newStr(mapMat[location.x][location.y - mov], "S");
				mapMat[location.x][location.y - mov] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "ox " << ID << " at (" << location.x << "," << location.y - mov << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y = location.y - mov;
			}
		}
		else {
			if (loc.x > location.x) {
				int mov;
				abs(loc.x - location.x) == 1 ? mov = 1 : mov = 2;
				mapMat[location.x + 1][location.y] = newStr(mapMat[location.x + 1][location.y], "S");
				mapMat[location.x + mov][location.y] = newStr(mapMat[location.x + mov][location.y], "S");
				mapMat[location.x + mov][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "ox " << ID << " at (" << location.x + mov << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x = location.x + mov;
			}
			else if (loc.x < location.x) {
				int mov;
				abs(loc.x - location.x) == 1 ? mov = 1 : mov = 2;
				mapMat[location.x - 1][location.y] = newStr(mapMat[location.x - 1][location.y], "S");
				mapMat[location.x - mov][location.y] = newStr(mapMat[location.x - mov][location.y], "S");
				mapMat[location.x - mov][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "ox " << ID << " at (" << location.x - mov << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x = location.x - mov;
			}
		}
	}
	else if (water != string::npos) {
		int horz = abs(location.y - loc.y);
		int vert = abs(location.x - loc.x);

		if (horz >= vert) {
			if (loc.y > location.y) {
				int mov;
				abs(loc.y - location.y) == 1 ? mov = 1 : abs(loc.y - location.y) == 2 ? mov = 2 : mov = 3;
				for (int i = 1; i < mov; i++) {
					mapMat[location.x][location.y + i] = newStr(mapMat[location.x][location.y + i], "S");
				}
				mapMat[location.x][location.y + mov] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "ox " << ID << " at (" << location.x << "," << location.y + mov << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y = location.y + mov;
			}
			else if (loc.y < location.y) {
				int mov;
				abs(loc.y - location.y) == 1 ? mov = 1 : abs(loc.y - location.y) == 2 ? mov = 2 : mov = 3;
				for (int i = 1; i < mov; i++) {
					mapMat[location.x][location.y - i] = newStr(mapMat[location.x][location.y - i], "S");
				}
				mapMat[location.x][location.y - mov] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "ox " << ID << " at (" << location.x << "," << location.y - mov << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y = location.y - mov;
			}
		}
		else {
			if (loc.x > location.x) {
				int mov;
				abs(loc.x - location.x) == 1 ? mov = 1 : abs(loc.x - location.x) == 2 ? mov = 2 : mov = 3;
				for (int i = 1; i < mov; i++) {
					mapMat[location.x + i][location.y] = newStr(mapMat[location.x + i][location.y], "S");
				}
				mapMat[location.x + mov][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "ox " << ID << " at (" << location.x + mov << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x = location.x + mov;
			}
			else if (loc.x < location.x) {
				int mov;
				abs(loc.x - location.x) == 1 ? mov = 1 : abs(loc.x - location.x) == 2 ? mov = 2 : mov = 3;
				for (int i = 1; i < mov; i++) {
					mapMat[location.x - i][location.y] = newStr(mapMat[location.x - i][location.y], "S");
				}
				mapMat[location.x - mov][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "ox " << ID << " at (" << location.x - mov << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x = location.x - mov;
			}
		}
	}
	else {
		int horz = abs(location.y - loc.y);
		int vert = abs(location.x - loc.x);

		if (horz >= vert) {
			if (loc.y > location.y) {
				int mov;
				abs(loc.y - location.y) == 1 ? mov = 1 : mov = 2;
				for (int i = 1; i < mov; i++) {
					mapMat[location.x][location.y + i] = newStr(mapMat[location.x][location.y + i], "S");
				}
				mapMat[location.x][location.y + mov] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "ox " << ID << " at (" << location.x << "," << location.y + mov << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y = location.y + mov;
			}
			else if (loc.y < location.y) {
				int mov;
				abs(loc.y - location.y) == 1 ? mov = 1 : mov = 2;
				for (int i = 1; i < mov; i++) {
					mapMat[location.x][location.y - i] = newStr(mapMat[location.x][location.y - i], "S");
				}
				mapMat[location.x][location.y - mov] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "ox " << ID << " at (" << location.x << "," << location.y - mov << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y = location.y - mov;
			}
		}
		else {
			if (loc.x > location.x) {
				int mov;
				abs(loc.x - location.x) == 1 ? mov = 1 : mov = 2;
				for (int i = 1; i < mov; i++) {
					mapMat[location.x + i][location.y] = newStr(mapMat[location.x + i][location.y], "S");
				}
				mapMat[location.x + mov][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "ox " << ID << " at (" << location.x + mov << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x = location.x + mov;
			}
			else if (loc.x < location.x) {
				int mov;
				abs(loc.x - location.x) == 1 ? mov = 1 : mov = 2;
				for (int i = 1; i < mov; i++) {
					mapMat[location.x - i][location.y] = newStr(mapMat[location.x - i][location.y], "S");
				}
				mapMat[location.x - mov][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "ox " << ID << " at (" << location.x - mov << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x = location.x - mov;
			}
		}
	}

}

//TIGER
tiger::tiger(string ID, point location) : zodiac(ID, location) {}
void tiger::printInfo() {
	cout << "tiger " << ID << " at (" << location.x << "," << location.y << ")" << endl;
}
void tiger:: move(point loc, gameMap mapMat){
			int horz = abs(location.y - loc.y);
			int vert = abs(location.x - loc.x);

			if (vert == 0 && horz != 0) {
				int movH;
				(abs(loc.y - location.y) == 1) ? movH = 1 : movH = 2;
				(loc.y > location.y) ? movH *= 1 : movH *= (-1);

				size_t checkStoneH = mapMat[location.x][location.y + movH].find("S");
				size_t checkWaterH = mapMat[location.x][location.y + movH].find("W");

				((movH == 2) && ((checkStoneH != string::npos || checkWaterH != string::npos) && (mapMat[location.x][location.y + 1].find("S") == string::npos || mapMat[location.x][location.y + 1].find("W") == string::npos))) ? movH *= 0.5 : movH = movH;
				((movH == -2) && ((checkStoneH != string::npos || checkWaterH != string::npos) && (mapMat[location.x][location.y - 1].find("S") == string::npos || mapMat[location.x][location.y - 1].find("W") == string::npos))) ? movH *= 0.5 : movH = movH;

				if (movH > 0 && (mapMat[location.x][location.y + 1].find("W") != string::npos || mapMat[location.x][location.y + 1].find("S") != string::npos)) {
					if (loc.x == 0) {
						mapMat[location.x + 1][location.y] += this->ID;
						mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
						cout << "tiger " << ID << " at (" << location.x + 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
						location.x += 1;
					}
					else if (loc.x == mapMat.row - 1) {
						mapMat[location.x - 1][location.y] += this->ID;
						mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
						cout << "tiger " << ID << " at (" << location.x - 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
						location.x -= 1;
					}
					else {
						mapMat[location.x + 1][location.y] += this->ID;
						mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
						cout << "tiger " << ID << " at (" << location.x + 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
						location.x += 1;
					}
				}
				else if (movH < 0 && (mapMat[location.x][location.y - 1].find("W") != string::npos || mapMat[location.x][location.y - 1].find("S") != string::npos)) {
					if (loc.x == 0) {
						mapMat[location.x + 1][location.y] += this->ID;
						mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
						cout << "tiger " << ID << " at (" << location.x + 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
						location.x += 1;
					}
					else if (loc.x == mapMat.row - 1) {
						mapMat[location.x - 1][location.y] += this->ID;
						mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
						cout << "tiger " << ID << " at (" << location.x - 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
						location.x -= 1;
					}
					else {
						mapMat[location.x + 1][location.y] += this->ID;
						mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
						cout << "tiger " << ID << " at (" << location.x + 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
						location.x += 1;
					}
				}
				else {
					mapMat[location.x][location.y + movH] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "tiger " << ID << " at (" << location.x << "," << location.y + movH << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.y = location.y + movH;
				}

			}
			else if (horz == 0 && vert != 0) {
				int movV;
				(abs(loc.x - location.x) == 1) ? movV = 1 : movV = 2;
				(loc.x > location.x) ? movV *= 1 : movV *= (-1);

				size_t checkStoneV = mapMat[location.x + movV][location.y].find("S");
				size_t checkWaterV = mapMat[location.x + movV][location.y].find("W");

				((movV == 2) && ((checkStoneV != string::npos || checkWaterV != string::npos) && (mapMat[location.x + 1][location.y].find("S") == string::npos || mapMat[location.x + 1][location.y].find("W") == string::npos))) ? movV *= 0.5 : movV = movV;
				((movV == -2) && ((checkStoneV != string::npos || checkWaterV != string::npos) && (mapMat[location.x - 1][location.y].find("S") == string::npos || mapMat[location.x - 1][location.y].find("W") == string::npos))) ? movV *= 0.5 : movV = movV;


				if (movV > 0 && (mapMat[location.x + 1][location.y].find("W") != string::npos || mapMat[location.x + 1][location.y].find("S") != string::npos)) {
					if (loc.y == 0) {
						mapMat[location.x][location.y + 1] += this->ID;
						mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
						cout << "tiger " << ID << " at (" << location.x << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
						location.y += 1;
					}
					else if (loc.x == mapMat.col - 1) {
						mapMat[location.x][location.y - 1] += this->ID;
						mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
						cout << "tiger " << ID << " at (" << location.x << "," << location.y - 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
						location.y -= 1;
					}
					else {
						mapMat[location.x][location.y + 1] += this->ID;
						mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
						cout << "tiger " << ID << " at (" << location.x << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
						location.y += 1;
					}
				}
				else if (movV < 0 && (mapMat[location.x - 1][location.y].find("W") != string::npos || mapMat[location.x - 1][location.y].find("S") != string::npos)) {
					if (loc.y == 0) {
						mapMat[location.x][location.y + 1] += this->ID;
						mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
						cout << "tiger " << ID << " at (" << location.x << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
						location.y += 1;
					}
					else if (loc.x == mapMat.col - 1) {
						mapMat[location.x][location.y - 1] += this->ID;
						mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
						cout << "tiger " << ID << " at (" << location.x << "," << location.y - 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
						location.y -= 1;
					}
					else {
						mapMat[location.x][location.y + 1] += this->ID;
						mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
						cout << "tiger " << ID << " at (" << location.x << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
						location.y += 1;
					}
				}
				else {
					mapMat[location.x + movV][location.y] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "tiger " << ID << " at (" << location.x + movV << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.x = location.x + movV;
				}
			}
			else if (horz >= vert) {
				int movH;
				(abs(loc.y - location.y) == 1) ? movH = 1 : movH = 2;
				(loc.y > location.y) ? movH *= 1 : movH *= (-1);
				int movV;
				(abs(loc.x - location.x) == 1) ? movV = 1 : movV = 2;
				(loc.x > location.x) ? movV *= 1 : movV *= (-1);
				size_t checkStoneH = mapMat[location.x][location.y + movH].find("S");
				size_t checkWaterH = mapMat[location.x][location.y + movH].find("W");

				size_t checkStoneV = mapMat[location.x + movV][location.y].find("S");
				size_t checkWaterV = mapMat[location.x + movV][location.y].find("W");

				((movH == 2) && (checkStoneH != string::npos || checkWaterH != string::npos || mapMat[location.x][location.y + 1].find("S") != string::npos || mapMat[location.x][location.y + 1].find("W") != string::npos)) ? movH *= 0.5 : movH = movH;
				((movH == -2) && (checkStoneH != string::npos || checkWaterH != string::npos || mapMat[location.x][location.y - 1].find("S") != string::npos || mapMat[location.x][location.y - 1].find("W") != string::npos)) ? movH *= 0.5 : movH = movH;
				((movV == 2) && (checkStoneV != string::npos || checkWaterV != string::npos || mapMat[location.x + 1][location.y].find("S") != string::npos || mapMat[location.x + 1][location.y].find("W") != string::npos)) ? movV *= 0.5 : movV = movV;
				((movV == -2) && (checkStoneV != string::npos || checkWaterV != string::npos || mapMat[location.x - 1][location.y].find("S") != string::npos || mapMat[location.x - 1][location.y].find("W") != string::npos)) ? movV *= 0.5 : movV = movV;


				checkStoneH = mapMat[location.x][location.y + movH].find("S");
				checkWaterH = mapMat[location.x][location.y + movH].find("W");

				checkStoneV = mapMat[location.x + movV][location.y].find("S");
				checkWaterV = mapMat[location.x + movV][location.y].find("W");

				if ((checkStoneH != string::npos || checkWaterH != string::npos) && abs(movH) == 1) {
					if ((checkStoneV != string::npos || checkWaterV != string::npos) && abs(movV) == 1) {
						this->status = "Stuck";
					}
					else {
						mapMat[location.x + movV][location.y] += this->ID;
						mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
						cout << "tiger " << ID << " at (" << location.x + movV << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
						location.x = location.x + movV;
					}
				}
				else {
					mapMat[location.x][location.y + movH] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "tiger " << ID << " at (" << location.x << "," << location.y + movH << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.y = location.y + movH;
				}
			}
			else {
				int movH;
				(abs(loc.y - location.y) == 1) ? movH = 1 : movH = 2;
				(loc.y > location.y) ? movH *= 1 : movH *= (-1);
				int movV;
				(abs(loc.x - location.x) == 1) ? movV = 1 : movV = 2;
				(loc.x > location.x) ? movV *= 1 : movV *= (-1);
				size_t checkStoneH = mapMat[location.x][location.y + movH].find("S");
				size_t checkWaterH = mapMat[location.x][location.y + movH].find("W");

				size_t checkStoneV = mapMat[location.x + movV][location.y].find("S");
				size_t checkWaterV = mapMat[location.x + movV][location.y].find("W");


				((movH == 2) && (checkStoneH != string::npos || checkWaterH != string::npos || mapMat[location.x][location.y + 1].find("S") != string::npos || mapMat[location.x][location.y + 1].find("W") != string::npos)) ? movH *= 0.5 : movH = movH;
				((movH == -2) && (checkStoneH != string::npos || checkWaterH != string::npos || mapMat[location.x][location.y - 1].find("S") != string::npos || mapMat[location.x][location.y - 1].find("W") != string::npos)) ? movH *= 0.5 : movH = movH;
				((movV == 2) && (checkStoneV != string::npos || checkWaterV != string::npos || mapMat[location.x + 1][location.y].find("S") != string::npos || mapMat[location.x + 1][location.y].find("W") != string::npos)) ? movV *= 0.5 : movV = movV;
				((movV == -2) && (checkStoneV != string::npos || checkWaterV != string::npos || mapMat[location.x - 1][location.y].find("S") != string::npos || mapMat[location.x - 1][location.y].find("W") != string::npos)) ? movV *= 0.5 : movV = movV;

				checkStoneH = mapMat[location.x][location.y + movH].find("S");
				checkWaterH = mapMat[location.x][location.y + movH].find("W");

				checkStoneV = mapMat[location.x + movV][location.y].find("S");
				checkWaterV = mapMat[location.x + movV][location.y].find("W");

				if ((checkStoneV != string::npos || checkWaterV != string::npos) && abs(movV) == 1) {
					if ((checkStoneH != string::npos || checkWaterH != string::npos) && abs(movH) == 1) {
						this->status = "Stuck";
					}
					else {
						mapMat[location.x][location.y + movH] += this->ID;
						mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
						cout << "tiger " << ID << " at (" << location.x << "," << location.y + movH << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
						location.y = location.y + movH;
					}
				}
				else {
					mapMat[location.x + movV][location.y] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "tiger " << ID << " at (" << location.x + movV << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.x = location.x + movV;
				}
			}
}

// CAT
cat::cat(string ID, point location) : zodiac(ID, location) {}
void cat:: printInfo() {
	cout << "cat " << ID << " at (" << location.x << "," << location.y << ")" << endl;
}
void cat:: move(point loc, gameMap mapMat) {
	int horz = abs(location.y - loc.y);
	int vert = abs(location.x - loc.x);

	if (vert == 0 && horz != 0) {
		int movH;
		(abs(loc.y - location.y) == 1) ? movH = 1 : movH = 2;
		(loc.y > location.y) ? movH *= 1 : movH *= (-1);

		size_t checkStoneH = mapMat[location.x][location.y + movH].find("S");
		size_t checkWaterH = mapMat[location.x][location.y + movH].find("W");

		((movH == 2) && ((checkStoneH != string::npos || checkWaterH != string::npos) && (mapMat[location.x][location.y + 1].find("S") == string::npos || mapMat[location.x][location.y + 1].find("W") == string::npos))) ? movH *= 0.5 : movH = movH;
		((movH == -2) && ((checkStoneH != string::npos || checkWaterH != string::npos) && (mapMat[location.x][location.y - 1].find("S") == string::npos || mapMat[location.x][location.y - 1].find("W") == string::npos))) ? movH *= 0.5 : movH = movH;

		if (movH > 0 && (mapMat[location.x][location.y + 1].find("W") != string::npos || mapMat[location.x][location.y + 1].find("S") != string::npos)) {
			if (loc.x == 0) {
				mapMat[location.x + 1][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "cat " << ID << " at (" << location.x + 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x += 1;
			}
			else if (loc.x == mapMat.row - 1) {
				mapMat[location.x - 1][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "cat " << ID << " at (" << location.x - 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x -= 1;
			}
			else {
				mapMat[location.x + 1][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "cat " << ID << " at (" << location.x + 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x += 1;
			}
		}
		else if (movH < 0 && (mapMat[location.x][location.y - 1].find("W") != string::npos || mapMat[location.x][location.y - 1].find("S") != string::npos)) {
			if (loc.x == 0) {
				mapMat[location.x + 1][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "cat " << ID << " at (" << location.x + 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x += 1;
			}
			else if (loc.x == mapMat.row - 1) {
				mapMat[location.x - 1][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "cat " << ID << " at (" << location.x - 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x -= 1;
			}
			else {
				mapMat[location.x + 1][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "cat " << ID << " at (" << location.x + 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x += 1;
			}
		}
		else {
			mapMat[location.x][location.y + movH] += this->ID;
			mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
			cout << "cat " << ID << " at (" << location.x << "," << location.y + movH << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
			location.y = location.y + movH;
		}

	}
	else if (horz == 0 && vert != 0) {
		int movV;
		(abs(loc.x - location.x) == 1) ? movV = 1 : movV = 2;
		(loc.x > location.x) ? movV *= 1 : movV *= (-1);

		size_t checkStoneV = mapMat[location.x + movV][location.y].find("S");
		size_t checkWaterV = mapMat[location.x + movV][location.y].find("W");

		((movV == 2) && ((checkStoneV != string::npos || checkWaterV != string::npos) && (mapMat[location.x + 1][location.y].find("S") == string::npos || mapMat[location.x + 1][location.y].find("W") == string::npos))) ? movV *= 0.5 : movV = movV;
		((movV == -2) && ((checkStoneV != string::npos || checkWaterV != string::npos) && (mapMat[location.x - 1][location.y].find("S") == string::npos || mapMat[location.x - 1][location.y].find("W") == string::npos))) ? movV *= 0.5 : movV = movV;


		if (movV > 0 && (mapMat[location.x + 1][location.y].find("W") != string::npos || mapMat[location.x + 1][location.y].find("S") != string::npos)) {
			if (loc.y == 0) {
				mapMat[location.x][location.y + 1] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "cat " << ID << " at (" << location.x << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y += 1;
			}
			else if (loc.x == mapMat.col - 1) {
				mapMat[location.x][location.y - 1] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "cat " << ID << " at (" << location.x << "," << location.y - 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y -= 1;
			}
			else {
				mapMat[location.x][location.y + 1] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "cat " << ID << " at (" << location.x << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y += 1;
			}
		}
		else if (movV < 0 && (mapMat[location.x - 1][location.y].find("W") != string::npos || mapMat[location.x - 1][location.y].find("S") != string::npos)) {
			if (loc.y == 0) {
				mapMat[location.x][location.y + 1] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "cat " << ID << " at (" << location.x << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y += 1;
			}
			else if (loc.x == mapMat.col - 1) {
				mapMat[location.x][location.y - 1] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "cat " << ID << " at (" << location.x << "," << location.y - 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y -= 1;
			}
			else {
				mapMat[location.x][location.y + 1] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "cat " << ID << " at (" << location.x << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y += 1;
			}
		}
		else {
			mapMat[location.x + movV][location.y] += this->ID;
			mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
			cout << "cat " << ID << " at (" << location.x + movV << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
			location.x = location.x + movV;
		}
	}
	else if (horz >= vert) {
		int movH;
		(abs(loc.y - location.y) == 1) ? movH = 1 : movH = 2;
		(loc.y > location.y) ? movH *= 1 : movH *= (-1);
		int movV;
		(abs(loc.x - location.x) == 1) ? movV = 1 : movV = 2;
		(loc.x > location.x) ? movV *= 1 : movV *= (-1);
		size_t checkStoneH = mapMat[location.x][location.y + movH].find("S");
		size_t checkWaterH = mapMat[location.x][location.y + movH].find("W");

		size_t checkStoneV = mapMat[location.x + movV][location.y].find("S");
		size_t checkWaterV = mapMat[location.x + movV][location.y].find("W");

		((movH == 2) && (checkStoneH != string::npos || checkWaterH != string::npos || mapMat[location.x][location.y + 1].find("S") != string::npos || mapMat[location.x][location.y + 1].find("W") != string::npos)) ? movH *= 0.5 : movH = movH;
		((movH == -2) && (checkStoneH != string::npos || checkWaterH != string::npos || mapMat[location.x][location.y - 1].find("S") != string::npos || mapMat[location.x][location.y - 1].find("W") != string::npos)) ? movH *= 0.5 : movH = movH;
		((movV == 2) && (checkStoneV != string::npos || checkWaterV != string::npos || mapMat[location.x + 1][location.y].find("S") != string::npos || mapMat[location.x + 1][location.y].find("W") != string::npos)) ? movV *= 0.5 : movV = movV;
		((movV == -2) && (checkStoneV != string::npos || checkWaterV != string::npos || mapMat[location.x - 1][location.y].find("S") != string::npos || mapMat[location.x - 1][location.y].find("W") != string::npos)) ? movV *= 0.5 : movV = movV;


		checkStoneH = mapMat[location.x][location.y + movH].find("S");
		checkWaterH = mapMat[location.x][location.y + movH].find("W");

		checkStoneV = mapMat[location.x + movV][location.y].find("S");
		checkWaterV = mapMat[location.x + movV][location.y].find("W");

		if ((checkStoneH != string::npos || checkWaterH != string::npos) && abs(movH) == 1) {
			if ((checkStoneV != string::npos || checkWaterV != string::npos) && abs(movV) == 1) {
				this->status = "Stuck";
			}
			else {
				mapMat[location.x + movV][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "cat " << ID << " at (" << location.x + movV << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x = location.x + movV;
			}
		}
		else {
			mapMat[location.x][location.y + movH] += this->ID;
			mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
			cout << "cat " << ID << " at (" << location.x << "," << location.y + movH << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
			location.y = location.y + movH;
		}
	}
	else {
		int movH;
		(abs(loc.y - location.y) == 1) ? movH = 1 : movH = 2;
		(loc.y > location.y) ? movH *= 1 : movH *= (-1);
		int movV;
		(abs(loc.x - location.x) == 1) ? movV = 1 : movV = 2;
		(loc.x > location.x) ? movV *= 1 : movV *= (-1);
		size_t checkStoneH = mapMat[location.x][location.y + movH].find("S");
		size_t checkWaterH = mapMat[location.x][location.y + movH].find("W");

		size_t checkStoneV = mapMat[location.x + movV][location.y].find("S");
		size_t checkWaterV = mapMat[location.x + movV][location.y].find("W");


		((movH == 2) && (checkStoneH != string::npos || checkWaterH != string::npos || mapMat[location.x][location.y + 1].find("S") != string::npos || mapMat[location.x][location.y + 1].find("W") != string::npos)) ? movH *= 0.5 : movH = movH;
		((movH == -2) && (checkStoneH != string::npos || checkWaterH != string::npos || mapMat[location.x][location.y - 1].find("S") != string::npos || mapMat[location.x][location.y - 1].find("W") != string::npos)) ? movH *= 0.5 : movH = movH;
		((movV == 2) && (checkStoneV != string::npos || checkWaterV != string::npos || mapMat[location.x + 1][location.y].find("S") != string::npos || mapMat[location.x + 1][location.y].find("W") != string::npos)) ? movV *= 0.5 : movV = movV;
		((movV == -2) && (checkStoneV != string::npos || checkWaterV != string::npos || mapMat[location.x - 1][location.y].find("S") != string::npos || mapMat[location.x - 1][location.y].find("W") != string::npos)) ? movV *= 0.5 : movV = movV;

		checkStoneH = mapMat[location.x][location.y + movH].find("S");
		checkWaterH = mapMat[location.x][location.y + movH].find("W");

		checkStoneV = mapMat[location.x + movV][location.y].find("S");
		checkWaterV = mapMat[location.x + movV][location.y].find("W");

		if ((checkStoneV != string::npos || checkWaterV != string::npos) && abs(movV) == 1) {
			if ((checkStoneH != string::npos || checkWaterH != string::npos) && abs(movH) == 1) {
				this->status = "Stuck";
			}
			else {
				mapMat[location.x][location.y + movH] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "cat " << ID << " at (" << location.x << "," << location.y + movH << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y = location.y + movH;
			}
		}
		else {
			mapMat[location.x + movV][location.y] += this->ID;
			mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
			cout << "cat " << ID << " at (" << location.x + movV << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
			location.x = location.x + movV;
		}
	}
}

//DRAGON
dragon::dragon(string ID, point location) : zodiac(ID, location) {}
void dragon::printInfo() {
	cout << "dragon " << ID << " at (" << location.x << "," << location.y << ")" << endl;
}
void dragon::moveDecade(point loc, gameMap mapMat) {
	int horz = abs(location.y - loc.y);
	int vert = abs(location.x - loc.x);
	if (horz >= vert) {
		int movH;
		(loc.y > location.y) ? movH = 1 : movH = -1;
		int movV;
		(loc.x > location.x) ? movV = 1 : movV = -1;
		size_t checkOH = mapMat[location.x][location.y + movH].find("O");
		//size_t checkWaterH = mapMat[location.x][location.y + movH].find("W");

		size_t checkOV = mapMat[location.x + movV][location.y].find("O");
		//size_t checkWaterV = mapMat[location.x + movV][location.y].find("W");

		if (checkOH != string::npos) {
			if (checkOV != string::npos) {
				this->status = "Stuck";
			}
			else {
				mapMat[location.x + movV][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "dragon " << ID << " at (" << location.x + movV << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x = location.x + movV;
			}
		}
		else {
			mapMat[location.x][location.y + movH] += this->ID;
			mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
			cout << "dragon " << ID << " at (" << location.x << "," << location.y + movH << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
			location.y = location.y + movH;
		}
	}
	else {
		int movH;
		(loc.y > location.y) ? movH = 1 : movH = -1;
		int movV;
		(loc.x > location.x) ? movV = 1 : movV = -1;
		size_t checkOH = mapMat[location.x][location.y + movH].find("O");
		//size_t checkWaterH = mapMat[location.x][location.y + movH].find("W");

		size_t checkOV = mapMat[location.x + movV][location.y].find("O");
		//size_t checkWaterV = mapMat[location.x + movV][location.y].find("W");

		if (checkOH != string::npos) {
			if (checkOV != string::npos) {
				this->status = "Stuck";
			}
			else {
				mapMat[location.x][location.y + movH] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "rat " << ID << " at (" << location.x << "," << location.y + movH << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y = location.y + movH;
			}
		}
		else {
			mapMat[location.x + movV][location.y] += this->ID;
			mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
			cout << "rat " << ID << " at (" << location.x + movV << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
			location.x = location.x + movV;
		}
	}
}
void dragon::move(point loc, gameMap mapMat) {
	int horz = location.y - loc.y;
	int vert = location.x - loc.x;
	if (horz > 0 && vert > 0) {
		if (mapMat[location.x - 1][location.y - 1].find("O") != string::npos) { moveDecade(loc, mapMat); }
		else {
			mapMat[location.x - 1][location.y - 1] += this->ID;
			mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
			cout << "dragon " << ID << " at (" << location.x - 1 << "," << location.y - 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
			horz--; vert--;
			location.x = location.x - 1;
			location.y = location.y - 1;
		}

	}
	else if (horz < 0 && vert < 0) {
		if (mapMat[location.x + 1][location.y + 1].find("O") != string::npos) { moveDecade(loc, mapMat); }
		else {
			mapMat[location.x + 1][location.y + 1] += this->ID;
			mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
			cout << "dragon " << ID << " at (" << location.x + 1 << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
			horz++; vert++;
			location.x = location.x + 1;
			location.y = location.y + 1;
		}


	}
	else if (horz > 0 && vert < 0) {
		if (mapMat[location.x + 1][location.y - 1].find("O") != string::npos) { moveDecade(loc, mapMat); }
		else {
			mapMat[location.x + 1][location.y - 1] += this->ID;
			mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
			cout << "dragon " << ID << " at (" << location.x + 1 << "," << location.y - 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
			horz--; vert++;
			location.x = location.x + 1;
			location.y = location.y - 1;
		}


	}
	else if (horz < 0 && vert>0) {
		if (mapMat[location.x - 1][location.y + 1].find("O") != string::npos) { moveDecade(loc, mapMat); }
		else {
			mapMat[location.x - 1][location.y + 1] += this->ID;
			mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
			cout << "dragon " << ID << " at (" << location.x - 1 << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
			horz++; vert--;
			location.x = location.x - 1;
			location.y = location.y + 1;
		}



	}
	else { moveDecade(loc, mapMat); }
}

//SNAKE
snake::snake(string ID, point location) : zodiac(ID, location) {}
void snake::printInfo() {
	cout << "snake " << ID << " at (" << location.x << "," << location.y << ")" << endl;
}
void snake::move(point loc, gameMap mapMat) {
	int horz = abs(location.y - loc.y);
	int vert = abs(location.x - loc.x);

	if (vert == 0 && horz != 0) {
		int movH;
		(abs(loc.y - location.y) == 1) ? movH = 1 : movH = 2;
		(loc.y > location.y) ? movH *= 1 : movH *= (-1);

		size_t checkStoneH = mapMat[location.x][location.y + movH].find("S");
		size_t checkWaterH = mapMat[location.x][location.y + movH].find("W");

		((movH == 2) && ((checkStoneH != string::npos || checkWaterH != string::npos) && (mapMat[location.x][location.y + 1].find("S") == string::npos || mapMat[location.x][location.y + 1].find("W") == string::npos))) ? movH *= 0.5 : movH = movH;
		((movH == -2) && ((checkStoneH != string::npos || checkWaterH != string::npos) && (mapMat[location.x][location.y - 1].find("S") == string::npos || mapMat[location.x][location.y - 1].find("W") == string::npos))) ? movH *= 0.5 : movH = movH;

		if (movH > 0 && (mapMat[location.x][location.y + 1].find("W") != string::npos || mapMat[location.x][location.y + 1].find("S") != string::npos)) {
			if (loc.x == 0) {
				mapMat[location.x + 1][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "snake " << ID << " at (" << location.x + 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x += 1;
			}
			else if (loc.x == mapMat.row - 1) {
				mapMat[location.x - 1][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "snake " << ID << " at (" << location.x - 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x -= 1;
			}
			else {
				mapMat[location.x + 1][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "snake " << ID << " at (" << location.x + 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x += 1;
			}
		}
		else if (movH < 0 && (mapMat[location.x][location.y - 1].find("W") != string::npos || mapMat[location.x][location.y - 1].find("S") != string::npos)) {
			if (loc.x == 0) {
				mapMat[location.x + 1][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "snake " << ID << " at (" << location.x + 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x += 1;
			}
			else if (loc.x == mapMat.row - 1) {
				mapMat[location.x - 1][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "snake " << ID << " at (" << location.x - 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x -= 1;
			}
			else {
				mapMat[location.x + 1][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "snake " << ID << " at (" << location.x + 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x += 1;
			}
		}
		else {
			mapMat[location.x][location.y + movH] += this->ID;
			mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
			cout << "snake " << ID << " at (" << location.x << "," << location.y + movH << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
			location.y = location.y + movH;
		}

	}
	else if (horz == 0 && vert != 0) {
		int movV;
		(abs(loc.x - location.x) == 1) ? movV = 1 : movV = 2;
		(loc.x > location.x) ? movV *= 1 : movV *= (-1);

		size_t checkStoneV = mapMat[location.x + movV][location.y].find("S");
		size_t checkWaterV = mapMat[location.x + movV][location.y].find("W");

		((movV == 2) && ((checkStoneV != string::npos || checkWaterV != string::npos) && (mapMat[location.x + 1][location.y].find("S") == string::npos || mapMat[location.x + 1][location.y].find("W") == string::npos))) ? movV *= 0.5 : movV = movV;
		((movV == -2) && ((checkStoneV != string::npos || checkWaterV != string::npos) && (mapMat[location.x - 1][location.y].find("S") == string::npos || mapMat[location.x - 1][location.y].find("W") == string::npos))) ? movV *= 0.5 : movV = movV;


		if (movV > 0 && (mapMat[location.x + 1][location.y].find("W") != string::npos || mapMat[location.x + 1][location.y].find("S") != string::npos)) {
			if (loc.y == 0) {
				mapMat[location.x][location.y + 1] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "snake " << ID << " at (" << location.x << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y += 1;
			}
			else if (loc.x == mapMat.col - 1) {
				mapMat[location.x][location.y - 1] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "snake " << ID << " at (" << location.x << "," << location.y - 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y -= 1;
			}
			else {
				mapMat[location.x][location.y + 1] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "snake " << ID << " at (" << location.x << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y += 1;
			}
		}
		else if (movV < 0 && (mapMat[location.x - 1][location.y].find("W") != string::npos || mapMat[location.x - 1][location.y].find("S") != string::npos)) {
			if (loc.y == 0) {
				mapMat[location.x][location.y + 1] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "snake " << ID << " at (" << location.x << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y += 1;
			}
			else if (loc.x == mapMat.col - 1) {
				mapMat[location.x][location.y - 1] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "snake " << ID << " at (" << location.x << "," << location.y - 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y -= 1;
			}
			else {
				mapMat[location.x][location.y + 1] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "snake " << ID << " at (" << location.x << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y += 1;
			}
		}
		else {
			mapMat[location.x + movV][location.y] += this->ID;
			mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
			cout << "snake " << ID << " at (" << location.x + movV << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
			location.x = location.x + movV;
		}
	}
	else if (horz >= vert) {
		int movH;
		(abs(loc.y - location.y) == 1) ? movH = 1 : movH = 2;
		(loc.y > location.y) ? movH *= 1 : movH *= (-1);
		int movV;
		(abs(loc.x - location.x) == 1) ? movV = 1 : movV = 2;
		(loc.x > location.x) ? movV *= 1 : movV *= (-1);
		size_t checkStoneH = mapMat[location.x][location.y + movH].find("S");
		size_t checkWaterH = mapMat[location.x][location.y + movH].find("W");

		size_t checkStoneV = mapMat[location.x + movV][location.y].find("S");
		size_t checkWaterV = mapMat[location.x + movV][location.y].find("W");

		((movH == 2) && (checkStoneH != string::npos || checkWaterH != string::npos || mapMat[location.x][location.y + 1].find("S") != string::npos || mapMat[location.x][location.y + 1].find("W") != string::npos)) ? movH *= 0.5 : movH = movH;
		((movH == -2) && (checkStoneH != string::npos || checkWaterH != string::npos || mapMat[location.x][location.y - 1].find("S") != string::npos || mapMat[location.x][location.y - 1].find("W") != string::npos)) ? movH *= 0.5 : movH = movH;
		((movV == 2) && (checkStoneV != string::npos || checkWaterV != string::npos || mapMat[location.x + 1][location.y].find("S") != string::npos || mapMat[location.x + 1][location.y].find("W") != string::npos)) ? movV *= 0.5 : movV = movV;
		((movV == -2) && (checkStoneV != string::npos || checkWaterV != string::npos || mapMat[location.x - 1][location.y].find("S") != string::npos || mapMat[location.x - 1][location.y].find("W") != string::npos)) ? movV *= 0.5 : movV = movV;


		checkStoneH = mapMat[location.x][location.y + movH].find("S");
		checkWaterH = mapMat[location.x][location.y + movH].find("W");

		checkStoneV = mapMat[location.x + movV][location.y].find("S");
		checkWaterV = mapMat[location.x + movV][location.y].find("W");

		if ((checkStoneH != string::npos || checkWaterH != string::npos) && abs(movH) == 1) {
			if ((checkStoneV != string::npos || checkWaterV != string::npos) && abs(movV) == 1) {
				this->status = "Stuck";
			}
			else {
				mapMat[location.x + movV][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "snake " << ID << " at (" << location.x + movV << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x = location.x + movV;
			}
		}
		else {
			mapMat[location.x][location.y + movH] += this->ID;
			mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
			cout << "snake " << ID << " at (" << location.x << "," << location.y + movH << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
			location.y = location.y + movH;
		}
	}
	else {
		int movH;
		(abs(loc.y - location.y) == 1) ? movH = 1 : movH = 2;
		(loc.y > location.y) ? movH *= 1 : movH *= (-1);
		int movV;
		(abs(loc.x - location.x) == 1) ? movV = 1 : movV = 2;
		(loc.x > location.x) ? movV *= 1 : movV *= (-1);
		size_t checkStoneH = mapMat[location.x][location.y + movH].find("S");
		size_t checkWaterH = mapMat[location.x][location.y + movH].find("W");

		size_t checkStoneV = mapMat[location.x + movV][location.y].find("S");
		size_t checkWaterV = mapMat[location.x + movV][location.y].find("W");


		((movH == 2) && (checkStoneH != string::npos || checkWaterH != string::npos || mapMat[location.x][location.y + 1].find("S") != string::npos || mapMat[location.x][location.y + 1].find("W") != string::npos)) ? movH *= 0.5 : movH = movH;
		((movH == -2) && (checkStoneH != string::npos || checkWaterH != string::npos || mapMat[location.x][location.y - 1].find("S") != string::npos || mapMat[location.x][location.y - 1].find("W") != string::npos)) ? movH *= 0.5 : movH = movH;
		((movV == 2) && (checkStoneV != string::npos || checkWaterV != string::npos || mapMat[location.x + 1][location.y].find("S") != string::npos || mapMat[location.x + 1][location.y].find("W") != string::npos)) ? movV *= 0.5 : movV = movV;
		((movV == -2) && (checkStoneV != string::npos || checkWaterV != string::npos || mapMat[location.x - 1][location.y].find("S") != string::npos || mapMat[location.x - 1][location.y].find("W") != string::npos)) ? movV *= 0.5 : movV = movV;

		checkStoneH = mapMat[location.x][location.y + movH].find("S");
		checkWaterH = mapMat[location.x][location.y + movH].find("W");

		checkStoneV = mapMat[location.x + movV][location.y].find("S");
		checkWaterV = mapMat[location.x + movV][location.y].find("W");

		if ((checkStoneV != string::npos || checkWaterV != string::npos) && abs(movV) == 1) {
			if ((checkStoneH != string::npos || checkWaterH != string::npos) && abs(movH) == 1) {
				this->status = "Stuck";
			}
			else {
				mapMat[location.x][location.y + movH] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "snake " << ID << " at (" << location.x << "," << location.y + movH << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y = location.y + movH;
			}
		}
		else {
			mapMat[location.x + movV][location.y] += this->ID;
			mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
			cout << "snake " << ID << " at (" << location.x + movV << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
			location.x = location.x + movV;
		}
	}
}

//HORSE
horse::horse(string ID, point location) : zodiac(ID, location) {}
void horse::printInfo() {
	cout << "horse " << ID << " at (" << location.x << "," << location.y << ")" << endl;
}
void horse::move(point loc, gameMap mapMat) {
	if (this->status == "") {
		int horz = abs(location.y - loc.y);
		int vert = abs(location.x - loc.x);

		if (horz >= vert) {
			if (loc.y > location.y) {
				int mov;
				abs(loc.y - location.y) == 1 ? mov = 1 : abs(loc.y - location.y) == 2 ? mov = 2 : mov = 3;
				mapMat[location.x][location.y + mov] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				for (int i = 1; i <= mov; i++) {
					if (mapMat[location.x][location.y + i].find("S") != string::npos) this->status = "Injured";
				}


				cout << "horse " << ID << " at (" << location.x << "," << location.y + mov << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y = location.y + mov;
			}
			else if (loc.y < location.y) {
				int mov;
				abs(loc.y - location.y) == 1 ? mov = 1 : abs(loc.y - location.y) == 2 ? mov = 2 : mov = 3;
				mapMat[location.x][location.y - mov] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				for (int i = 1; i <= mov; i++) {
					if (mapMat[location.x][location.y - i].find("S") != string::npos) this->status = "Injured";
				}

				cout << "horse " << ID << " at (" << location.x << "," << location.y - mov << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y = location.y - mov;
			}
		}
		else {
			if (loc.x > location.x) {
				int mov;
				abs(loc.x - location.x) == 1 ? mov = 1 : abs(loc.x - location.x) == 1 ? mov = 2 : mov = 3;
				mapMat[location.x + mov][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				for (int i = 1; i <= mov; i++) {
					if (mapMat[location.x + i][location.y].find("S") != string::npos) this->status = "Injured";
				}

				cout << "horse " << ID << " at (" << location.x + mov << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x = location.x + mov;
			}
			else if (loc.x < location.x) {
				int mov;
				abs(loc.x - location.x) == 1 ? mov = 1 : abs(loc.x - location.x) == 1 ? mov = 2 : mov = 3;
				mapMat[location.x - mov][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				for (int i = 1; i <= mov; i++) {
					if (mapMat[location.x - i][location.y].find("S") != string::npos) this->status = "Injured";
				}

				cout << "horse " << ID << " at (" << location.x - mov << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x = location.x - mov;
			}
		}
	}
	else if (this->status == "Injured") {
		int horz = abs(location.y - loc.y);
		int vert = abs(location.x - loc.x);

		if (horz >= vert) {
			if (loc.y > location.y) {
				int mov;
				mov = 1;
				mapMat[location.x][location.y + mov] += this->ID;
				//mapMat[location.x][location.y + mov] = newStr(mapMat[location.x][location.y], "W");
				//mapMat[location.x][location.y + mov] = newStr(mapMat[location.x][location.y], "S");

				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "horse " << ID << " at (" << location.x << "," << location.y + mov << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y = location.y + mov;
			}
			else if (loc.y < location.y) {
				int mov;
				mov = 1;
				mapMat[location.x][location.y - mov] += this->ID;
				//mapMat[location.x][location.y - mov] = newStr(mapMat[location.x][location.y], "W");
				//mapMat[location.x][location.y - mov] = newStr(mapMat[location.x][location.y], "S");

				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "horse " << ID << " at (" << location.x << "," << location.y - mov << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y = location.y - mov;
			}
		}
		else {
			if (loc.x > location.x) {
				int mov;
				mov = 1;
				mapMat[location.x + mov][location.y] += this->ID;
				//mapMat[location.x + mov][location.y] = newStr(mapMat[location.x][location.y], "W");
				//mapMat[location.x + mov][location.y] = newStr(mapMat[location.x][location.y], "S");

				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "horse " << ID << " at (" << location.x + mov << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x = location.x + mov;
			}
			else if (loc.x < location.x) {
				int mov;
				mov = 1;
				mapMat[location.x - mov][location.y] += this->ID;
				//mapMat[location.x - mov][location.y] = newStr(mapMat[location.x][location.y], "W");
				//mapMat[location.x - mov][location.y] = newStr(mapMat[location.x][location.y], "S");

				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "horse " << ID << " at (" << location.x - mov << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x = location.x - mov;
			}
		}
	}

}

//GOAT
goat::goat(string ID, point location) : zodiac(ID, location) {}
void goat::printInfo() {
	cout << "goat " << ID << " at (" << location.x << "," << location.y << ")" << endl;
}
void goat::move(point loc, gameMap mapMat) {
	int horz = abs(location.y - loc.y);
	int vert = abs(location.x - loc.x);

	if (vert == 0 && horz != 0) {
		int movH;
		(abs(loc.y - location.y) == 1) ? movH = 1 : movH = 2;
		(loc.y > location.y) ? movH *= 1 : movH *= (-1);

		size_t checkStoneH = mapMat[location.x][location.y + movH].find("S");
		size_t checkWaterH = mapMat[location.x][location.y + movH].find("W");

		((movH == 2) && ((checkStoneH != string::npos || checkWaterH != string::npos) && (mapMat[location.x][location.y + 1].find("S") == string::npos || mapMat[location.x][location.y + 1].find("W") == string::npos))) ? movH *= 0.5 : movH = movH;
		((movH == -2) && ((checkStoneH != string::npos || checkWaterH != string::npos) && (mapMat[location.x][location.y - 1].find("S") == string::npos || mapMat[location.x][location.y - 1].find("W") == string::npos))) ? movH *= 0.5 : movH = movH;

		if (movH > 0 && (mapMat[location.x][location.y + 1].find("W") != string::npos || mapMat[location.x][location.y + 1].find("S") != string::npos)) {
			if (loc.x == 0) {
				mapMat[location.x + 1][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "goat " << ID << " at (" << location.x + 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x += 1;
			}
			else if (loc.x == mapMat.row - 1) {
				mapMat[location.x - 1][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "goat " << ID << " at (" << location.x - 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x -= 1;
			}
			else {
				mapMat[location.x + 1][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "goat " << ID << " at (" << location.x + 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x += 1;
			}
		}
		else if (movH < 0 && (mapMat[location.x][location.y - 1].find("W") != string::npos || mapMat[location.x][location.y - 1].find("S") != string::npos)) {
			if (loc.x == 0) {
				mapMat[location.x + 1][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "goat " << ID << " at (" << location.x + 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x += 1;
			}
			else if (loc.x == mapMat.row - 1) {
				mapMat[location.x - 1][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "goat " << ID << " at (" << location.x - 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x -= 1;
			}
			else {
				mapMat[location.x + 1][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "goat " << ID << " at (" << location.x + 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x += 1;
			}
		}
		else {
			mapMat[location.x][location.y + movH] += this->ID;
			mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
			cout << "goat " << ID << " at (" << location.x << "," << location.y + movH << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
			location.y = location.y + movH;
		}

	}
	else if (horz == 0 && vert != 0) {
		int movV;
		(abs(loc.x - location.x) == 1) ? movV = 1 : movV = 2;
		(loc.x > location.x) ? movV *= 1 : movV *= (-1);

		size_t checkStoneV = mapMat[location.x + movV][location.y].find("S");
		size_t checkWaterV = mapMat[location.x + movV][location.y].find("W");

		((movV == 2) && ((checkStoneV != string::npos || checkWaterV != string::npos) && (mapMat[location.x + 1][location.y].find("S") == string::npos || mapMat[location.x + 1][location.y].find("W") == string::npos))) ? movV *= 0.5 : movV = movV;
		((movV == -2) && ((checkStoneV != string::npos || checkWaterV != string::npos) && (mapMat[location.x - 1][location.y].find("S") == string::npos || mapMat[location.x - 1][location.y].find("W") == string::npos))) ? movV *= 0.5 : movV = movV;


		if (movV > 0 && (mapMat[location.x + 1][location.y].find("W") != string::npos || mapMat[location.x + 1][location.y].find("S") != string::npos)) {
			if (loc.y == 0) {
				mapMat[location.x][location.y + 1] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "goat " << ID << " at (" << location.x << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y += 1;
			}
			else if (loc.x == mapMat.col - 1) {
				mapMat[location.x][location.y - 1] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "goat " << ID << " at (" << location.x << "," << location.y - 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y -= 1;
			}
			else {
				mapMat[location.x][location.y + 1] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "goat " << ID << " at (" << location.x << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y += 1;
			}
		}
		else if (movV < 0 && (mapMat[location.x - 1][location.y].find("W") != string::npos || mapMat[location.x - 1][location.y].find("S") != string::npos)) {
			if (loc.y == 0) {
				mapMat[location.x][location.y + 1] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "goat " << ID << " at (" << location.x << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y += 1;
			}
			else if (loc.x == mapMat.col - 1) {
				mapMat[location.x][location.y - 1] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "goat " << ID << " at (" << location.x << "," << location.y - 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y -= 1;
			}
			else {
				mapMat[location.x][location.y + 1] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "goat " << ID << " at (" << location.x << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y += 1;
			}
		}
		else {
			mapMat[location.x + movV][location.y] += this->ID;
			mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
			cout << "goat " << ID << " at (" << location.x + movV << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
			location.x = location.x + movV;
		}
	}
	else if (horz >= vert) {
		int movH;
		(abs(loc.y - location.y) == 1) ? movH = 1 : movH = 2;
		(loc.y > location.y) ? movH *= 1 : movH *= (-1);
		int movV;
		(abs(loc.x - location.x) == 1) ? movV = 1 : movV = 2;
		(loc.x > location.x) ? movV *= 1 : movV *= (-1);
		size_t checkStoneH = mapMat[location.x][location.y + movH].find("S");
		size_t checkWaterH = mapMat[location.x][location.y + movH].find("W");

		size_t checkStoneV = mapMat[location.x + movV][location.y].find("S");
		size_t checkWaterV = mapMat[location.x + movV][location.y].find("W");

		((movH == 2) && (checkStoneH != string::npos || checkWaterH != string::npos || mapMat[location.x][location.y + 1].find("S") != string::npos || mapMat[location.x][location.y + 1].find("W") != string::npos)) ? movH *= 0.5 : movH = movH;
		((movH == -2) && (checkStoneH != string::npos || checkWaterH != string::npos || mapMat[location.x][location.y - 1].find("S") != string::npos || mapMat[location.x][location.y - 1].find("W") != string::npos)) ? movH *= 0.5 : movH = movH;
		((movV == 2) && (checkStoneV != string::npos || checkWaterV != string::npos || mapMat[location.x + 1][location.y].find("S") != string::npos || mapMat[location.x + 1][location.y].find("W") != string::npos)) ? movV *= 0.5 : movV = movV;
		((movV == -2) && (checkStoneV != string::npos || checkWaterV != string::npos || mapMat[location.x - 1][location.y].find("S") != string::npos || mapMat[location.x - 1][location.y].find("W") != string::npos)) ? movV *= 0.5 : movV = movV;


		checkStoneH = mapMat[location.x][location.y + movH].find("S");
		checkWaterH = mapMat[location.x][location.y + movH].find("W");

		checkStoneV = mapMat[location.x + movV][location.y].find("S");
		checkWaterV = mapMat[location.x + movV][location.y].find("W");

		if ((checkStoneH != string::npos || checkWaterH != string::npos) && abs(movH) == 1) {
			if ((checkStoneV != string::npos || checkWaterV != string::npos) && abs(movV) == 1) {
				this->status = "Stuck";
			}
			else {
				mapMat[location.x + movV][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "goat " << ID << " at (" << location.x + movV << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x = location.x + movV;
			}
		}
		else {
			mapMat[location.x][location.y + movH] += this->ID;
			mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
			cout << "goat " << ID << " at (" << location.x << "," << location.y + movH << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
			location.y = location.y + movH;
		}
	}
	else {
		int movH;
		(abs(loc.y - location.y) == 1) ? movH = 1 : movH = 2;
		(loc.y > location.y) ? movH *= 1 : movH *= (-1);
		int movV;
		(abs(loc.x - location.x) == 1) ? movV = 1 : movV = 2;
		(loc.x > location.x) ? movV *= 1 : movV *= (-1);
		size_t checkStoneH = mapMat[location.x][location.y + movH].find("S");
		size_t checkWaterH = mapMat[location.x][location.y + movH].find("W");

		size_t checkStoneV = mapMat[location.x + movV][location.y].find("S");
		size_t checkWaterV = mapMat[location.x + movV][location.y].find("W");


		((movH == 2) && (checkStoneH != string::npos || checkWaterH != string::npos || mapMat[location.x][location.y + 1].find("S") != string::npos || mapMat[location.x][location.y + 1].find("W") != string::npos)) ? movH *= 0.5 : movH = movH;
		((movH == -2) && (checkStoneH != string::npos || checkWaterH != string::npos || mapMat[location.x][location.y - 1].find("S") != string::npos || mapMat[location.x][location.y - 1].find("W") != string::npos)) ? movH *= 0.5 : movH = movH;
		((movV == 2) && (checkStoneV != string::npos || checkWaterV != string::npos || mapMat[location.x + 1][location.y].find("S") != string::npos || mapMat[location.x + 1][location.y].find("W") != string::npos)) ? movV *= 0.5 : movV = movV;
		((movV == -2) && (checkStoneV != string::npos || checkWaterV != string::npos || mapMat[location.x - 1][location.y].find("S") != string::npos || mapMat[location.x - 1][location.y].find("W") != string::npos)) ? movV *= 0.5 : movV = movV;

		checkStoneH = mapMat[location.x][location.y + movH].find("S");
		checkWaterH = mapMat[location.x][location.y + movH].find("W");

		checkStoneV = mapMat[location.x + movV][location.y].find("S");
		checkWaterV = mapMat[location.x + movV][location.y].find("W");

		if ((checkStoneV != string::npos || checkWaterV != string::npos) && abs(movV) == 1) {
			if ((checkStoneH != string::npos || checkWaterH != string::npos) && abs(movH) == 1) {
				this->status = "Stuck";
			}
			else {
				mapMat[location.x][location.y + movH] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "goat " << ID << " at (" << location.x << "," << location.y + movH << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y = location.y + movH;
			}
		}
		else {
			mapMat[location.x + movV][location.y] += this->ID;
			mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
			cout << "goat " << ID << " at (" << location.x + movV << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
			location.x = location.x + movV;
		}
	}
}

//MONKEY
monkey::monkey(string ID, point location) : zodiac(ID, location) {}
void monkey::printInfo() {
	cout << "monkey " << ID << " at (" << location.x << "," << location.y << ")" << endl;
}
void monkey::move(point loc, gameMap mapMat) {
	size_t findTree = mapMat[location.x][location.y].find("T");
	if (findTree != string::npos) {
		int horz = abs(location.y - loc.y);
		int vert = abs(location.x - loc.x);

		if (horz >= vert) {
			int mov;
			abs(loc.y - location.y) == 1 ? mov = 1 : abs(loc.y - location.y) == 2 ? mov = 2 : abs(loc.y - location.y) == 3 ? mov = 3 : mov = 4;
			(loc.y > location.y) ? mov *= 1 : mov *= (-1);
			mapMat[location.x][location.y + mov] += this->ID;
			mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
			cout << "monkey " << ID << " at (" << location.x << "," << location.y + mov << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
			location.y = location.y + mov;
		}
		else {
			int mov;
			abs(loc.x - location.x) == 1 ? mov = 1 : abs(loc.x - location.x) == 2 ? mov = 2 : abs(loc.x - location.x) == 3 ? mov = 3 : mov = 4;
			(loc.x > location.x) ? mov *= 1 : mov *= (-1);
			mapMat[location.x][location.y + mov] += this->ID;
			mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
			cout << "monkey " << ID << " at (" << location.x + mov << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
			location.x = location.x + mov;
		}
	}
	else {
		int horz = abs(location.y - loc.y);
		int vert = abs(location.x - loc.x);

		if (vert == 0 && horz != 0) {
			int movH;
			(abs(loc.y - location.y) == 1) ? movH = 1 : movH = 2;
			(loc.y > location.y) ? movH *= 1 : movH *= (-1);

			size_t checkStoneH = mapMat[location.x][location.y + movH].find("S");
			size_t checkWaterH = mapMat[location.x][location.y + movH].find("W");

			((movH == 2) && ((checkStoneH != string::npos || checkWaterH != string::npos) && (mapMat[location.x][location.y + 1].find("S") == string::npos || mapMat[location.x][location.y + 1].find("W") == string::npos))) ? movH *= 0.5 : movH = movH;
			((movH == -2) && ((checkStoneH != string::npos || checkWaterH != string::npos) && (mapMat[location.x][location.y - 1].find("S") == string::npos || mapMat[location.x][location.y - 1].find("W") == string::npos))) ? movH *= 0.5 : movH = movH;

			if (movH > 0 && (mapMat[location.x][location.y + 1].find("W") != string::npos || mapMat[location.x][location.y + 1].find("S") != string::npos)) {
				if (loc.x == 0) {
					mapMat[location.x + 1][location.y] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "monkey " << ID << " at (" << location.x + 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.x += 1;
				}
				else if (loc.x == mapMat.row - 1) {
					mapMat[location.x - 1][location.y] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "monkey " << ID << " at (" << location.x - 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.x -= 1;
				}
				else {
					mapMat[location.x + 1][location.y] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "monkey " << ID << " at (" << location.x + 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.x += 1;
				}
			}
			else if (movH < 0 && (mapMat[location.x][location.y - 1].find("W") != string::npos || mapMat[location.x][location.y - 1].find("S") != string::npos)) {
				if (loc.x == 0) {
					mapMat[location.x + 1][location.y] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "monkey " << ID << " at (" << location.x + 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.x += 1;
				}
				else if (loc.x == mapMat.row - 1) {
					mapMat[location.x - 1][location.y] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "monkey " << ID << " at (" << location.x - 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.x -= 1;
				}
				else {
					mapMat[location.x + 1][location.y] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "monkey " << ID << " at (" << location.x + 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.x += 1;
				}
			}
			else {
				mapMat[location.x][location.y + movH] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "monkey " << ID << " at (" << location.x << "," << location.y + movH << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y = location.y + movH;
			}

		}
		else if (horz == 0 && vert != 0) {
			int movV;
			(abs(loc.x - location.x) == 1) ? movV = 1 : movV = 2;
			(loc.x > location.x) ? movV *= 1 : movV *= (-1);

			size_t checkStoneV = mapMat[location.x + movV][location.y].find("S");
			size_t checkWaterV = mapMat[location.x + movV][location.y].find("W");

			((movV == 2) && ((checkStoneV != string::npos || checkWaterV != string::npos) && (mapMat[location.x + 1][location.y].find("S") == string::npos || mapMat[location.x + 1][location.y].find("W") == string::npos))) ? movV *= 0.5 : movV = movV;
			((movV == -2) && ((checkStoneV != string::npos || checkWaterV != string::npos) && (mapMat[location.x - 1][location.y].find("S") == string::npos || mapMat[location.x - 1][location.y].find("W") == string::npos))) ? movV *= 0.5 : movV = movV;


			if (movV > 0 && (mapMat[location.x + 1][location.y].find("W") != string::npos || mapMat[location.x + 1][location.y].find("S") != string::npos)) {
				if (loc.y == 0) {
					mapMat[location.x][location.y + 1] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "monkey " << ID << " at (" << location.x << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.y += 1;
				}
				else if (loc.x == mapMat.col - 1) {
					mapMat[location.x][location.y - 1] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "monkey " << ID << " at (" << location.x << "," << location.y - 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.y -= 1;
				}
				else {
					mapMat[location.x][location.y + 1] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "monkey " << ID << " at (" << location.x << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.y += 1;
				}
			}
			else if (movV < 0 && (mapMat[location.x - 1][location.y].find("W") != string::npos || mapMat[location.x - 1][location.y].find("S") != string::npos)) {
				if (loc.y == 0) {
					mapMat[location.x][location.y + 1] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "monkey " << ID << " at (" << location.x << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.y += 1;
				}
				else if (loc.x == mapMat.col - 1) {
					mapMat[location.x][location.y - 1] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "monkey " << ID << " at (" << location.x << "," << location.y - 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.y -= 1;
				}
				else {
					mapMat[location.x][location.y + 1] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "monkey " << ID << " at (" << location.x << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.y += 1;
				}
			}
			else {
				mapMat[location.x + movV][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "monkey " << ID << " at (" << location.x + movV << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x = location.x + movV;
			}
		}
		else if (horz >= vert) {
			int movH;
			(abs(loc.y - location.y) == 1) ? movH = 1 : movH = 2;
			(loc.y > location.y) ? movH *= 1 : movH *= (-1);
			int movV;
			(abs(loc.x - location.x) == 1) ? movV = 1 : movV = 2;
			(loc.x > location.x) ? movV *= 1 : movV *= (-1);
			size_t checkStoneH = mapMat[location.x][location.y + movH].find("S");
			size_t checkWaterH = mapMat[location.x][location.y + movH].find("W");

			size_t checkStoneV = mapMat[location.x + movV][location.y].find("S");
			size_t checkWaterV = mapMat[location.x + movV][location.y].find("W");

			((movH == 2) && (checkStoneH != string::npos || checkWaterH != string::npos || mapMat[location.x][location.y + 1].find("S") != string::npos || mapMat[location.x][location.y + 1].find("W") != string::npos)) ? movH *= 0.5 : movH = movH;
			((movH == -2) && (checkStoneH != string::npos || checkWaterH != string::npos || mapMat[location.x][location.y - 1].find("S") != string::npos || mapMat[location.x][location.y - 1].find("W") != string::npos)) ? movH *= 0.5 : movH = movH;
			((movV == 2) && (checkStoneV != string::npos || checkWaterV != string::npos || mapMat[location.x + 1][location.y].find("S") != string::npos || mapMat[location.x + 1][location.y].find("W") != string::npos)) ? movV *= 0.5 : movV = movV;
			((movV == -2) && (checkStoneV != string::npos || checkWaterV != string::npos || mapMat[location.x - 1][location.y].find("S") != string::npos || mapMat[location.x - 1][location.y].find("W") != string::npos)) ? movV *= 0.5 : movV = movV;


			checkStoneH = mapMat[location.x][location.y + movH].find("S");
			checkWaterH = mapMat[location.x][location.y + movH].find("W");

			checkStoneV = mapMat[location.x + movV][location.y].find("S");
			checkWaterV = mapMat[location.x + movV][location.y].find("W");

			if ((checkStoneH != string::npos || checkWaterH != string::npos) && abs(movH) == 1) {
				if ((checkStoneV != string::npos || checkWaterV != string::npos) && abs(movV) == 1) {
					this->status = "Stuck";
				}
				else {
					mapMat[location.x + movV][location.y] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "monkey " << ID << " at (" << location.x + movV << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.x = location.x + movV;
				}
			}
			else {
				mapMat[location.x][location.y + movH] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "monkey " << ID << " at (" << location.x << "," << location.y + movH << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y = location.y + movH;
			}
		}
		else {
			int movH;
			(abs(loc.y - location.y) == 1) ? movH = 1 : movH = 2;
			(loc.y > location.y) ? movH *= 1 : movH *= (-1);
			int movV;
			(abs(loc.x - location.x) == 1) ? movV = 1 : movV = 2;
			(loc.x > location.x) ? movV *= 1 : movV *= (-1);
			size_t checkStoneH = mapMat[location.x][location.y + movH].find("S");
			size_t checkWaterH = mapMat[location.x][location.y + movH].find("W");

			size_t checkStoneV = mapMat[location.x + movV][location.y].find("S");
			size_t checkWaterV = mapMat[location.x + movV][location.y].find("W");


			((movH == 2) && (checkStoneH != string::npos || checkWaterH != string::npos || mapMat[location.x][location.y + 1].find("S") != string::npos || mapMat[location.x][location.y + 1].find("W") != string::npos)) ? movH *= 0.5 : movH = movH;
			((movH == -2) && (checkStoneH != string::npos || checkWaterH != string::npos || mapMat[location.x][location.y - 1].find("S") != string::npos || mapMat[location.x][location.y - 1].find("W") != string::npos)) ? movH *= 0.5 : movH = movH;
			((movV == 2) && (checkStoneV != string::npos || checkWaterV != string::npos || mapMat[location.x + 1][location.y].find("S") != string::npos || mapMat[location.x + 1][location.y].find("W") != string::npos)) ? movV *= 0.5 : movV = movV;
			((movV == -2) && (checkStoneV != string::npos || checkWaterV != string::npos || mapMat[location.x - 1][location.y].find("S") != string::npos || mapMat[location.x - 1][location.y].find("W") != string::npos)) ? movV *= 0.5 : movV = movV;

			checkStoneH = mapMat[location.x][location.y + movH].find("S");
			checkWaterH = mapMat[location.x][location.y + movH].find("W");

			checkStoneV = mapMat[location.x + movV][location.y].find("S");
			checkWaterV = mapMat[location.x + movV][location.y].find("W");

			if ((checkStoneV != string::npos || checkWaterV != string::npos) && abs(movV) == 1) {
				if ((checkStoneH != string::npos || checkWaterH != string::npos) && abs(movH) == 1) {
					this->status = "Stuck";
				}
				else {
					mapMat[location.x][location.y + movH] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "monkey " << ID << " at (" << location.x << "," << location.y + movH << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.y = location.y + movH;
				}
			}
			else {
				mapMat[location.x + movV][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "monkey " << ID << " at (" << location.x + movV << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x = location.x + movV;
			}
		}
	}
}

//ROOSTER
rooster::rooster(string ID, point location) : zodiac(ID, location) {}
void rooster::printInfo() {
	cout << "rooster " << ID << " at (" << location.x << "," << location.y << ")" << endl;
}
void rooster::move(point loc, gameMap mapMat) {
	size_t findTree = mapMat[location.x][location.y].find("T");
	size_t findStone = mapMat[location.x][location.y].find("S");
	if (findTree != string::npos || findStone != string::npos) {
		int horz = abs(location.y - loc.y);
		int vert = abs(location.x - loc.x);

		if (vert == 0 && horz != 0) {
			int movH;
			(abs(loc.y - location.y) == 1) ? movH = 1 : (abs(loc.y - location.y) == 2) ? movH = 2 : movH = 3;
			(loc.y > location.y) ? movH *= 1 : movH *= (-1);

			size_t checkWaterH = mapMat[location.x][location.y + movH].find("W");

			((movH == 2) && ((checkWaterH != string::npos) && (mapMat[location.x][location.y + 1].find("W") == string::npos))) ? movH *= 0.5 : movH = movH;
			((movH == -2) && ((checkWaterH != string::npos) && (mapMat[location.x][location.y - 1].find("W") == string::npos))) ? movH *= 0.5 : movH = movH;

			if (movH > 0 && (mapMat[location.x][location.y + 1].find("W") != string::npos)) {
				if (loc.x == 0) {
					mapMat[location.x + 1][location.y] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "rooster " << ID << " at (" << location.x + 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.x += 1;
				}
				else if (loc.x == mapMat.row - 1) {
					mapMat[location.x - 1][location.y] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "rooster " << ID << " at (" << location.x - 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.x -= 1;
				}
				else {
					mapMat[location.x + 1][location.y] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "rooster " << ID << " at (" << location.x + 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.x += 1;
				}
			}
			else if (movH < 0 && (mapMat[location.x][location.y - 1].find("W") != string::npos)) {
				if (loc.x == 0) {
					mapMat[location.x + 1][location.y] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "rooster " << ID << " at (" << location.x + 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.x += 1;
				}
				else if (loc.x == mapMat.row - 1) {
					mapMat[location.x - 1][location.y] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "rooster " << ID << " at (" << location.x - 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.x -= 1;
				}
				else {
					mapMat[location.x + 1][location.y] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "rooster " << ID << " at (" << location.x + 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.x += 1;
				}
			}
			else {
				mapMat[location.x][location.y + movH] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "rooster " << ID << " at (" << location.x << "," << location.y + movH << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y = location.y + movH;
			}

		}
		else if (horz == 0 && vert != 0) {
			int movV;
			(abs(loc.x - location.x) == 1) ? movV = 1 : (abs(loc.x - location.x) == 2) ? movV = 2 : movV = 3;
			(loc.x > location.x) ? movV *= 1 : movV *= (-1);

			size_t checkWaterV = mapMat[location.x + movV][location.y].find("W");

			((movV == 2) && ((checkWaterV != string::npos) && (mapMat[location.x + 1][location.y].find("W") == string::npos))) ? movV *= 0.5 : movV = movV;
			((movV == -2) && ((checkWaterV != string::npos) && (mapMat[location.x - 1][location.y].find("W") == string::npos))) ? movV *= 0.5 : movV = movV;


			if (movV > 0 && (mapMat[location.x + 1][location.y].find("W") != string::npos)) {
				if (loc.y == 0) {
					mapMat[location.x][location.y + 1] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "rooster " << ID << " at (" << location.x << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.y += 1;
				}
				else if (loc.x == mapMat.col - 1) {
					mapMat[location.x][location.y - 1] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "rooster " << ID << " at (" << location.x << "," << location.y - 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.y -= 1;
				}
				else {
					mapMat[location.x][location.y + 1] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "rooster " << ID << " at (" << location.x << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.y += 1;
				}
			}
			else if (movV < 0 && (mapMat[location.x - 1][location.y].find("W") != string::npos)) {
				if (loc.y == 0) {
					mapMat[location.x][location.y + 1] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "rooster " << ID << " at (" << location.x << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.y += 1;
				}
				else if (loc.x == mapMat.col - 1) {
					mapMat[location.x][location.y - 1] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "rooster " << ID << " at (" << location.x << "," << location.y - 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.y -= 1;
				}
				else {
					mapMat[location.x][location.y + 1] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "rooster " << ID << " at (" << location.x << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.y += 1;
				}
			}
			else {
				mapMat[location.x + movV][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "rooster " << ID << " at (" << location.x + movV << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x = location.x + movV;
			}
		}
		else if (horz >= vert) {
			int movH;
			(abs(loc.y - location.y) == 1) ? movH = 1 : (abs(loc.y - location.y) == 2) ? movH = 2 : movH = 3;
			(loc.y > location.y) ? movH *= 1 : movH *= (-1);
			int movV;
			(abs(loc.x - location.x) == 1) ? movV = 1 : (abs(loc.x - location.x) == 2) ? movV = 2 : movV = 3;
			(loc.x > location.x) ? movV *= 1 : movV *= (-1);
			size_t checkWaterH = mapMat[location.x][location.y + movH].find("W");
			size_t checkStoneH = mapMat[location.x][location.y + movH].find("S");

			size_t checkWaterV = mapMat[location.x + movV][location.y].find("W");
			size_t checkStoneV = mapMat[location.x + movV][location.y].find("S");


			((movH == 2) && (checkStoneH != string::npos || checkWaterH != string::npos || mapMat[location.x][location.y + 1].find("W") != string::npos)) ? movH *= 0.5 : movH = movH;
			((movH == -2) && (checkStoneH != string::npos || checkWaterH != string::npos || mapMat[location.x][location.y - 1].find("W") != string::npos)) ? movH *= 0.5 : movH = movH;
			((movV == 2) && (checkStoneV != string::npos || checkWaterV != string::npos || mapMat[location.x + 1][location.y].find("W") != string::npos)) ? movV *= 0.5 : movV = movV;
			((movV == -2) && (checkStoneV != string::npos || checkWaterV != string::npos || mapMat[location.x - 1][location.y].find("W") != string::npos)) ? movV *= 0.5 : movV = movV;


			checkWaterH = mapMat[location.x][location.y + movH].find("W");

			checkWaterV = mapMat[location.x + movV][location.y].find("W");

			if ((checkWaterH != string::npos) && abs(movH) == 1) {
				if ((checkWaterV != string::npos) && abs(movV) == 1) {
					this->status = "Stuck";
				}
				else {
					mapMat[location.x + movV][location.y] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "rooster " << ID << " at (" << location.x + movV << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.x = location.x + movV;
				}
			}
			else {
				mapMat[location.x][location.y + movH] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "rooster " << ID << " at (" << location.x << "," << location.y + movH << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y = location.y + movH;
			}
		}
		else {
			int movH;
			(abs(loc.y - location.y) == 1) ? movH = 1 : (abs(loc.y - location.y) == 2) ? movH = 2 : movH = 3;
			(loc.y > location.y) ? movH *= 1 : movH *= (-1);
			int movV;
			(abs(loc.x - location.x) == 1) ? movV = 1 : (abs(loc.x - location.x) == 2) ? movV = 2 : movV = 3;
			(loc.x > location.x) ? movV *= 1 : movV *= (-1);
			size_t checkWaterH = mapMat[location.x][location.y + movH].find("W");
			size_t checkStoneH = mapMat[location.x][location.y + movH].find("S");

			size_t checkWaterV = mapMat[location.x + movV][location.y].find("W");
			size_t checkStoneV = mapMat[location.x + movV][location.y].find("S");



			((movH == 2) && (checkStoneH != string::npos || checkWaterH != string::npos || mapMat[location.x][location.y + 1].find("W") != string::npos)) ? movH *= 0.5 : movH = movH;
			((movH == -2) && (checkStoneH != string::npos || checkWaterH != string::npos || mapMat[location.x][location.y - 1].find("W") != string::npos)) ? movH *= 0.5 : movH = movH;
			((movV == 2) && (checkStoneV != string::npos || checkWaterV != string::npos || mapMat[location.x + 1][location.y].find("W") != string::npos)) ? movV *= 0.5 : movV = movV;
			((movV == -2) && (checkStoneV != string::npos || checkWaterV != string::npos || mapMat[location.x - 1][location.y].find("W") != string::npos)) ? movV *= 0.5 : movV = movV;

			checkWaterH = mapMat[location.x][location.y + movH].find("W");

			checkWaterV = mapMat[location.x + movV][location.y].find("W");

			if ((checkWaterV != string::npos) && abs(movV) == 1) {
				if ((checkWaterH != string::npos) && abs(movH) == 1) {
					this->status = "Stuck";
				}
				else {
					mapMat[location.x][location.y + movH] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "rooster " << ID << " at (" << location.x << "," << location.y + movH << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.y = location.y + movH;
				}
			}
			else {
				mapMat[location.x + movV][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "rooster " << ID << " at (" << location.x + movV << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x = location.x + movV;
			}
		}
	}
	else {
		int horz = abs(location.y - loc.y);
		int vert = abs(location.x - loc.x);

		if (vert == 0 && horz != 0) {
			int movH;
			(abs(loc.y - location.y) == 1) ? movH = 1 : movH = 2;
			(loc.y > location.y) ? movH *= 1 : movH *= (-1);

			size_t checkStoneH = mapMat[location.x][location.y + movH].find("S");
			size_t checkWaterH = mapMat[location.x][location.y + movH].find("W");

			((movH == 2) && ((checkWaterH != string::npos) && (mapMat[location.x][location.y + 1].find("W") == string::npos))) ? movH *= 0.5 : movH = movH;
			((movH == -2) && ((checkWaterH != string::npos) && (mapMat[location.x][location.y - 1].find("W") == string::npos))) ? movH *= 0.5 : movH = movH;

			if (movH > 0 && (mapMat[location.x][location.y + 1].find("W") != string::npos)) {
				if (loc.x == 0) {
					mapMat[location.x + 1][location.y] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "rooster " << ID << " at (" << location.x + 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.x += 1;
				}
				else if (loc.x == mapMat.row - 1) {
					mapMat[location.x - 1][location.y] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "rooster " << ID << " at (" << location.x - 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.x -= 1;
				}
				else {
					mapMat[location.x + 1][location.y] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "rooster " << ID << " at (" << location.x + 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.x += 1;
				}
			}
			else if (movH < 0 && (mapMat[location.x][location.y - 1].find("W") != string::npos)) {
				if (loc.x == 0) {
					mapMat[location.x + 1][location.y] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "rooster " << ID << " at (" << location.x + 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.x += 1;
				}
				else if (loc.x == mapMat.row - 1) {
					mapMat[location.x - 1][location.y] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "rooster " << ID << " at (" << location.x - 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.x -= 1;
				}
				else {
					mapMat[location.x + 1][location.y] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "rooster " << ID << " at (" << location.x + 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.x += 1;
				}
			}
			else {
				mapMat[location.x][location.y + movH] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "rooster " << ID << " at (" << location.x << "," << location.y + movH << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y = location.y + movH;
			}

		}
		else if (horz == 0 && vert != 0) {
			int movV;
			(abs(loc.x - location.x) == 1) ? movV = 1 : movV = 2;
			(loc.x > location.x) ? movV *= 1 : movV *= (-1);

			size_t checkStoneV = mapMat[location.x + movV][location.y].find("S");
			size_t checkWaterV = mapMat[location.x + movV][location.y].find("W");

			((movV == 2) && ((checkWaterV != string::npos) && (mapMat[location.x + 1][location.y].find("W") == string::npos))) ? movV *= 0.5 : movV = movV;
			((movV == -2) && ((checkWaterV != string::npos) && (mapMat[location.x - 1][location.y].find("W") == string::npos))) ? movV *= 0.5 : movV = movV;


			if (movV > 0 && (mapMat[location.x + 1][location.y].find("W") != string::npos)) {
				if (loc.y == 0) {
					mapMat[location.x][location.y + 1] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "rooster " << ID << " at (" << location.x << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.y += 1;
				}
				else if (loc.x == mapMat.col - 1) {
					mapMat[location.x][location.y - 1] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "rooster " << ID << " at (" << location.x << "," << location.y - 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.y -= 1;
				}
				else {
					mapMat[location.x][location.y + 1] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "rooster " << ID << " at (" << location.x << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.y += 1;
				}
			}
			else if (movV < 0 && (mapMat[location.x - 1][location.y].find("W") != string::npos)) {
				if (loc.y == 0) {
					mapMat[location.x][location.y + 1] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "rooster " << ID << " at (" << location.x << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.y += 1;
				}
				else if (loc.x == mapMat.col - 1) {
					mapMat[location.x][location.y - 1] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "rooster " << ID << " at (" << location.x << "," << location.y - 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.y -= 1;
				}
				else {
					mapMat[location.x][location.y + 1] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "rooster " << ID << " at (" << location.x << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.y += 1;
				}
			}
			else {
				mapMat[location.x + movV][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "rooster " << ID << " at (" << location.x + movV << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x = location.x + movV;
			}
		}
		else if (horz >= vert) {
			int movH;
			(abs(loc.y - location.y) == 1) ? movH = 1 : movH = 2;
			(loc.y > location.y) ? movH *= 1 : movH *= (-1);
			int movV;
			(abs(loc.x - location.x) == 1) ? movV = 1 : movV = 2;
			(loc.x > location.x) ? movV *= 1 : movV *= (-1);
			size_t checkWaterH = mapMat[location.x][location.y + movH].find("W");
			size_t checkStoneH = mapMat[location.x][location.y + movH].find("S");

			size_t checkWaterV = mapMat[location.x + movV][location.y].find("W");
			size_t checkStoneV = mapMat[location.x + movV][location.y].find("S");


			((movH == 2) && (checkStoneH != string::npos || checkWaterH != string::npos || mapMat[location.x][location.y + 1].find("W") != string::npos)) ? movH *= 0.5 : movH = movH;
			((movH == -2) && (checkStoneH != string::npos || checkWaterH != string::npos || mapMat[location.x][location.y - 1].find("W") != string::npos)) ? movH *= 0.5 : movH = movH;
			((movV == 2) && (checkStoneV != string::npos || checkWaterV != string::npos || mapMat[location.x + 1][location.y].find("W") != string::npos)) ? movV *= 0.5 : movV = movV;
			((movV == -2) && (checkStoneV != string::npos || checkWaterV != string::npos || mapMat[location.x - 1][location.y].find("W") != string::npos)) ? movV *= 0.5 : movV = movV;


			checkWaterH = mapMat[location.x][location.y + movH].find("W");

			checkWaterV = mapMat[location.x + movV][location.y].find("W");

			if ((checkWaterH != string::npos) && abs(movH) == 1) {
				if ((checkWaterV != string::npos) && abs(movV) == 1) {
					this->status = "Stuck";
				}
				else {
					mapMat[location.x + movV][location.y] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "rooster " << ID << " at (" << location.x + movV << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.x = location.x + movV;
				}
			}
			else {
				mapMat[location.x][location.y + movH] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "rooster " << ID << " at (" << location.x << "," << location.y + movH << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y = location.y + movH;
			}
		}
		else {
			int movH;
			(abs(loc.y - location.y) == 1) ? movH = 1 : movH = 2;
			(loc.y > location.y) ? movH *= 1 : movH *= (-1);
			int movV;
			(abs(loc.x - location.x) == 1) ? movV = 1 : movV = 2;
			(loc.x > location.x) ? movV *= 1 : movV *= (-1);
			size_t checkWaterH = mapMat[location.x][location.y + movH].find("W");
			size_t checkStoneH = mapMat[location.x][location.y + movH].find("S");

			size_t checkWaterV = mapMat[location.x + movV][location.y].find("W");
			size_t checkStoneV = mapMat[location.x][location.y + movH].find("S");


			((movH == 2) && (checkStoneH != string::npos || checkWaterH != string::npos || mapMat[location.x][location.y + 1].find("W") != string::npos)) ? movH *= 0.5 : movH = movH;
			((movH == -2) && (checkStoneH != string::npos || checkWaterH != string::npos || mapMat[location.x][location.y - 1].find("W") != string::npos)) ? movH *= 0.5 : movH = movH;
			((movV == 2) && (checkStoneV != string::npos || checkWaterV != string::npos || mapMat[location.x + 1][location.y].find("W") != string::npos)) ? movV *= 0.5 : movV = movV;
			((movV == -2) && (checkStoneV != string::npos || checkWaterV != string::npos || mapMat[location.x - 1][location.y].find("W") != string::npos)) ? movV *= 0.5 : movV = movV;

			checkWaterH = mapMat[location.x][location.y + movH].find("W");

			checkWaterV = mapMat[location.x + movV][location.y].find("W");

			if ((checkWaterV != string::npos) && abs(movV) == 1) {
				if ((checkWaterH != string::npos) && abs(movH) == 1) {
					this->status = "Stuck";
				}
				else {
					mapMat[location.x][location.y + movH] += this->ID;
					mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
					cout << "rooster " << ID << " at (" << location.x << "," << location.y + movH << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
					location.y = location.y + movH;
				}
			}
			else {
				mapMat[location.x + movV][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "rooster " << ID << " at (" << location.x + movV << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x = location.x + movV;
			}
		}
	}
}

//DOG
dog::dog(string ID, point location) : zodiac(ID, location) {}
void dog::printInfo() {
	cout << "dog " << ID << " at (" << location.x << "," << location.y << ")" << endl;
}
void dog::move(point loc, gameMap mapMat) {
	int horz = abs(location.y - loc.y);
	int vert = abs(location.x - loc.x);

	if (vert == 0 && horz != 0) {
		int movH;
		(abs(loc.y - location.y) == 1) ? movH = 1 : movH = 2;
		(loc.y > location.y) ? movH *= 1 : movH *= (-1);

		size_t checkStoneH = mapMat[location.x][location.y + movH].find("S");
		size_t checkWaterH = mapMat[location.x][location.y + movH].find("W");

		((movH == 2) && ((checkStoneH != string::npos || checkWaterH != string::npos) && (mapMat[location.x][location.y + 1].find("S") == string::npos || mapMat[location.x][location.y + 1].find("W") == string::npos))) ? movH *= 0.5 : movH = movH;
		((movH == -2) && ((checkStoneH != string::npos || checkWaterH != string::npos) && (mapMat[location.x][location.y - 1].find("S") == string::npos || mapMat[location.x][location.y - 1].find("W") == string::npos))) ? movH *= 0.5 : movH = movH;

		if (movH > 0 && (mapMat[location.x][location.y + 1].find("W") != string::npos || mapMat[location.x][location.y + 1].find("S") != string::npos)) {
			if (loc.x == 0) {
				mapMat[location.x + 1][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "dog " << ID << " at (" << location.x + 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x += 1;
			}
			else if (loc.x == mapMat.row - 1) {
				mapMat[location.x - 1][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "dog " << ID << " at (" << location.x - 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x -= 1;
			}
			else {
				mapMat[location.x + 1][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "dog " << ID << " at (" << location.x + 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x += 1;
			}
		}
		else if (movH < 0 && (mapMat[location.x][location.y - 1].find("W") != string::npos || mapMat[location.x][location.y - 1].find("S") != string::npos)) {
			if (loc.x == 0) {
				mapMat[location.x + 1][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "dog " << ID << " at (" << location.x + 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x += 1;
			}
			else if (loc.x == mapMat.row - 1) {
				mapMat[location.x - 1][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "dog " << ID << " at (" << location.x - 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x -= 1;
			}
			else {
				mapMat[location.x + 1][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "dog " << ID << " at (" << location.x + 1 << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x += 1;
			}
		}
		else {
			mapMat[location.x][location.y + movH] += this->ID;
			mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
			cout << "dog " << ID << " at (" << location.x << "," << location.y + movH << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
			location.y = location.y + movH;
		}

	}
	else if (horz == 0 && vert != 0) {
		int movV;
		(abs(loc.x - location.x) == 1) ? movV = 1 : movV = 2;
		(loc.x > location.x) ? movV *= 1 : movV *= (-1);

		size_t checkStoneV = mapMat[location.x + movV][location.y].find("S");
		size_t checkWaterV = mapMat[location.x + movV][location.y].find("W");

		((movV == 2) && ((checkStoneV != string::npos || checkWaterV != string::npos) && (mapMat[location.x + 1][location.y].find("S") == string::npos || mapMat[location.x + 1][location.y].find("W") == string::npos))) ? movV *= 0.5 : movV = movV;
		((movV == -2) && ((checkStoneV != string::npos || checkWaterV != string::npos) && (mapMat[location.x - 1][location.y].find("S") == string::npos || mapMat[location.x - 1][location.y].find("W") == string::npos))) ? movV *= 0.5 : movV = movV;


		if (movV > 0 && (mapMat[location.x + 1][location.y].find("W") != string::npos || mapMat[location.x + 1][location.y].find("S") != string::npos)) {
			if (loc.y == 0) {
				mapMat[location.x][location.y + 1] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "dog " << ID << " at (" << location.x << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y += 1;
			}
			else if (loc.x == mapMat.col - 1) {
				mapMat[location.x][location.y - 1] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "dog " << ID << " at (" << location.x << "," << location.y - 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y -= 1;
			}
			else {
				mapMat[location.x][location.y + 1] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "dog " << ID << " at (" << location.x << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y += 1;
			}
		}
		else if (movV < 0 && (mapMat[location.x - 1][location.y].find("W") != string::npos || mapMat[location.x - 1][location.y].find("S") != string::npos)) {
			if (loc.y == 0) {
				mapMat[location.x][location.y + 1] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "dog " << ID << " at (" << location.x << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y += 1;
			}
			else if (loc.x == mapMat.col - 1) {
				mapMat[location.x][location.y - 1] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "dog " << ID << " at (" << location.x << "," << location.y - 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y -= 1;
			}
			else {
				mapMat[location.x][location.y + 1] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "dog " << ID << " at (" << location.x << "," << location.y + 1 << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y += 1;
			}
		}
		else {
			mapMat[location.x + movV][location.y] += this->ID;
			mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
			cout << "dog " << ID << " at (" << location.x + movV << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
			location.x = location.x + movV;
		}
	}
	else if (horz >= vert) {
		int movH;
		(abs(loc.y - location.y) == 1) ? movH = 1 : movH = 2;
		(loc.y > location.y) ? movH *= 1 : movH *= (-1);
		int movV;
		(abs(loc.x - location.x) == 1) ? movV = 1 : movV = 2;
		(loc.x > location.x) ? movV *= 1 : movV *= (-1);
		size_t checkStoneH = mapMat[location.x][location.y + movH].find("S");
		size_t checkWaterH = mapMat[location.x][location.y + movH].find("W");

		size_t checkStoneV = mapMat[location.x + movV][location.y].find("S");
		size_t checkWaterV = mapMat[location.x + movV][location.y].find("W");

		((movH == 2) && (checkStoneH != string::npos || checkWaterH != string::npos || mapMat[location.x][location.y + 1].find("S") != string::npos || mapMat[location.x][location.y + 1].find("W") != string::npos)) ? movH *= 0.5 : movH = movH;
		((movH == -2) && (checkStoneH != string::npos || checkWaterH != string::npos || mapMat[location.x][location.y - 1].find("S") != string::npos || mapMat[location.x][location.y - 1].find("W") != string::npos)) ? movH *= 0.5 : movH = movH;
		((movV == 2) && (checkStoneV != string::npos || checkWaterV != string::npos || mapMat[location.x + 1][location.y].find("S") != string::npos || mapMat[location.x + 1][location.y].find("W") != string::npos)) ? movV *= 0.5 : movV = movV;
		((movV == -2) && (checkStoneV != string::npos || checkWaterV != string::npos || mapMat[location.x - 1][location.y].find("S") != string::npos || mapMat[location.x - 1][location.y].find("W") != string::npos)) ? movV *= 0.5 : movV = movV;


		checkStoneH = mapMat[location.x][location.y + movH].find("S");
		checkWaterH = mapMat[location.x][location.y + movH].find("W");

		checkStoneV = mapMat[location.x + movV][location.y].find("S");
		checkWaterV = mapMat[location.x + movV][location.y].find("W");

		if ((checkStoneH != string::npos || checkWaterH != string::npos) && abs(movH) == 1) {
			if ((checkStoneV != string::npos || checkWaterV != string::npos) && abs(movV) == 1) {
				this->status = "Stuck";
			}
			else {
				mapMat[location.x + movV][location.y] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "dog " << ID << " at (" << location.x + movV << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.x = location.x + movV;
			}
		}
		else {
			mapMat[location.x][location.y + movH] += this->ID;
			mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
			cout << "dog " << ID << " at (" << location.x << "," << location.y + movH << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
			location.y = location.y + movH;
		}
	}
	else {
		int movH;
		(abs(loc.y - location.y) == 1) ? movH = 1 : movH = 2;
		(loc.y > location.y) ? movH *= 1 : movH *= (-1);
		int movV;
		(abs(loc.x - location.x) == 1) ? movV = 1 : movV = 2;
		(loc.x > location.x) ? movV *= 1 : movV *= (-1);
		size_t checkStoneH = mapMat[location.x][location.y + movH].find("S");
		size_t checkWaterH = mapMat[location.x][location.y + movH].find("W");

		size_t checkStoneV = mapMat[location.x + movV][location.y].find("S");
		size_t checkWaterV = mapMat[location.x + movV][location.y].find("W");


		((movH == 2) && (checkStoneH != string::npos || checkWaterH != string::npos || mapMat[location.x][location.y + 1].find("S") != string::npos || mapMat[location.x][location.y + 1].find("W") != string::npos)) ? movH *= 0.5 : movH = movH;
		((movH == -2) && (checkStoneH != string::npos || checkWaterH != string::npos || mapMat[location.x][location.y - 1].find("S") != string::npos || mapMat[location.x][location.y - 1].find("W") != string::npos)) ? movH *= 0.5 : movH = movH;
		((movV == 2) && (checkStoneV != string::npos || checkWaterV != string::npos || mapMat[location.x + 1][location.y].find("S") != string::npos || mapMat[location.x + 1][location.y].find("W") != string::npos)) ? movV *= 0.5 : movV = movV;
		((movV == -2) && (checkStoneV != string::npos || checkWaterV != string::npos || mapMat[location.x - 1][location.y].find("S") != string::npos || mapMat[location.x - 1][location.y].find("W") != string::npos)) ? movV *= 0.5 : movV = movV;

		checkStoneH = mapMat[location.x][location.y + movH].find("S");
		checkWaterH = mapMat[location.x][location.y + movH].find("W");

		checkStoneV = mapMat[location.x + movV][location.y].find("S");
		checkWaterV = mapMat[location.x + movV][location.y].find("W");

		if ((checkStoneV != string::npos || checkWaterV != string::npos) && abs(movV) == 1) {
			if ((checkStoneH != string::npos || checkWaterH != string::npos) && abs(movH) == 1) {
				this->status = "Stuck";
			}
			else {
				mapMat[location.x][location.y + movH] += this->ID;
				mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
				cout << "dog " << ID << " at (" << location.x << "," << location.y + movH << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
				location.y = location.y + movH;
			}
		}
		else {
			mapMat[location.x + movV][location.y] += this->ID;
			mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
			cout << "dog " << ID << " at (" << location.x + movV << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
			location.x = location.x + movV;
		}
	}
}

//BOAR
boar::boar(string ID, point location) : zodiac(ID, location) {}
void boar::printInfo() {
	cout << "boar " << ID << " at (" << location.x << "," << location.y << ")" << endl;
}
void boar::move(point loc, gameMap mapMat) {
	int horz = abs(location.y - loc.y);
	int vert = abs(location.x - loc.x);

	if (horz >= vert) {
		if (loc.y > location.y) {
			int mov;
			mov = 1;
			mapMat[location.x][location.y + mov] += this->ID;
			//mapMat[location.x][location.y + mov] = newStr(mapMat[location.x][location.y], "W");
			mapMat[location.x][location.y + mov] = newStr(mapMat[location.x][location.y + mov], "S");

			mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
			cout << "boar " << ID << " at (" << location.x << "," << location.y + mov << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
			location.y = location.y + mov;
		}
		else if (loc.y < location.y) {
			int mov;
			mov = 1;
			mapMat[location.x][location.y - mov] += this->ID;
			//mapMat[location.x][location.y - mov] = newStr(mapMat[location.x][location.y], "W");
			mapMat[location.x][location.y - mov] = newStr(mapMat[location.x][location.y - mov], "S");

			mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
			cout << "boar " << ID << " at (" << location.x << "," << location.y - mov << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
			location.y = location.y - mov;
		}
	}
	else {
		if (loc.x > location.x) {
			int mov;
			mov = 1;
			mapMat[location.x + mov][location.y] += this->ID;
			//mapMat[location.x + mov][location.y] = newStr(mapMat[location.x][location.y], "W");
			mapMat[location.x + mov][location.y] = newStr(mapMat[location.x + mov][location.y], "S");

			mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
			cout << "boar " << ID << " at (" << location.x + mov << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
			location.x = location.x + mov;
		}
		else if (loc.x < location.x) {
			int mov;
			mov = 1;
			mapMat[location.x - mov][location.y] += this->ID;
			//mapMat[location.x - mov][location.y] = newStr(mapMat[location.x][location.y], "W");
			mapMat[location.x - mov][location.y] = newStr(mapMat[location.x - mov][location.y], "S");

			mapMat[location.x][location.y] = newStr(mapMat[location.x][location.y], this->ID);
			cout << "boar " << ID << " at (" << location.x - mov << "," << location.y << ")" << " move from (" << location.x << "," << location.y << ")" << endl;
			location.x = location.x - mov;
		}
	}
}

//CLASS ZOLIST
zoList::zoList() {
	zList = new zodiac * [12];
	sz = 0;
}
zodiac*&zoList:: operator[](int i) {
	return zList[i];
}
void zoList:: add(zodiac* zo) {
	zList[sz] = zo;
	sz++;
}
zoList::~zoList() {
	for (int i = 0; i < sz; i++) {
		delete zList[i];
	}
	delete[] zList;
}

//GAME CLASS
Game::Game(const gameMap& m) {
	mapMat = m;
}
void Game::addZo(zodiac* zo) {
	zList.add(zo);
	if (zo->location.x >= mapMat.row || zo->location.y >= mapMat.col) {
		cout << "Out of Bound\n";
		check = true;
		return;
	}
	else {
		if (mapMat.mapMat[zo->location.x][zo->location.y] == "") mapMat.mapMat[zo->location.x][zo->location.y] = zo->ID;
		else mapMat.mapMat[zo->location.x][zo->location.y] = mapMat.mapMat[zo->location.x][zo->location.y] + zo->ID;
		num++;
	}

}
void Game::startGame(point goal, bool fl) {
	if (goal.x >= mapMat.row || goal.y >= mapMat.col) { cout << "Out of Bound\n"; return; }
	else if (check) { return; }
	else {
		cout << "GAME START" << endl;
		mapMat.mapMat[goal.x][goal.y] = mapMat.mapMat[goal.x][goal.y] + "G";
		string ch = mapMat.mapMat[goal.x][goal.y];
		flag = fl;
		if (fl == true) {
			int i = 1;
			mapMat.printMap();
			while (mapMat.mapMat[goal.x][goal.y] == ch) {
				cout << "TURN " << i << endl;
				for (int j = 0; j < num; j++) {
					zList.zList[j]->move(goal, mapMat);
				}
				mapMat.printMap();
				i++;
			}
			cout << "########RESULT#########\n";
			int man[100], rank[100];
			for (int j = 0; j < num; j++) {
				size_t check = mapMat.mapMat[goal.x][goal.y].find(zList.zList[j]->ID);
				if (check != string::npos) {
					cout << "Congratulations to the winner "; zList.zList[j]->printInfo();
					man[j] = 0;
					rank[j] = 1;
				}
				else {
					man[j] = abs(zList.zList[j]->location.x - goal.x) + abs(zList.zList[j]->location.y - goal.y);
					rank[j] = 1;
				}
			}
			for (int ii = 0; ii < num; ii++)
				for (int jj = 0; jj < num; jj++)
					if (man[jj] < man[ii])
						rank[ii]++;

			for (int j = 0; j < num; j++) {
				size_t check = mapMat.mapMat[goal.x][goal.y].find(zList.zList[j]->ID);
				if (check == string::npos) {
					cout << "Rank " << rank[j] << ":"; zList.zList[j]->printInfo();
				}
			}
		}
	}
}
void Game::startGame(point goal) {
	mapMat.mapMat[goal.x][goal.y] = mapMat.mapMat[goal.x][goal.y] + "G";
	mapMat.printMap();
}
Game::~Game() {}





