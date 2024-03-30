#include "Board.h"
#include <random>
#include <ctype.h>
#include <string>

Board::Board(string arr[][COLS], Ship ships[], int fleetSize) {

	/*makes 2d board array accessible*/
	buildDefaultBoardArray(arr);

	for (int i = 0; i < fleetSize; i++) {
		this->ship = ships[i];
		shipBoard();
	}// end for loop

	//displayCompleteBoard();
	displayHiddenBoard();
	userCoordinate();
	gameOver();

}// end 2arg constructor

void Board::shipBoard() {

	string start = "[";
	string closing = "]";
	int shipSize = ship.getSize();
	char* shipParts = new char[shipSize];
	int element = 0;
	char orientation = shipOrientation();

	/*Initialize ship with letters*/
	for (int count = 0; count < shipSize; count++)
		shipParts[count] = ship.getLetter();

	bool error;

	/*will loop if an error occurs while plotting ships*/
	do {

		error = false;

		/*will reset if error*/
		int randStart = randomStartingPosition();
		int randStart2 = randomStartingPosition();

		/*determines if ships can be plotted*/
		bool spaceAvailable = availableSpace(orientation, randStart, randStart2);

		if (orientation == 'V' && spaceAvailable) {

			for (int c = randStart2; c < COLS; c++)
			{

				if ((arr[randStart][c] == "[ ]") && element != ship.getSize()) {

					arr[randStart][c] = start + shipParts[element] + closing;

					element++;

				}// end if 

			}// end for loop

		}// end if

		if (orientation == 'H' && spaceAvailable) {

			for (int r = randStart2; r < ROWS; r++)
			{

				if ((arr[r][randStart] == "[ ]") && element != ship.getSize()) {

					arr[r][randStart] = start + shipParts[element] + closing;

					element++;

				}// end if 
			}// end for loop

		}// end if

		if (!spaceAvailable)
			error = true;

	} while (error);

}// end shipBoard 

void Board::displayCompleteBoard() {

	//Show the current board
	cout << "\t\t\t\t\t     A  B  C  D  E  F  G  H  I  J\n";

	//char columnLetters = 'A';

	for (int r = 0; r < ROWS; r++)
	{
		if (r != 9)
			cout << "\t\t\t\t\t   " << r + 1;
		else
			cout << "\t\t\t\t\t  " << r + 1;

		for (int c = 0; c < COLS; c++)
		{
				cout << arr[r][c];
			
		}// end inner for loop

		if (r == ROWS - 1)
			cout << "\tMisses in a Row: " << getMissedShots() << endl;
		else
			cout << endl;

	}// end for loop

}// end displayCompleteBoard

void Board::buildDefaultBoardArray(string arr[][COLS]) {

	for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < COLS; c++)
		{

			this->arr[r][c] = arr[r][c] = "[ ]";


		}// end inner for loop

	}// end for loop

}// end buildDefaultBoardArray

char Board::shipOrientation() {

	random_device myEngine;
	uniform_int_distribution<int> randomInt(0, 1);
	int randomVal = randomInt(myEngine);

	if (randomVal == 0)
		return 'V';
	else
		return 'H';

}// end shipOrientation

bool Board::availableSpace(char orientation, int val, int val2) {

	bool freeSpace;

	int count = 0;

	if (orientation == 'V') {

		freeSpace = true;

		for (int c = val2; c < COLS; c++)
		{
			if (arr[val][c] != "[ ]")
				freeSpace = false; // force another position

		/*prevents out-of-bounds errors in board*/
			count++;

		}// end  for loop

	}// end if statement

	else {

		freeSpace = true;

		for (int r = val2; r < ROWS; r++)
		{

			if (arr[r][val] != "[ ]")
				freeSpace = false; // force another position

	/*prevents out-of-bounds errors in board*/
			count++;

		}// end for loop

	}//end else

	/*ensures there is enough space for a ship to be plotted*/
	if (count < this->ship.getSize())
		freeSpace = false;

	return freeSpace;

}// end orientationSize

int Board::randomStartingPosition() {

	random_device myEngine;
	uniform_int_distribution<int> randomInt(0, 9);
	int randomVal = randomInt(myEngine);

	return randomVal;

}// end randomStartingPosition function

void Board::userCoordinate() {

	bool hideShips = true;
	bool isFirstCoo = true;
	char tempCoo = ' ';
	string tempCoo2 = "";
	int firstCoordinate = 9;
	int secondCoordinate = 9;

	cout << "\nReminder: Read Rules and Commands Section.\n";

	do {

		if (tempCoo == ' ')
			cout << "\nEnter a Coordinate Commander! ~~> ";

		if (tempCoo == 's' || tempCoo == 'S' || tempCoo == 'z' || tempCoo == 'Z' && !isFirstCoo)
			cout << "\nNext Coordinate Commander! ~~> ";


		cin >> tempCoo;

		if (tempCoo == 'q' || tempCoo == 'Q')
			break;

		if (tempCoo == 's' || tempCoo == 'S') {

			if(isFirstCoo)
				tempCoo = ' ';

			if (hideShips)
				cout << "\nShip Display Activated...\n";
			else
				cout << "\nShip Display Already Active...\n";

			hideShips = false;

			continue;

		}// end if

		if (tempCoo == 'Z' || tempCoo == 'z') {

			if (isFirstCoo)
				tempCoo = ' ';

			if (!hideShips)
				cout << "\nShip Hid Activated...\n";
			else
				cout << "\nShip Hid Already Active...\n";

			hideShips = true;

			continue;

		}// end if

		cin >> tempCoo2;

		bool error = true;

		do {

			if ((tempCoo >= 'A' && tempCoo <= 'J')
				|| (tempCoo >= 'a' && tempCoo <= 'j'))
			{
				error = false;
			}// end if

			if (!isdigit(tempCoo2[0]))
				error = true;
			else
				secondCoordinate = stoi(tempCoo2);

			if (!error && (secondCoordinate < 1 || secondCoordinate > 10))
				error = true;

			if (error) {
				cout << "\nInvalid Coordinate Commander! Try Again! ~~> ";
				cin >> tempCoo;

				if (tempCoo == 'q' || tempCoo == 'Q')
					break;

				if (tempCoo == 's' || tempCoo == 'S') {

					if (hideShips)
						cout << "\nShip Display Activated...\n";
					else
						cout << "\nShip Display Already Active...\n";

					hideShips = false;

					continue;

				}// end if

				if (tempCoo == 'Z' || tempCoo == 'z') {

					if (!hideShips)
						cout << "\nShip Hid Activated...\n";
					else
						cout << "\nShip Hid Already Active...\n ";

					hideShips = true;

					continue;

				}// end if

				cin >> tempCoo2;

			}// end if

		} while (error);

		char letterCaps = 'A';
		int count = 0;

		/*Converts first coordinate to int*/
		for (char letter = 'a'; letter <= 'j'; letter++) {

			if (tempCoo == letter || tempCoo == letterCaps) {
				firstCoordinate = count;
				break;
			}
			else {
				count++;
				letterCaps++;
			}
		}// end loop

		if (arr[secondCoordinate - 1][firstCoordinate] == "[O]" || arr[secondCoordinate - 1][firstCoordinate] == "[X]")
			cout << "\nEnter a Valid Coordinate Commander! ~~> ";

		/*Prevents Hitting the Same Target*/
		if ((tempCoo != 'q' && tempCoo != 'Q') &&
			(arr[secondCoordinate - 1][firstCoordinate] != "[O]" && arr[secondCoordinate - 1][firstCoordinate] != "[X]"))
		{
			displayShot(firstCoordinate, secondCoordinate, hideShips);

			if (instantVictory || wrongHits == 12)
				break;

			isFirstCoo = false;

			cout << "\nNext Coordinate Commander! ~~> ";

		}// end if


	} while (tempCoo != 'q' && tempCoo != 'Q');


}// end userCoordinate function

void Board::displayShot(int coor1, int coor2, bool hideShips) {

	string start = "[", end = "]", mark;

	/*fixes a logic error while plotting*/
	coor2--;

	shipHits(coor2, coor1);

	if (arr[coor2][coor1] != "[ ]") {

		mark = "X";
		wrongHits = 0; //resets wrong hits in a row
	}

	else {

		mark = "O";
		wrongHits++; // adds wrong hits in a row
	}
	arr[coor2][coor1] = start + mark + end;

	if (hideShips)
		displayHiddenBoard();

	else
		displayCompleteBoard();

	/*[coo2][coo1] is due to change in coordinate letters and numbers position*/

}// end displayShot function

void Board::shipHits(int coor2, int coor1) {

	if (arr[coor2][coor1] == "[S]")
		subSize--;
	else if (arr[coor2][coor1] == "[F]")
		frigSize--;
	else if (arr[coor2][coor1] == "[D]")
		destSize--;
	else if (arr[coor2][coor1] == "[B]")
		batlSize--;
	else if (arr[coor2][coor1] == "[A]")
		acSize--;

	if (subSize == 0 && frigSize == 0 && destSize == 0 && batlSize == 0 && acSize == 0)
		instantVictory = true; // game will end after this instruction

}

void Board::gameOver() {

	string message = " ";
	int shipsDown = 0;

	if (wrongHits == 12)
		cout << "\nRetreat! We've Been Exposed!";

	else if (subSize == 0 && frigSize == 0 && destSize == 0 && batlSize == 0 && acSize == 0)
		cout << "\nGood Work Commander! Victory is Ours!";
	else
		cout << "\nDepressing! Better Luck Next Time!";

	if (subSize == 0) {
		message += " |1 Submarine|";
		shipsDown++;
	}

	if (frigSize == 0) {
		message += " |1 Frigate|";
		shipsDown++;
	}

	if (destSize == 0) {
		message += " |1 Destroyer|";
		shipsDown++;
	}

	if (batlSize == 0) {
		message += " |1 Battleship|";
		shipsDown++;
	}

	if (acSize == 0) {
		message += " |1 Aircraft Carrier|";
		shipsDown++;
	}

	if (shipsDown > 0)
	cout << "\nShips Destroyed:" << message;

}

void Board::displayHiddenBoard() {

	//Show the current board
	cout << "\t\t\t\t\t     A  B  C  D  E  F  G  H  I  J\n";

	for (int r = 0; r < ROWS; r++)
	{
		if (r != 9)
			cout << "\t\t\t\t\t   " << r + 1;
		else
			cout << "\t\t\t\t\t  " << r + 1;

		for (int c = 0; c < COLS; c++)
		{

			if (arr[r][c] == "[ ]" || arr[r][c] == "[X]" || arr[r][c] == "[O]")
				cout << arr[r][c];
			else
				cout << "[ ]";

		}// end inner for loop

		if (r == ROWS - 1)
			cout << "\tMisses in a Row: " << getMissedShots() << endl;
		else
			cout << endl;

	}// end for loop

}

int Board::getMissedShots() {return wrongHits;}

bool Board::getVictoryResult() {return instantVictory;}