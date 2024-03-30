#ifndef INVENTORY_H
#define INVENTORY_H

#include "Hotel.h"

#include <string>
using namespace std;

class Inventory {

private:

	int maxHotelSpace = 122, reservedCount = 0, revenue = 0;

	Hotel* inventory = new Hotel[maxHotelSpace];

	Hotel* courtYard = new Courtyard();
	Hotel* scenic = new Scenic();
	Hotel* deluxe = new DeluxeSuite();
	Hotel* pentHouse = new Penthouse();

	void fillInventory(Hotel*);
	void addRevenue(Hotel);

public:

	Inventory();
	~Inventory();

	void displayInventory();
	void reserveRoom(int);
	bool isValidReserve(int);
	int getRevenue();
	void getRoomsReserved();
	int getRsvCount();
	void recordInformation(string);

};

#endif