#include "Inventory.h"
#ifndef MENU_H
#define MENU_H
class Menu
{
private:
	char savedCommand;
	string saveDate, saveOldDate;
	Inventory inventory;
	void roomReserve();
	void getTotal();
	void mainMenu();
	void date();
	void saveData();
	void getDayInfo();

public:
	Menu();

};
#endif
