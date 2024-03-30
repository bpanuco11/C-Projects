#include "Board.h"
#include <string>
#include <vector>
#include <Windows.h>

Board::Board() {

	userCommand();

}//end no-arg constructor

Board::~Board() {

	pieces = nullptr; 
	pieces2 = nullptr;

	delete pieces, pieces2;

}// end destructor

void Board::fillPieces() {

	cout << "|___________________________________/\\________________/ CHESS"
		<< " \\________________/\\___________________________| v3.0.0\n\n";

	int index = 0, tempIndex = 0, quantity;

	ChessPiece* king = new King();
	ChessPiece* queen = new Queen();
	ChessPiece* knight = new Knight();
	ChessPiece* rook = new Rook();
	ChessPiece* bishop = new Bishop();
	ChessPiece* pawn = new Pawn();

	//fills an inventory full of chess pieces
	for (int index = 0; index < 16; index++) {
		if (index <= 7)
			pieces[index] = *pawn;
		else if (index == 8 || index == 15)
			pieces[index] = *rook;
		else if (index == 9 || index == 14)
			pieces[index] = *knight;
		else if (index == 10 || index == 13)
			pieces[index] = *bishop;
		else if (index == 11)
			pieces[index] = *queen;
		else
			pieces[index] = *king;

	}// end loop

	//upper half
	for (int index = 0; index < 16; index++) {

		if (index == 0 || index == 7)
			pieces2[index] = *rook;
		else if (index == 1 || index == 6)
			pieces2[index] = *knight;
		else if (index == 2 || index == 5)
			pieces2[index] = *bishop;
		else if (index == 3)
			pieces2[index] = *queen;
		else if (index == 4)
			pieces2[index] = *king;
		else
			pieces2[index] = *pawn;

	}// end loop


	king = nullptr;
	queen = nullptr;
	knight = nullptr;
	bishop = nullptr;
	rook = nullptr;
	pawn = nullptr;



	delete king, queen, knight, bishop, rook, pawn;

}// end fillPieces

void Board::startingBoard() {

	fillPieces();
	glossary();

	for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < COLS; c++)
		{
			this->board[r][c] = board[r][c] = "[ ]";

		}
	}// end full loop

	//Prints the starting pieces to their positions; lower half
	for (int index = 0, coo1 = 6, coo2 = 0; index < 16; index++, coo2++) {

		if (coo2 == 8) {
			coo2 = 0;
			coo1 = 7;
		}// end if

		board[coo1][coo2] = pieces[index].getPieceType();

	}// end loop

	/*
	//upper half
	for (int index = 0, coo1 = 0, coo2 = 0; index < 16; index++, coo2++) {

		if (coo2 == 8) {
			coo2 = 0;
			coo1 = 1;
		}// end if

		board[coo1][coo2] = pieces2[index].getlCaseType();

	}// end loop
	*/
}// end startingBoard

void Board::displayBoard() {

	/*used for coloring text*/
	//HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	

	int rowCount = ROWS;

	cout << "\n___________________________________________________________________"
		<< "____________________________________________________\n\n";

	for (int r = 0; r < ROWS; r++)
	{
		cout << "\t\t\t\t\t    " << rowCount-- << "| ";
		for (int c = 0; c < COLS; c++)
		{
			if (isdigit(board[r][c][1]) || islower(board[r][c][1])) {
				SetConsoleTextAttribute(console_color, 11);
				cout << board[r][c];
				SetConsoleTextAttribute(console_color, 7);
			}
			else
				cout << board[r][c];
		}

		cout << endl;
	}// end full loop

	cout << "\t\t\t\t\t     | ________________________";
	cout << "\n\t\t\t\t\t        1  2  3  4  5  6  7  8 \n\n";
	cout << "___________________________________________________________________"
		<< "____________________________________________________\n\n";

}// end displayBoard

void Board::glossary() {

	cout << "\t(Commands)\t\t\t\t\t\t\t\t\t\t(Glossary)"
		<< "\n\t\t\t\t\t\t\t\t\t\t\t(P|p): Pawn  (H|h): Horse"
		<< "\n(R/r): Restart  (Q/q): Quit\t\t\t\t\t\t\t\t(R|r): Rook  (B|b): Bishop"
		<< "\n\t\t\t\t\t\t\t\t\t\t\t(Q|q): Queen (K|k): King"
		<< "\n";

}// end glossary

void Board::userCommand() {

	string tempCoo = "";
	int coo1 = 0, coo2 = 0;
	bool rangeError = false;

	/*Starting Board Displayed*/
	startingBoard();
	displayBoard();


	while (tempCoo[0] != 'Q' && tempCoo[0] != 'q') {

		if (!rangeError) {
			cout << "(R/r): Restart  \t(Q/q): Quit\n\n";
			cout << "Enter a chess piece coordinate or a command >> ";
			getline(cin, tempCoo);
		}// does not execute if there is a range error prior

		if (tempCoo[0] == 'Q' || tempCoo[0] == 'q') {
			SetConsoleTextAttribute(console_color, 10); //set text to green
			cout << "\nQuit Successful...\n\n";
			SetConsoleTextAttribute(console_color, 7); //set text to gray
			break;
		}
		if (tempCoo[0] == 'R' || tempCoo[0] == 'r') {

			/*restart and paint text red*/
			SetConsoleTextAttribute(console_color, 10); //set text to green
			cout << "\nRestart Successful...\n\n";
			SetConsoleTextAttribute(console_color, 7); //set text to gray

			startingBoard();
			displayBoard();
			continue;

		}// end restart if

		/*Run a loop if coordinates are invalid*/
		while (!isCooValid(tempCoo, &coo1, &coo2)) {
			SetConsoleTextAttribute(console_color, 12); //set text to red
			cout << "\nError... Try Again >> ";
			SetConsoleTextAttribute(console_color, 7); //set text to gray
			getline(cin, tempCoo);
		}// end inner loop

		if ((coo1 > 0 && coo1 <= 8) && (coo2 > 0 && coo2 <= 8)) {

			rangeError = false;
			movePiece(coo1, coo2);

		}// end if

		else {
			SetConsoleTextAttribute(console_color, 12); //set text to red
			cout << "\nRange Error... Try Again >> ";
			SetConsoleTextAttribute(console_color, 7); //set text to gray
			getline(cin, tempCoo);
			rangeError = true;
			continue;
		}// range index error

		cout << "\n";

	}// end loop


}// end userCommand()

bool Board::isCooValid(string coordinate, int* coo1, int* coo2) {

	int validCount = 0;
	*coo1 = 0, * coo2 = 0;

	if (coordinate[0] == 'Q' || coordinate[0] == 'q'
		|| coordinate[0] == 'R' || coordinate[0] == 'r')
		return true;

	for (int index = 0; index < coordinate.size(); index++) {

		if (isdigit(coordinate[index])) {
			validCount++;

			if (*coo1 == 0) {

				*coo1 = int(coordinate[index]) - 48;
				continue;

			}// end inner if1
			if (*coo2 == 0) {

				*coo2 = int(coordinate[index]) - 48;
				continue;

			}// end inner if2

		}// end outter if

		if (isalpha(coordinate[index]))
			return false;

	}// end loop

	if (validCount == 2)
		return true;
	else
		return false;

}//isCooValid()

void Board::movePiece(int coo1, int coo2) {

	string piece, tempChoice;
	bool repeat = true;
	int choice = 0, allowedChoices = 0;

	/*Adjust correct intended coordinates*/
	fixCoordinates(&coo1, &coo2);

	/*record pawn movement*/
	if (board[coo1][coo2] == "[P]" && coo1 - 1 != -1) {

		piece = "[P]";

		if (coo1 != 6)
			pawnMove(coo1, coo2, false, &allowedChoices);
		else
			pawnMove(coo1, coo2, true, &allowedChoices);

	}// end pawn movement algorithm

	/*record rook movement*/
	else if (board[coo1][coo2] == "[R]") {

		piece = "[R]";

		rookMove(coo1, coo2, &allowedChoices);

	}// end rook movement algorithm

	/*record king movement*/
	else if (board[coo1][coo2] == "[K]") {

		piece = "[K]";

		kingMove(coo1, coo2, &allowedChoices);

	}// end king movement algorithm

	/*record bishop movement*/
	else if (board[coo1][coo2] == "[B]") {

		piece = "[B]";
		bishopMove(coo1, coo2, &allowedChoices);
	}// end bishop movement algorithm

	/*record knight movement*/
	else if (board[coo1][coo2] == "[H]") {

		piece = "[H]";
		knightMove(coo1, coo2, &allowedChoices);

	}// end knight move algorithm

	/*record queen movement*/
	else if (board[coo1][coo2] == "[Q]") {

		piece = "[Q]";

		queenMove(coo1, coo2, &allowedChoices);

	}// end queen move algorithm

	/*checks if piece can move*/
	if (!isMoveValid()) {

		SetConsoleTextAttribute(console_color, 12); //set text to red
		cout << "\nPiece Error, Choose a Movable Piece...\n";
		SetConsoleTextAttribute(console_color, 7); //set text to gray
		return;
	}// end move validation

	displayBoard();

	/*choose a piece move given by number or character*/
	while (repeat) {
		cout << "Choose a # or letter to move your " << piece << " >> ";
		getline(cin, tempChoice);

		for (int i = 0; i < tempChoice.size(); i++) {

			if (isdigit(tempChoice[i]))
				choice = int(tempChoice[i]) - 48;

			else if (isalpha(tempChoice[i]))
				choice = alphaToNum(tempChoice[i]);

			if (choice <= allowedChoices && choice > 0) {
				repeat = false;
				break;
			}// end inner if

		}// end inner loop

		/*plots new piece and delete previous one*/
		if (!repeat) {
			board[coo1][coo2] = "[ ]";
			board[rowArray[choice - 1]][columnArray[choice - 1]] = piece;
			deleteChoices();

		}// end if

		else {
			SetConsoleTextAttribute(console_color, 12); //set text to red
			cout << "\nError, Invalid Choice...\n";
			SetConsoleTextAttribute(console_color, 7); //set text to gray
		}
	}// end outter loop

	displayBoard();

}// end movePiece()

void Board::fixCoordinates(int* coo1, int* coo2) {

	if (*coo1 == 1)
		*coo1 = 7;
	else if (*coo1 == 2)
		*coo1 = 6;
	else if (*coo1 == 3)
		*coo1 = 5;
	else if (*coo1 == 5)
		*coo1 = 3;
	else if (*coo1 == 6)
		*coo1 = 2;
	else if (*coo1 == 7)
		*coo1 = 1;
	else if (*coo1 == 8)
		*coo1 = 0;

	*coo2 -= 1;

}// end fixCoordinates()

void Board::pawnMove(int coo1, int coo2, bool secondMove, int* allowedChoices) {

	/*another piece blocks movement*/
	if (isalpha(board[coo1 - 1][coo2][1]))
		return;

	board[coo1 - 1][coo2] = "[1]";
	rowArray.push_back(coo1 - 1);
	columnArray.push_back(coo2);
	*allowedChoices += 1;

	if (secondMove) {

		/*another piece blocks movement*/
		if (isalpha(board[coo1 - 2][coo2][1]))
			return;

		board[coo1 - 2][coo2] = "[2]";
		rowArray.push_back(coo1 - 2);
		columnArray.push_back(coo2);
		*allowedChoices += 1;
	}// end if

}// end pawnMove()

void Board::rookMove(int coo1, int coo2, int* allowedChoices) {

	int rowSize, colSize;
	string open = "[", close = "]";
	char letter = '`';

	//up
	rowSize = coo1;
	for (int i = 1; i <= rowSize; i++) {

		/*another piece blocks movement*/
		if (isalpha(board[coo1 - i][coo2][1]))
			break;

		*allowedChoices += 1;
		string number = to_string(*allowedChoices);
		board[coo1 - i][coo2] = open + number + close;
		rowArray.push_back(coo1 - i);
		columnArray.push_back(coo2);

	}// end up move

	//down
	rowSize = ROWS - coo1;
	for (int i = 1; i < rowSize; i++) {


		/*another piece blocks movement*/
		if (isalpha(board[coo1 + i][coo2][1]))
			break;

		*allowedChoices += 1;
		string number = to_string(*allowedChoices);
		board[coo1 + i][coo2] = open + number + close;
		rowArray.push_back(coo1 + i);
		columnArray.push_back(coo2);

	}// end down move

	//right
	colSize = COLS - coo2;
	for (int i = 1; i < colSize; i++) {

		/*another piece blocks movement*/
		if (isalpha(board[coo1][coo2 + i][1]))
			break;

		*allowedChoices += 1;
		if (*allowedChoices >= 10) {

			letter++;
			board[coo1][coo2 + i] = open + letter + close;
		}
		else {

			string number = to_string(*allowedChoices);
			board[coo1][coo2 + i] = open + number + close;

		}
		rowArray.push_back(coo1);
		columnArray.push_back(coo2 + i);

	}// end right move

	//left
	colSize = coo2;
	for (int i = 1; i <= colSize; i++) {

		/*another piece blocks movement*/
		if (isalpha(board[coo1][coo2 - i][1]))
			break;

		*allowedChoices += 1;
		if (*allowedChoices >= 10) {
			letter++;
			board[coo1][coo2 - i] = open + letter + close;
		}
		else {
			string number = to_string(*allowedChoices);
			board[coo1][coo2 - i] = open + number + close;
		}
		rowArray.push_back(coo1);
		columnArray.push_back(coo2 - i);

	}// end left move


}// end rookMove()

void Board::bishopMove(int coo1, int coo2, int* allowedChoices) {

	int i = 0;
	string open = "[", close = "]";
	char letter = '`';

	//diagonal up-right
	while (coo1 - i != 0 && coo2 + i != 7) {

		i++;

		/*another piece blocks movement*/
		if (isalpha(board[coo1 - i][coo2 + i][1]))
			break;

		*allowedChoices += 1;
		if (*allowedChoices >= 10) {

			letter++;
			board[coo1 - i][coo2 + i] = open + letter + close;
		}
		else {

			string number = to_string(*allowedChoices);
			board[coo1 - i][coo2 + i] = open + number + close;

		}
		rowArray.push_back(coo1 - i);
		columnArray.push_back(coo2 + i);

	}// end diagonal up-right

	i = 0;
	//diagonal up-left
	while (coo1 - i != 0 && coo2 - i != 0) {

		i++;

		/*another piece blocks movement*/
		if (isalpha(board[coo1 - i][coo2 - i][1]))
			break;

		*allowedChoices += 1;
		if (*allowedChoices >= 10) {

			letter++;
			board[coo1 - i][coo2 - i] = open + letter + close;
		}
		else {

			string number = to_string(*allowedChoices);
			board[coo1 - i][coo2 - i] = open + number + close;

		}
		rowArray.push_back(coo1 - i);
		columnArray.push_back(coo2 - i);

	}// end diagonal up-left

	i = 0;
	//diagonal down-left
	while (coo1 + i != 7 && coo2 - i != 0) {

		i++;

		/*another piece blocks movement*/
		if (isalpha(board[coo1 + i][coo2 - i][1]))
			break;

		*allowedChoices += 1;
		if (*allowedChoices >= 10) {

			letter++;
			board[coo1 + i][coo2 - i] = open + letter + close;
		}
		else {

			string number = to_string(*allowedChoices);
			board[coo1 + i][coo2 - i] = open + number + close;

		}
		rowArray.push_back(coo1 + i);
		columnArray.push_back(coo2 - i);

	}// end diagonal down-left

	i = 0;
	//diagonal down-right
	while (coo1 + i != 7 && coo2 + i != 7) {

		i++;

		/*another piece blocks movement*/
		if (isalpha(board[coo1 + i][coo2 + i][1]))
			break;

		*allowedChoices += 1;
		if (*allowedChoices >= 10) {

			letter++;
			board[coo1 + i][coo2 + i] = open + letter + close;
		}
		else {

			string number = to_string(*allowedChoices);
			board[coo1 + i][coo2 + i] = open + number + close;

		}
		rowArray.push_back(coo1 + i);
		columnArray.push_back(coo2 + i);

	}// end diagonal down-right


}// end bishopMove()

void Board::knightMove(int coo1, int coo2, int* allowedChoices) {

	int row, col;
	string open = "[", close = "]";

	// to move up
	row = coo1 - 2; col = coo2 + 1;
	if (row >= 0 && row < 8 && col >= 0 && col < 8)
	{
		if (!isalpha(board[row][col][1])) {

			*allowedChoices += 1;
			string number = to_string(*allowedChoices);
			board[row][col] = open + number + close;
			rowArray.push_back(row);
			columnArray.push_back(col);
		}// runs if no piece is in the way
	}
	row = coo1 - 1; col = coo2 + 2;
	if (row >= 0 && row < 8 && col >= 0 && col < 8)
	{
		if (!isalpha(board[row][col][1])) {

			*allowedChoices += 1;
			string number = to_string(*allowedChoices);
			board[row][col] = open + number + close;
			rowArray.push_back(row);
			columnArray.push_back(col);
		}// runs if no piece is in the way
	}

	// to move right
	row = coo1 + 1; col = coo2 + 2;
	if (row >= 0 && row < 8 && col >= 0 && col < 8)
	{
		if (!isalpha(board[row][col][1])) {

			*allowedChoices += 1;
			string number = to_string(*allowedChoices);
			board[row][col] = open + number + close;
			rowArray.push_back(row);
			columnArray.push_back(col);
		}// runs if no piece is in the way
	}
	row = coo1 + 2; col = coo2 + 1;
	if (row >= 0 && row < 8 && col >= 0 && col < 8)
	{
		if (!isalpha(board[row][col][1])) {

			*allowedChoices += 1;
			string number = to_string(*allowedChoices);
			board[row][col] = open + number + close;
			rowArray.push_back(row);
			columnArray.push_back(col);
		}// runs if no piece is in the way
	}

	// to move down
	row = coo1 + 2; col = coo2 - 1;
	if (row >= 0 && row < 8 && col >= 0 && col < 8)
	{
		if (!isalpha(board[row][col][1])) {

			*allowedChoices += 1;
			string number = to_string(*allowedChoices);
			board[row][col] = open + number + close;
			rowArray.push_back(row);
			columnArray.push_back(col);
		}// runs if no piece is in the way
	}
	row = coo1 + 1; col = coo2 - 2;
	if (row >= 0 && row < 8 && col >= 0 && col < 8)
	{
		if (!isalpha(board[row][col][1])) {

			*allowedChoices += 1;
			string number = to_string(*allowedChoices);
			board[row][col] = open + number + close;
			rowArray.push_back(row);
			columnArray.push_back(col);
		}// runs if no piece is in the way
	}

	// to move left
	row = coo1 - 1; col = coo2 - 2;
	if (row >= 0 && row < 8 && col >= 0 && col < 8)
	{
		if (!isalpha(board[row][col][1])) {

			*allowedChoices += 1;
			string number = to_string(*allowedChoices);
			board[row][col] = open + number + close;
			rowArray.push_back(row);
			columnArray.push_back(col);
		}// runs if no piece is in the way
	}
	row = coo1 - 2; col = coo2 - 1;
	if (row >= 0 && row < 8 && col >= 0 && col < 8)
	{
		if (!isalpha(board[row][col][1])) {

			*allowedChoices += 1;
			string number = to_string(*allowedChoices);
			board[row][col] = open + number + close;
			rowArray.push_back(row);
			columnArray.push_back(col);
		}// runs if no piece is in the way
	}

}// end knightMove()

void Board::kingMove(int coo1, int coo2, int* allowedChoices) {

	int rowSize, colSize;
	string open = "[", close = "]";

	//up
	if (coo1 != 0 && !isalpha(board[coo1 - 1][coo2][1])) {

		*allowedChoices += 1;
		string number = to_string(*allowedChoices);
		board[coo1 - 1][coo2] = open + number + close;
		rowArray.push_back(coo1 - 1);
		columnArray.push_back(coo2);

	}// end up move

	//down
	if (coo1 != 7 && !isalpha(board[coo1 + 1][coo2][1])) {

		*allowedChoices += 1;
		string number = to_string(*allowedChoices);
		board[coo1 + 1][coo2] = open + number + close;
		rowArray.push_back(coo1 + 1);
		columnArray.push_back(coo2);

	}// end down move

	//left
	if (coo2 != 0 && !isalpha(board[coo1][coo2 - 1][1])) {

		*allowedChoices += 1;
		string number = to_string(*allowedChoices);
		board[coo1][coo2 - 1] = open + number + close;
		rowArray.push_back(coo1);
		columnArray.push_back(coo2 - 1);

	}// end left move

	//right
	if (coo2 != 7 && !isalpha(board[coo1][coo2 + 1][1])) {

		*allowedChoices += 1;
		string number = to_string(*allowedChoices);
		board[coo1][coo2 + 1] = open + number + close;
		rowArray.push_back(coo1);
		columnArray.push_back(coo2 + 1);

	}// end right move

	//diagonal up-right
	if ((coo1 != 0 && coo2 != 7) && !isalpha(board[coo1 - 1][coo2 + 1][1])) {

		*allowedChoices += 1;
		string number = to_string(*allowedChoices);
		board[coo1 - 1][coo2 + 1] = open + number + close;
		rowArray.push_back(coo1 - 1);
		columnArray.push_back(coo2 + 1);

	}// end diagonal up-right

	//diagonal up-left
	if ((coo1 != 0 && coo2 != 0) && !isalpha(board[coo1 - 1][coo2 - 1][1])) {

		*allowedChoices += 1;
		string number = to_string(*allowedChoices);
		board[coo1 - 1][coo2 - 1] = open + number + close;
		rowArray.push_back(coo1 - 1);
		columnArray.push_back(coo2 - 1);

	}// end diagonal up-left

	//diagonal down-left
	if ((coo1 != 7 && coo2 != 0) && !isalpha(board[coo1 + 1][coo2 - 1][1])) {

		*allowedChoices += 1;
		string number = to_string(*allowedChoices);
		board[coo1 + 1][coo2 - 1] = open + number + close;
		rowArray.push_back(coo1 + 1);
		columnArray.push_back(coo2 - 1);

	}// end diagonal down-left

	//diagonal down-right
	if ((coo1 != 7 && coo2 != 7) && !isalpha(board[coo1 + 1][coo2 + 1][1])) {

		*allowedChoices += 1;
		string number = to_string(*allowedChoices);
		board[coo1 + 1][coo2 + 1] = open + number + close;
		rowArray.push_back(coo1 + 1);
		columnArray.push_back(coo2 + 1);

	}// end diagonal down-right

}// end kingMove()

void Board::queenMove(int coo1, int coo2, int* allowedChoices) {

	int rowSize, colSize, i = 0;
	string open = "[", close = "]";
	char letter = '`';

	//up
	rowSize = coo1;
	for (int i = 1; i <= rowSize; i++) {

		/*another piece blocks movement*/
		if (isalpha(board[coo1 - i][coo2][1]))
			break;

		*allowedChoices += 1;
		string number = to_string(*allowedChoices);
		board[coo1 - i][coo2] = open + number + close;
		rowArray.push_back(coo1 - i);
		columnArray.push_back(coo2);

	}// end up move

	//down
	rowSize = ROWS - coo1;
	for (int i = 1; i < rowSize; i++) {


		/*another piece blocks movement*/
		if (isalpha(board[coo1 + i][coo2][1]))
			break;

		*allowedChoices += 1;
		string number = to_string(*allowedChoices);
		board[coo1 + i][coo2] = open + number + close;
		rowArray.push_back(coo1 + i);
		columnArray.push_back(coo2);

	}// end down move

	//right
	colSize = COLS - coo2;
	for (int i = 1; i < colSize; i++) {

		/*another piece blocks movement*/
		if (isalpha(board[coo1][coo2 + i][1]))
			break;

		*allowedChoices += 1;
		if (*allowedChoices >= 10) {

			letter++;
			board[coo1][coo2 + i] = open + letter + close;
		}
		else {

			string number = to_string(*allowedChoices);
			board[coo1][coo2 + i] = open + number + close;

		}
		rowArray.push_back(coo1);
		columnArray.push_back(coo2 + i);

	}// end right move

	//left
	colSize = coo2;
	for (int i = 1; i <= colSize; i++) {

		/*another piece blocks movement*/
		if (isalpha(board[coo1][coo2 - i][1]))
			break;

		*allowedChoices += 1;
		if (*allowedChoices >= 10) {
			letter++;
			board[coo1][coo2 - i] = open + letter + close;
		}
		else {
			string number = to_string(*allowedChoices);
			board[coo1][coo2 - i] = open + number + close;
		}
		rowArray.push_back(coo1);
		columnArray.push_back(coo2 - i);

	}// end left move

	//diagonal up-right
	while (coo1 - i != 0 && coo2 + i != 7) {

		i++;

		/*another piece blocks movement*/
		if (isalpha(board[coo1 - i][coo2 + i][1]))
			break;

		*allowedChoices += 1;
		if (*allowedChoices >= 10) {

			letter++;
			board[coo1 - i][coo2 + i] = open + letter + close;
		}
		else {

			string number = to_string(*allowedChoices);
			board[coo1 - i][coo2 + i] = open + number + close;

		}
		rowArray.push_back(coo1 - i);
		columnArray.push_back(coo2 + i);

	}// end diagonal up-right

	i = 0;
	//diagonal up-left
	while (coo1 - i != 0 && coo2 - i != 0) {

		i++;

		/*another piece blocks movement*/
		if (isalpha(board[coo1 - i][coo2 - i][1]))
			break;

		*allowedChoices += 1;
		if (*allowedChoices >= 10) {

			letter++;
			board[coo1 - i][coo2 - i] = open + letter + close;
		}
		else {

			string number = to_string(*allowedChoices);
			board[coo1 - i][coo2 - i] = open + number + close;

		}
		rowArray.push_back(coo1 - i);
		columnArray.push_back(coo2 - i);

	}// end diagonal up-left

	i = 0;
	//diagonal down-left
	while (coo1 + i != 7 && coo2 - i != 0) {

		i++;

		/*another piece blocks movement*/
		if (isalpha(board[coo1 + i][coo2 - i][1]))
			break;

		*allowedChoices += 1;
		if (*allowedChoices >= 10) {

			letter++;
			board[coo1 + i][coo2 - i] = open + letter + close;
		}
		else {

			string number = to_string(*allowedChoices);
			board[coo1 + i][coo2 - i] = open + number + close;

		}
		rowArray.push_back(coo1 + i);
		columnArray.push_back(coo2 - i);

	}// end diagonal down-left

	i = 0;
	//diagonal down-right
	while (coo1 + i != 7 && coo2 + i != 7) {

		i++;

		/*another piece blocks movement*/
		if (isalpha(board[coo1 + i][coo2 + i][1]))
			break;

		*allowedChoices += 1;
		if (*allowedChoices >= 10) {

			letter++;
			board[coo1 + i][coo2 + i] = open + letter + close;
		}
		else {

			string number = to_string(*allowedChoices);
			board[coo1 + i][coo2 + i] = open + number + close;

		}
		rowArray.push_back(coo1 + i);
		columnArray.push_back(coo2 + i);

	}// end diagonal down-right


}// end queenMove()

void Board::deleteChoices() {

	for (int r = 0; r < ROWS; r++)
	{

		for (int c = 0; c < COLS; c++)
		{
			if (isdigit(board[r][c][1]) || islower(board[r][c][1]))
				board[r][c] = "[ ]";
		}

	}// end full loop

	rowArray.clear();
	columnArray.clear();

}// end deleteChoices

bool Board::isMoveValid() {

	for (int r = 0; r < ROWS; r++)
	{

		for (int c = 0; c < COLS; c++)
		{
			if (isdigit(board[r][c][1]))
				return true;
		}

	}// end full loop

	return false;

}// end isMoveValid()

int Board::alphaToNum(char userChar) {

	int number = 10;

	for (char letter = 'a'; letter < 'z'; letter++, number++) {

		if (userChar == letter)
			return number;

	}// end loop

}// end alphaToNum()