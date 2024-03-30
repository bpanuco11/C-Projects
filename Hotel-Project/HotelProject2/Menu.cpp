#include "Menu.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

Menu::Menu() {

	date();
	mainMenu();
	saveData();

}// end no-arg constructor

void Menu::roomReserve() {


	string tempChoice;
	bool repeat = true, validChoice = false;

	int choice = 0;

	while (repeat) {

		cout << "\nMenu:(M)\tQuit:(Q)\n";
		cout << "\nEnter a command or a value(1-4) to reserve a room >> ";
		cin >> tempChoice;

		if (tempChoice[0] == 'M' || tempChoice[0] == 'm' || tempChoice[0] == 'Q' || tempChoice[0] == 'q') {
			savedCommand = tempChoice[0];
			cout << "\n";
			break;
		}

		if (isdigit(tempChoice[0]))
			choice = stoi(tempChoice);


		while (!isdigit(tempChoice[0]) || (choice < 1 || choice > 4) || !inventory.isValidReserve(choice)) {

			cout << "Invalid Input... Try Again >> ";
			cin >> tempChoice;

			if (tempChoice[0] == 'M' || tempChoice[0] == 'm' || tempChoice[0] == 'Q' || tempChoice[0] == 'q') {
				repeat = false;
				savedCommand = tempChoice[0];
				cout << "\n";
				break;
			}

			if (isdigit(tempChoice[0]))
				choice = stoi(tempChoice);

		}// end inner loop

		if (tempChoice[0] != 'M' && tempChoice[0] != 'm' && tempChoice[0] != 'Q' && tempChoice[0] != 'q') {
			inventory.reserveRoom(choice);
			cout << "\n";
			inventory.displayInventory();
			cout << "\n";
		}

	}// end loop

}// end roomReserve

void Menu::getTotal() {

	cout << "\n" << setw(65) << left << "\nRooms Reserved:" <<
		setw(8) << right << inventory.getRsvCount() << "\n\n";

	inventory.getRoomsReserved();

	cout << "\n" << setw(65) << left << "\nTotal Revenue:" << setw(2) << left
		<< "$ " << setw(8) << right << inventory.getRevenue() << endl;

}

void Menu::mainMenu() {

	bool repeat = true;
	string tempChoice;

	cout << "\n\nCommands:\n\n(M) Enter 'M' or 'm' to return to the Menu.";
	cout << "\n(R) Enter 'R' or 'r' to reserve a room";
	cout << "\n(T) Enter 'T' or 't' to display the total revenue";
	cout << "\n(D) Enter 'D' or 'd' to display previous days receipts";
	cout << "\n(Q) Enter 'Q' or 'q' to quit program.\n\n\n\n";

	while (repeat) {

		cout << "Reserve Room: (R)\tTotal Revenue: (T)\tDay Receipt: (D)\tQuit: (Q)\n\n";
		cout << "Enter a choice (R,T,D,Q) >> ";
		cin >> tempChoice;

		while (tempChoice[0] != 'Q' && tempChoice[0] != 'q' && tempChoice[0] != 'R' && tempChoice[0] != 'r'
			&& tempChoice[0] != 'T' && tempChoice[0] != 't' && tempChoice[0] != 'D' && tempChoice[0] != 'd') {

			cout << "Error... enter a valid choice (R,T,D,Q) >> ";
			cin >> tempChoice;
		}

		if (tempChoice[0] == 'Q' || tempChoice[0] == 'q')
			break;

		if (tempChoice[0] == 'R' || tempChoice[0] == 'r') {

			inventory.displayInventory();
			roomReserve();

			if (savedCommand == 'Q' || savedCommand == 'q')
				break;
			else
				continue;

		}// end if statement

		if (tempChoice[0] == 'T' || tempChoice[0] == 't')
			getTotal();

		if (tempChoice[0] == 'D' || tempChoice[0] == 'd') {

			date();
			getDayInfo();
			
		}

		cout << "\n";

	}// end loop

}// end mainMenu

void Menu::date() {

	string date,tempDate = "";
	static bool isTodaysDate = true;
	bool error = true;
	int month, day, year;

	if (isTodaysDate) {
		cout << "Please Enter Today's Date (Ex: 08 16 2022) >> ";
		getline(cin, date);
	}// end if
	else {
		getline(cin, date);// removes an error
		cout << "\nPlease Enter a Date to Retrieve (Ex: 05 26 2012) >> ";
		getline(cin, date);
	}

	while (error) {

		if (date.length() == 10 && isdigit(date[0]) && isdigit(date[1]) && isdigit(date[3]) && isdigit(date[4]) 
			&& isdigit(date[6])&& isdigit(date[7]) && isdigit(date[8]) && isdigit(date[9])) {

			tempDate = tempDate + date[0] + date[1];
			month = stoi(tempDate);
			//cout << month;
			tempDate = "";

			tempDate = tempDate + date[3] + date[4];
			day = stoi(tempDate);
			//cout << day;
			tempDate = "";

			tempDate = tempDate + date[6] + date[7] + date[8] + date[9];
			year = stoi(tempDate);
			//cout << year;
			tempDate = "";

			if (month>12)
				error = true;
			else if (day>31)
				error = true;
			else
				error = false;
		}// end if

		if(error) {
			cout << "\nError... Enter Date as MM DD YYYY >> ";
			getline(cin, date);
			continue;
		}

		if (isTodaysDate) {

			saveDate = "";
			saveDate = saveDate + date[0] + date[1] + "-" + date[3] + date[4] + "-"
				+ date[6] + date[7] + date[8] + date[9];

			isTodaysDate = false;
		}// end if
		else {

			saveOldDate = "";
			saveOldDate = saveOldDate + date[0] + date[1] + "-" + date[3] + date[4] + "-"
				+ date[6] + date[7] + date[8] + date[9];

		}// end else

	}// end loop

}// end date

void Menu::saveData() {

	string path = "C:\\Users\\Brandon\\OneDrive\\Desktop\\C++\\Interm C++\\Hotel Project\\Guest_Data\\"
		+ saveDate + ".txt";

	inventory.recordInformation(path);

}// end saveData

void Menu::getDayInfo() {
	
	string sentence;
	fstream dataFile;

	string path = "C:\\Users\\Brandon\\OneDrive\\Desktop\\C++\\Interm C++\\Hotel Project\\Guest_Data\\"
		+ saveOldDate + ".txt";

	dataFile.open(path, ios::in);

	if (dataFile.fail())
		cout << "\nAn Error has Occurred...";
	else {

		cout << "\nDate: "<< saveOldDate<<"\n\n";
		while (getline(dataFile, sentence, '\n')) {

			cout << sentence << endl;
		}// end loop
		dataFile.close();
		cout << "\n\n";
	}
}// end getDayInfo
