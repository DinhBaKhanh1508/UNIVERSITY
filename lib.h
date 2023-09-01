#if !defined(LIB_HEADER)
#define LIB_HEADER
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;


class gameMap {
public:
	string** mapMat;
	int row;
	int col;
	gameMap();
	gameMap(string** inputMat, int r, int c);
	void printMap();
	~gameMap();
	string*& operator[](int i);
};

class point {
public:
	int x;
	int y;
	point();
	point(int x, int y);
};

string newStr(string str, string ID);


class zodiac {
public:
	string ID;
	point location;
	string status = "";
	zodiac(string ID, point location);
	virtual void printInfo();
	virtual void move(point loc, gameMap mapMat);
	virtual ~zodiac();
};


class rat : public zodiac {
public:
	rat(string ID, point location);
	void printInfo();
	void move(point loc, gameMap mapMat);
};

class ox : public zodiac {
public:
	ox(string ID, point location);
	void printInfo();
	void move(point loc, gameMap mapMat);
};

class tiger : public zodiac {
public:
	tiger(string ID, point location);
	void printInfo();
	void move(point loc, gameMap mapMat);
};

class cat : public zodiac {
public:
	cat(string ID, point location);
	void printInfo();
	void move(point loc, gameMap mapMat);
};

class dragon : public zodiac {
public:
	dragon(string ID, point location);
	void printInfo();
	void moveDecade(point loc, gameMap mapMat);
	void move(point loc, gameMap mapMat);
};

class snake : public zodiac {
public:
	snake(string ID, point location);
	void printInfo();
	void move(point loc, gameMap mapMat);
};

class horse : public zodiac {
public:
	horse(string ID, point location);
	void printInfo();
	void move(point loc, gameMap mapMat);
};

class goat : public zodiac {
public:
	goat(string ID, point location);
	void printInfo();
	void move(point loc, gameMap mapMat);
};

class monkey : public zodiac {
public:
	monkey(string ID, point location);
	void printInfo();
	void move(point loc, gameMap mapMat);
};

class rooster : public zodiac {
public:
	rooster(string ID, point location);
	void printInfo();
	void move(point loc, gameMap mapMat);
};

class dog : public zodiac {
public:
	dog(string ID, point location);
	void printInfo();
	void move(point loc, gameMap mapMat);
};

class boar : public zodiac {
public:
	boar(string ID, point location);
	void printInfo();
	void move(point loc, gameMap mapMat);
};


class zoList {
public:
	zodiac** zList;
	int sz = 0;
	zoList();
	zodiac*& operator[](int i);
	void add(zodiac* zo);
	~zoList();
};

class Game {
public:
	gameMap mapMat;
	zoList zList;
	bool flag = false;
	int num = 0;
	bool check = false;
	Game(const gameMap& m);
	void addZo(zodiac* zo);
	void startGame(point goal, bool fl);
	void startGame(point goal);
	~Game();

};

	
#endif