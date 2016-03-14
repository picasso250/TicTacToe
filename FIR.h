#include <tuple>
#include <algorithm>
#include <functional>
#include <iostream>
#include <cstdio>
#include <cassert>

#include "TicTacToe.h"

using namespace std;

template <int SIZE = 13>
struct FIR_T : TicTacToe_T<SIZE>
{
	const static int MAX_LEVEL = 12;

	char isRow() {
		for (int i = 0; i < SIZE; ++i) {
			int s[] = {0,0};
			for (int j = 0; j < SIZE; ++j)
			{
				char stone = this->cb[i][j];
				int x = stone == 'X' ? 1 : 0;
				if (stone != ' ') {
					s[x]++;
					if (s[x] >= 5) return stone;
				} else {
					s[0] = s[1] = 0;
				}
			}
		}
		return '-';
	}
	char isCol() {
		for (int j = 0; j < SIZE; ++j)
		{
			int s[] = {0,0};
			for (int i = 0; i < SIZE; ++i)
			{
				char stone = this->cb[i][j];
				int x = stone == 'X' ? 1 : 0;
				if (stone != ' ') {
					s[x]++;
					if (s[x] >= 5) return stone;
				} else {
					s[0] = s[1] = 0;
				}
			}
		}
		return '-';
	}
	char isX() {
		// is /, the left part
		for (int i = 0; i < SIZE; ++i)
		{
			int s[] = {0,0};
			for (int k = 0; k < SIZE && i-k >= 0; ++k)
			{
				char stone = this->cb[k][i-k];
				// printf("(%d,%d) ", k,i-k);
				if (stone != ' ')
				{
					int x = stone == 'X' ? 1 : 0;
					s[x]++;
					if (s[x] == 5)
					{
						return stone;
					}
				} else {
					s[0] = s[1] = 0;
				}
			}
			// cout<<endl;
		}
		// is /, the right part
		for (int i = 0; i <= SIZE - 5; ++i)
		{
			int s[] = {0,0};
			for (int k = 0; k < SIZE && i+k < SIZE; ++k)
			{
				char stone = this->cb[i+k][SIZE-k-1];
				// printf("(%d,%d) ", i+k,SIZE-k-1);
				if (stone != ' ')
				{
					int x = stone == 'X' ? 1 : 0;
					s[x]++;
					if (s[x] == 5)
					{
						return stone;
					}
				}
			}
			// cout<<endl;
		}
		// is \, the right part
		for (int i = 0; i < SIZE; ++i)
		{
			int s[] = {0,0};
			for (int k = 0; k < SIZE; ++k)
			{
				for (int k = 0; k < SIZE && i+k < SIZE; ++k)
				{
					char stone = this->cb[k][i+k];
					if (stone != ' ')
					{
						int x = stone == 'X' ? 1 : 0;
						s[x]++;
						if (s[x] == 5)
						{
							return stone;
						}
					} else {
						s[0] = s[1] = 0;
					}
				}
			}
		}
		// is \, the left part
		for (int i = 0; i < SIZE; ++i)
		{
			int s[] = {0,0};
			for (int k = 0; k < SIZE && i+k < SIZE; ++k)
			{
				char stone = this->cb[i+k][k];
				if (stone != ' ')
				{
					int x = stone == 'X' ? 1 : 0;
					s[x]++;
					if (s[x] == 5)
					{
						return stone;
					}
				} else {
					s[0] = s[1] = 0;
				}
			}
		}
		return '-';
	}
	// bool is_left_down_5(int i, int j)
	// {
	// 	char s = this->cb[i][j];
	// 	for (int k = 1; k < 5 && 0 <= i-k && j+k < SIZE; ++k)
	// 	{
	// 		if (this->cb[i-k][j+k] != s) {
	// 			return false;
	// 		}
	// 	}
	// 	return true;
	// }
	// bool is_right_down_5(int i, int j)
	// {
	// 	char s = this->cb[i][j];
	// 	for (int k = 1; k < 5 && i+k < SIZE && j+k < SIZE; ++k)
	// 	{
	// 		if (this->cb[i+k][j+k] != s) {
	// 			return false;
	// 		}
	// 	}
	// 	return true;
	// }
	// 返回胜利/失败的概率
	double getNodeValue(char p, int level = 0) // [-1,1]
	{
		char op = p == 'X' ? 'O' : 'X';
		if (this->isGameOver()) {
			char w = this->whoWins();
			if (w == '-') return 0;
			return (w == p) ? 1 : -1;
		}
		if (level >= MAX_LEVEL)
		{
			return 0.5;
		}
		int _x = this->x, _y = this->y;
		vector<double> v;
		char next_p = this->isCurPlayer(op)? p : op;
		walk_empty([&](int i, int j) {
			// 不会离已有的棋子太远 距离2
			if (too_far_from_all(i, j)) return;
			this->play(i, j, next_p);
			double val = getNodeValue(p, level+1);
			v.push_back(val);
			this->cb[i][j] = ' ';
		});
		this->x = _x; this->y = _y;
		assert(v.size() != 0);
		double sum_of_elems = 0.0;
		for (double val : v)
		    sum_of_elems += val;
		return sum_of_elems / v.size();
	}
	bool too_far_from_all(int i, int j) {
		for (int ii = -2; ii <= 2; ++ii)
		{
			if (!in_board(i+ii))
			{
				continue;
			}
			for (int jj = -2; jj < 2 && in_board(j+jj); ++jj)
			{
				if (!in_board(j+jj))
				{
					continue;
				}
				if (this->cb[i+ii][j+jj] != ' ')
				{
					return false;
				}
			}
		}
		return true;
	}
	bool in_board(int i)
	{
		return 0 <= i && i < SIZE;
	}
};
typedef FIR_T<13> FIR;
