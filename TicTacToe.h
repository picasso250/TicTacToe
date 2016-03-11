#include <tuple>
#include <algorithm>
#include <functional>
#include <iostream>
#include <cstdio>
#include <cassert>

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
	int getNodeValue(char p) // true => 不败节点 false => 必败节点
	{
		char op = p == 'X' ? 'O' : 'X';
		if (isGameOver()) {
			char w = whoWins();
			if (w == '-') return 0;
			return (w == p) ? 1 : -1;
		}
		int _x = x, _y = y;
		vector<int> v;
		if (isCurPlayer(op))
		{
			walk_empty([&](int i, int j) {
				play(i, j, p);
				int val = getNodeValue(p);
				v.push_back(val);
				play(i, j, ' ');
			});
			x = _x; y = _y;
			if (any_of(v.begin(), v.end(), [](int i) {return i==1;})) {
				return 1;
			}
			return (any_of(v.begin(), v.end(), [](int i) {return i==0;})) ?
				0 : -1;
		}
		assert(isCurPlayer(p));
		walk_empty([&](int i, int j){
			play(i, j, op);
			int val = getNodeValue(p);
			v.push_back(val);
			play(i, j, ' ');
		});
		x = _x; y = _y;
		if (any_of(v.begin(), v.end(), [](int i) {return i==-1;})) {
			return -1;
		}
		return (any_of(v.begin(), v.end(), [](int i) {return i==1;})) ?
			1 : 0;
	}
	void walk_empty(function<void(int,int)> callback)
	{
		for (int i = 0; i < SIZE; ++i)
			for (int j = 0; j < SIZE; ++j)
				if (cb[i][j] == ' ')
					callback(i,j);
	}
	bool isCurPlayer(char p)
	{
		if (x == -1 && y == -1) {
			return p == 'O';
		}
		return (cb[x][y] == p);
	}
	tuple<int,int> getAI_MoveO()
	{
		int _x = x, _y = y;
		vector<tuple<int,int,int>> vec;
		walk_empty([&](int i, int j){
			play(i, j, 'O');
			vec.push_back(make_tuple(i, j, getNodeValue('O')));
			play(i, j, ' ');
		});
		x = _x; y = _y;

		int i, j, v;
		for (auto e : vec) {
			tie(i, j, v) = e;
			if (v == 1)
			{
				return make_tuple(i,j);
			}
		}
		for (auto e : vec) {
			tie(i, j, v) = e;
			if (v == 0)
			{
				return make_tuple(i,j);
			}
		}
		return make_tuple (-1, -1);
	}
};
