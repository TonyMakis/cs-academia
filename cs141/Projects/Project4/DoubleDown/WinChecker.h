#pragma once
class WinChecker
{
public:
	int winningIndeces[4] = { 0, 0, 0, 0 };

	int level;
	char board[17];

	WinChecker(int gameLevel, char gameBoard[]);

	bool checkWinners();
};

