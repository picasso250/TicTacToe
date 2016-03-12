#include <tuple>
#include <iostream>
#include <cstdio>
#include <cctype>

#include "FIR.h"

using namespace std;

int main(int argc, char const *argv[])
{
	FIR game;
	char str[25];
	while (!game.isGameOver()) {
		game.print();
		char p = game.isCurPlayer('X') ? 'O' : 'X';
		printf("It is %c's turn\n", p);
		if (p == 'O')
		{
			int x,y;
			tie (x, y) = game.getAI_MoveO();
			// printf("AI move %d, %d\n", x, y);
			if (x == -1)
			{
				cout << "I lose." << endl;
				return -1;
			}
			game.play(x, y, 'O');
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
		if (game.cb[x][y] != ' ')
		{
			printf("%c%c has %c, please chose another move.\n", col, row, game.cb[x][y]);
			continue;
		}
		game.play(x, y, p);
	}
	char winner = game.whoWins();
	if (winner == '-')
	{
		game.print();
		cout << "It's a tie." << endl;
		return 0;
	}
	game.print();
	printf("%c wins!\n", winner);
	return 0;
}
