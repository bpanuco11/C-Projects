#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <array>
#include <iostream>
#include "ChessPiece.h"
#include <vector>
#include <Windows.h>
using namespace std;

class Board
{
private:

	HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);

	const static int COLS = 8;
	const static int ROWS = 8;
	array<array<string, COLS>, ROWS> board;
	ChessPiece* pieces = new ChessPiece[16];
	ChessPiece* pieces2 = new ChessPiece[16];
	vector <int> rowArray;
	vector <int> columnArray;

	void fillPieces();
	void startingBoard();
	void displayBoard();
	void glossary();
	void userCommand();
	bool isCooValid(string, int*, int*);
	void movePiece(int, int);
	void fixCoordinates(int*, int*);
	void pawnMove(int, int, bool, int*);
	void rookMove(int, int, int*);
	void bishopMove(int, int, int*);
	void knightMove(int, int, int*);
	void kingMove(int, int, int*);
	void queenMove(int, int, int*);
	void deleteChoices();
	bool isMoveValid();
	int alphaToNum(char);


public:
	Board();
	~Board();


};
#endif
