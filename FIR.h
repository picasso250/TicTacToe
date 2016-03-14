#include <tuple>
#include <algorithm>
#include <functional>
#include <iostream>
#include <cstdio>
#include <cassert>

#include "TicTacToe.h"

using namespace std;

template <int SIZE = 13>
struct FIR : public TicTacToe<SIZE>
{
	char isRow() {
		for (int i = 0; i < SIZE; ++i) {
			int s[] = {0,0};
			for (int j = 0; j < SIZE; ++j)
			{
				int x = this->cb[i][j] == 'X' ? 1 : 0;
				if (this->cb[i][j] != ' ')
				{
					s[x]++;
					if (s[x] >= 5) return x ? 'X' : 'O';
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
				int x = this->cb[i][j] == 'X' ? 1 : 0;
				if (this->cb[i][j] != ' ')
				{
					s[x]++;
					if (s[x] >= 5) return x ? 'X' : 'O';
				} else {
					s[0] = s[1] = 0;
				}
			}
		}
		return '-';
	}
	char isX() {
		// is /, the left part
		for (int i = 5-1; i < SIZE; ++i)
		{
			int s[] = {0,0};
			for (int k = 0; k < SIZE && i+k < SIZE && i-k >= 0; ++k)
			{
				char stone = this->cb[i+k][i-k];
				if (stone != ' ')
				{
					int x = stone == 'X' ? 1 : 0;
					s[x]++;
					if (s[x] == 5)
					{
						return stone;
					}
				} else {
					s[0] = 0;
					s[1] = 0;
				}
			}
		}
		// is /, the right part
		for (int i = 0; i <= SIZE - 5; ++i)
		{
			int s[] = {0,0};
			for (int k = 0; k < SIZE; ++k)
			{
				char stone = this->cb[k][SIZE-k-1];
				if (stone != ' ')
				{
					s[x]++;
					if (s[x] == 5)
					{
						return stone;
					}
				}
			}
		}
		// is \, the right part
		for (int i = 0; i < SIZE; ++i)
		{
			int s[] = {0,0};
			for (int k = 0; k < SIZE; ++k)
			{
				for (int k = 0; k < SIZE && i+k < SIZE; ++k)
				{
					char stone = this->cb[k][i+k]
					if (stone != ' ')
					{
						int x = stone == 'X' ? 1 : 0;
						s[x]++;
						if (s[x] == 5)
						{
							return stone;
						}
					} else {
						s[0] = 0;
						s[1] = 0;
					}
				}
			}
		}
		return '-';
	}
	bool is_left_down_5(int i, int j)
	{
		char s = cb[i][j];
		for (int k = 1; k < 5 && 0 <= i-k && j+k < SIZE; ++k)
		{
			if (cb[i-k][j+k] != s) {
				return false;
			}
		}
		return true;
	}
	bool is_right_down_5(int i, int j)
	{
		char s = cb[i][j];
		for (int k = 1; k < 5 && i+k < SIZE && j+k < SIZE; ++k)
		{
			if (cb[i+k][j+k] != s) {
				return false;
			}
		}
		return true;
	}
};