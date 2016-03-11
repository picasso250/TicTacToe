#include <tuple>
#include <iostream>
#include <cstdio>
#include <cctype>

#include "TicTacToe.h"

using namespace std;

int main(int argc, char const *argv[])
{
	TicTacToe ttt;
	char str[25];
	while (!ttt.isGameOver()) {
		ttt.print();
		char p = ttt.isCurPlayer('X') ? 'O' : 'X';
		printf("It is %c's turn\n", p);
		if (p == 'O')
		{
			int x,y;
			std::tie (x, y) = ttt.getAI_MoveO();
			// printf("AI move %d, %d\n", x, y);
			if (x == -1)
			{
				cout << "I lose." << endl;
				return -1;
			}
			ttt.play(x, y, 'O');
			continue;
		}
		cin.getline(str, 25);
		char col = toupper(str[0]);
		char row = str[1];
		if (col == 'Q')
		{
			return 0;
		}
		if (col < 'A' || col > 'C') {
			perror("must A-C");
			return 1;
		}
		if (row < '1' || row > '3')
		{
			perror("must be 1-3");
			return 1;
		}
		int x = row - '1';
		int y = col - 'A';
		if (ttt.cb[x][y] != ' ')
		{
			printf("%c%c has %c, please chose another move.\n", col, row, ttt.cb[x][y]);
			continue;
		}
		ttt.play(x, y, p);
	}
	char winner = ttt.whoWins();
	if (winner == '-')
	{
		cout << "It's a tie." << endl;
		return 0;
	}
	printf("%c wins!.\n", winner);
	return 0;
}
