#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <string>
using namespace std;

class Ship
{

private:

	int shipSize;
	char letter;
	string type;

public:

	Ship();
	Ship(int, char, string);
	const int getSize();
	const char getLetter();
	const string getType();
};
#endif
