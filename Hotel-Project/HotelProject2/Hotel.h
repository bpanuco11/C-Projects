#ifndef HOTEL_H
#define HOTEL_H

#include <string>
using namespace std;

class Hotel
{

protected:
	int reservationSize;
	int cost;
	int roomNumber;
	string roomType, tempRType, guest;


public:
	Hotel() {
		reservationSize = 0;
		cost = 0;
		roomNumber = 0;
		roomType = "";
		tempRType = "";
		guest = "";
	}
	int getCost() { return this->cost; }
	int getRSize() { return this->reservationSize; }
	int getRoomNumber(){ return this->roomNumber; }
	string getGuest() { return this->guest; }
	string getRType() { return this->roomType; }
	string getTempRType();
	void roomReserved(string);
	void setRoomNumber(int);
	void setGuest(string);

};
#endif

class Courtyard : public Hotel {

public:
	Courtyard() {

		cost = 125;
		reservationSize = 70;
		roomType = "Standard Room: Courtyard";

	}

};

class Scenic : public Hotel {

public:
	Scenic() {

		cost = 145;
		reservationSize = 35;
		roomType = "Standard Room: Scenic";

	}

};

class DeluxeSuite : public Hotel {

public:
	DeluxeSuite() {

		cost = 350;
		reservationSize = 15;
		roomType = "Deluxe Suite";

	}

};

class Penthouse : public Hotel {

public:
	Penthouse() {

		cost = 1135;
		reservationSize = 2;
		roomType = "Penthouse";

	}

};