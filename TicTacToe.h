#include <iostream>
#include <cstdio>

using namespace std;

struct TicTacToe {
	static const int SIZE = 3;

	// 'X' 黑棋
	// 'O' 白棋
	// ' ' 没有棋子
	// chess board
	char cb[SIZE][SIZE];
	short x;
	short y;
	TicTacToe() : x(-1), y(-1)
	{
		for (int i = 0; i < SIZE; ++i)
		{
			for (int j = 0; j < SIZE; ++j)
			{
				cb[i][j] = ' ';
			}
		}
	}
	void print()
	{
		printColNum();
		for (int i = 0; i < SIZE; ++i)
		{
			int j = -1;
			printf("%d%c", i+1, getBracketChar(i, j));
			for (j = 0; j < SIZE; ++j)
			{
				printf("%c%c", cb[i][j], getBracketChar(i, j));
			}
			cout << i+1 << endl;
		}
		printColNum();
	}
	char getBracketChar(int i, int j)
	{
		char c = ' ';
		if (i == x)
		{
			if (j == y)
			{
				return ')';
			} else if (j+1 == y) {
				return '(';
			}
		}
		return c;
	}
	void printColNum()
	{
		cout<<"  ";
		for (int i = 0; i < SIZE; ++i)
		{
			printf("%c ", i+'A');
		}
		cout<<endl;
	}
	bool isGameOver()
	{
		if (whoWins() != '-')
		{
			return true;
		}
		for (int i = 0; i < SIZE; ++i)
		{
			for (int j = 0; j < SIZE; ++j)
			{
				if (cb[i][j] == ' ')
				{
					return false;
				}
			}
		}
		return true;
	}
	// return X|O|-
	// X胜 | O胜 | 平局或者没有结果
	char whoWins()
	{
		char c = isRow();
		if (c != '-') {
			return c;
		}
		c = isCol();
		if (c != '-') {
			return c;
		}
		return isX();
	}
	char isRow() {
		for (int i = 0; i < SIZE; ++i)
		{
			if (cb[i][0] != ' ' && cb[i][0] == cb[i][1] && cb[i][1] == cb[i][2])
			{
				return cb[i][0];
			}
		}
		// cout<<"will return - row"<<endl;
		return '-';
	}
	char isCol() {
		for (int j = 0; j < SIZE; ++j)
		{
			if (cb[0][j] != ' ' && cb[0][j] == cb[1][j] && cb[1][j] == cb[2][j])
			{
				return cb[0][j];
			}
		}
		// cout<<"will return - col"<<endl;
		return '-';
	}
	char isX() {
		if (cb[1][1] == ' ')
		{
			return '-';
		}
		if (cb[0][0] == cb[1][1] && cb[1][1] == cb[2][2])
		{
			return cb[0][0];
		}
		if (cb[0][2] == cb[1][1] && cb[1][1] == cb[2][0])
		{
			return cb[1][1];
		}
		return '-';
	}
	void play(int x, int y, char p) {
		cb[x][y] = p;
		this->x = x;
		this->y = y;
	}
	bool checkBoard(int x) {
		return (x >= 0 && x < SIZE);
	}
	bool isXNotFail() // true => 不败节点 false => 必败节点
	{
		return isPlayerNotFail('X');
	}
	bool isPlayerNotFail(char p) // true => 不败节点 false => 必败节点
	{
		char op = p == 'X' ? 'O' : 'X';
		if (isGameOver())
		{
			return !(whoWins() == op);
		}
		if (isCurPlayer(op))
		{
			int _x = x, _y = y;
			for (int i = 0; i < SIZE; ++i)
			{
				for (int j = 0; j < SIZE; ++j)
				{
					if (cb[i][j] == ' ')
					{
						play(i, j, p);
						if (isXNotFail()) {
							play(i, j, ' ');
							x = _x; y = _y;
							return true;
						}
						play(i, j, ' ');
					}
				}
			}
			x = _x; y = _y;
			return false;
		}
		if (isCurPlayer(p))
		{
			int _x = x, _y = y;
			for (int i = 0; i < SIZE; ++i)
			{
				for (int j = 0; j < SIZE; ++j)
				{
					if (cb[i][j] == ' ')
					{
						play(i, j, op);
						if (!isXNotFail()) {
							play(i, j, ' ');
							x = _x; y = _y;
							return false;
						}
						play(i, j, ' ');
					}
				}
			}
			x = _x; y = _y;
			return true;
		}
	}
	bool isCurPlayer(char p)
	{
		if (x == -1 && y == -1) {
			return p == 'O';
		}
		return (cb[x][y] == p);
	}
};
