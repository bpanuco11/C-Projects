#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <string>

using namespace std;

class ChessPiece
{
protected:
	int quantity;
	string pieceType, lCaseType;

public:
	ChessPiece();
	int getQuantity() { return this->quantity; }
	string getPieceType() { return this->pieceType; }
	string getlCaseType() { return this->lCaseType; }

};
#endif

class King : public ChessPiece {

public:
	King() {

		pieceType = "[K]";
		lCaseType = "[k]";
		quantity = 1;

	}


};

class Queen : public ChessPiece {

public:
	Queen() {

		pieceType = "[Q]";
		lCaseType = "[q]";
		quantity = 1;

	}


};

class Rook : public ChessPiece {

public:
	Rook() {

		pieceType = "[R]";
		lCaseType = "[r]";
		quantity = 2;

	}


};

class Knight : public ChessPiece {
public:
	Knight() {

		pieceType = "[H]";
		lCaseType = "[h]";
		quantity = 2;

	}


};

class Bishop : public ChessPiece {

public:
	Bishop() {

		pieceType = "[B]";
		lCaseType = "[b]";
		quantity = 2;

	}


};

class Pawn : public ChessPiece {
public:
	Pawn() {

		pieceType = "[P]";
		lCaseType = "[p]";
		quantity = 8;

	}



};