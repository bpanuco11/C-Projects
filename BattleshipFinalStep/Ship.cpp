#include "Ship.h"
Ship::Ship(int shipSize, char letter, string type) {

	this->shipSize = shipSize;
	this->letter = letter;
	this->type = type;

}// end 1 arg constructor

Ship::Ship() {
	shipSize = 0;
	letter = ' ';
	type = "";
}

const int Ship::getSize() {

	return shipSize;
}
const char Ship::getLetter() {

	return letter;
}
const string Ship::getType() {

	return type;
}