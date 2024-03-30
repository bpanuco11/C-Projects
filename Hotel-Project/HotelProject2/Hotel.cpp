#include "Hotel.h"

void Hotel::roomReserved(string reserved) {

	tempRType = roomType;
	roomType = reserved;

}

string Hotel::getTempRType(){return this->tempRType;}

void Hotel::setRoomNumber(int number) {this->roomNumber = number;}

void Hotel::setGuest(string guest) { this->guest = guest; }
