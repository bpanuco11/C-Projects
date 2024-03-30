#ifndef BOARD_H
#define BOARD_H

#include "Ship.h"
class Board
{

private:

	Ship ship;
	int subSize = 3, frigSize = 2, destSize = 3,
		batlSize = 4, acSize = 5;
	bool instantVictory = false;
	int wrongHits = 0;
	const static int COLS = 10;
	const static int ROWS = 10;
	string arr[ROWS][COLS];
	void buildDefaultBoardArray(string[][COLS]);
	char shipOrientation();
	bool availableSpace(char, int, int);
	int randomStartingPosition();
	void userCoordinate();
	void displayShot(int, int, bool);

public:
	bool getVictoryResult();
	int getMissedShots();
	void gameOver();
	void shipBoard();
	void displayCompleteBoard();
	void shipHits(int, int);
	void displayHiddenBoard();
	Board() {}
	Board(string[][COLS], Ship[], int);
};
#endif
