#include "Inventory.h"
#include <iostream>
#include <iomanip>
#include <fstream>

Inventory::Inventory() {

	fillInventory(courtYard);
	fillInventory(scenic);
	fillInventory(deluxe);
	fillInventory(pentHouse);

}// end no-arg constructor

Inventory::~Inventory() {

	inventory = nullptr;
	courtYard = nullptr;
	scenic = nullptr;
	deluxe = nullptr;
	pentHouse = nullptr;
	delete inventory, courtYard, scenic, deluxe, pentHouse;
}

void Inventory::fillInventory(Hotel* hotel) {

	int currentSize = hotel->getRSize();
	int roomsConstructed = 0;
	static int index = 0, roomNumber ;
	bool stop = false;

	if (hotel->getRType() == "Standard Room: Courtyard")
		roomNumber = 101;
	else if (hotel->getRType() == "Standard Room: Scenic")
		roomNumber = 201;
	else if (hotel->getRType() == "Deluxe Suite")
		roomNumber = 236;
	else
		roomNumber = 301;



	while (!stop) {

		inventory[index] = *hotel;
		inventory[index].setRoomNumber(roomNumber);

		index++;
		roomNumber++;
		currentSize--;

		if (currentSize == 0)
			stop = true;

	}// end loop

	hotel = nullptr;
	delete hotel;

}// end fillInventory

void Inventory::displayInventory() {

	int cyardCount = 0, scenicCount = 0,
		deluxeCount = 0, pentCount = 0;

	for (int i = 0; i < maxHotelSpace; i++) {

		if (inventory[i].getRType() == "Standard Room: Courtyard")
			cyardCount++;
		else if (inventory[i].getRType() == "Standard Room: Scenic")
			scenicCount++;
		else if (inventory[i].getRType() == "Deluxe Suite")
			deluxeCount++;
		else if (inventory[i].getRType() == "Penthouse")
			pentCount++;

	}// end loop

	cout << "\nCurrent Inventory:\n\n";

	if (cyardCount > 0)
		cout << "(1) Courtyards: " << cyardCount << " Room/s" << endl;
	if (scenicCount > 0)
		cout << "(2) Scenics: " << scenicCount << " Room/s" << endl;
	if (deluxeCount > 0)
		cout << "(3) Deluxes: " << deluxeCount << " Room/s" << endl;
	if (pentCount > 0)
		cout << "(4) Penthouses: " << pentCount << " Room/s" << endl;


}// end displayInventory

void Inventory::reserveRoom(int choice) {

	string guestName;

	cout << "Enter Guest Name >> ";
	getline(cin, guestName);// prevents an error
	getline(cin, guestName);

	for (int i = 0; i < maxHotelSpace; i++) {

		if ((choice == 1) && inventory[i].getRType() == "Standard Room: Courtyard") {
			inventory[i].roomReserved("Reserved");
			reservedCount++;
			addRevenue(inventory[i]);
			inventory[i].setGuest(guestName);
			cout << "\n" << guestName << " Room: " << inventory[i].getRoomNumber() << "\n";
			break;
		}
		else if ((choice == 2) && inventory[i].getRType() == "Standard Room: Scenic") {
			inventory[i].roomReserved("Reserved");
			reservedCount++;
			addRevenue(inventory[i]);
			inventory[i].setGuest(guestName);
			cout << "\n" << guestName << " Room: " << inventory[i].getRoomNumber() << "\n";
			break;
		}
		else if ((choice == 3) && inventory[i].getRType() == "Deluxe Suite") {
			inventory[i].roomReserved("Reserved");
			reservedCount++;
			addRevenue(inventory[i]);
			inventory[i].setGuest(guestName);
			cout << "\n" << guestName << " Room: " << inventory[i].getRoomNumber() << "\n";
			break;
		}
		else if ((choice == 4) && inventory[i].getRType() == "Penthouse") {
			inventory[i].roomReserved("Reserved");
			reservedCount++;
			addRevenue(inventory[i]);
			inventory[i].setGuest(guestName);
			cout << "\n" << guestName << " >> R# " << inventory[i].getRoomNumber() << "\n";
			break;
		}
		/*else if (i == maxHotelSpace - 1)
			cout << "All Rooms Reserved...";*/

	}// end loop

}

bool Inventory::isValidReserve(int choice)
{
	for (int i = 0; i < maxHotelSpace; i++) {

		if ((choice == 1) && inventory[i].getRType() == "Standard Room: Courtyard") {
			return true;
		}
		else if ((choice == 2) && inventory[i].getRType() == "Standard Room: Scenic") {
			return true;
		}
		else if ((choice == 3) && inventory[i].getRType() == "Deluxe Suite") {
			return true;
		}
		else if ((choice == 4) && inventory[i].getRType() == "Penthouse") {
			return true;
		}
		if (i == maxHotelSpace - 1)
			return false;

	}// end loop

}// end isValidReserve

void Inventory::addRevenue(Hotel room) { revenue += room.getCost(); }

int Inventory::getRevenue() { return revenue; }

void Inventory::getRoomsReserved() {

	int cyards = 0, scenics = 0, deluxes = 0, pents = 0;

	for (int i = 0; i < maxHotelSpace; i++) {

		if (inventory[i].getTempRType() == "Standard Room: Courtyard")
			cyards++;
		else if (inventory[i].getTempRType() == "Standard Room: Scenic")
			scenics++;
		else if (inventory[i].getTempRType() == "Deluxe Suite")
			deluxes++;
		else if (inventory[i].getTempRType() == "Penthouse")
			pents++;

	}// end loop

	if (cyards > 0)
		cout << setw(64) << left << "Courtyards: " << setw(8) << right << cyards << endl;
	if (scenics > 0)
		cout << setw(64) << left << "Scenics: " << setw(8) << right << scenics << endl;
	if (deluxes > 0)
		cout << setw(64) << left << "Deluxes: " << setw(8) << right << deluxes << endl;
	if (pents > 0)
		cout << setw(64) << left << "Penthouses: " << setw(8) << right << pents << endl;


}// end getRoomsReserved

int Inventory::getRsvCount()
{
	return reservedCount;
}

void Inventory::recordInformation(string path) {

	fstream dataFile;
	dataFile.open(path, ios::out);

	dataFile << "Guest\t\t\t\t\tRoom #\n\n";

	for (int i = 0; i < maxHotelSpace; i++)
		if(inventory[i].getRType() == "Reserved")
			dataFile<< setw(35) << left << inventory[i].getGuest() << setw(8) << right << inventory[i].getRoomNumber() << endl;

	dataFile << "\n\n" << setw(35) << left << "\nRooms Reserved:" <<
		setw(8) << right << getRsvCount();

	dataFile << setw(35) << left << "\nTotal Revenue:" << setw(2) << left
		<< "$ " << setw(8) << right << getRevenue() << endl;


	dataFile.close();

}// end recordInformation