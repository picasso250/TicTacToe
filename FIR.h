#include <tuple>
#include <map>
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
	// 4 = 3m29.908s => 0m49.850s
	const static int MAX_LEVEL = 4;
	const static int MAX_BATTLE_RANGE = 2;

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
					if (s[x] >= 5) {
						return stone;
					}
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
						// printf("/ left part\n");
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
						// printf("/ right part\n");
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
			for (int k = 0; k < SIZE && i+k < SIZE; ++k)
			{
				char stone = this->cb[k][i+k];
				if (stone != ' ')
				{
					int x = stone == 'X' ? 1 : 0;
					s[x]++;
					if (s[x] == 5)
					{
						// printf("\\ right\n");
						return stone;
					}
				} else {
					s[0] = s[1] = 0;
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
						// printf("\\ left \n");
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
		// if (this->isGameOver()) {
		// 	char w = this->whoWins();
		// 	this->print();
		// 	printf("%c wins\n", w);
		// 	if (w == '-') return 0;
		// 	return (w == p) ? 1 : -1;
		// }
		if (level >= MAX_LEVEL)
		{
			// printf("level reached\n");
			return 0.0;
		}
		int _x = this->x, _y = this->y;
		vector<double> v;
		char next_p = this->isCurPlayer(op)? p : op;
		int child_i = 0;
		this->walk_empty([&](int i, int j) {
			// 不会离已有的棋子太远 距离2
			if (!in_battle_field(i, j)) {
				return;
			}
			this->play(i, j, next_p);
			this->print();
			char winner = win_by();
			double val;
			if (winner == '-')
			{
				val = getNodeValue(p, level+1);
			} else {
				val = winner == p ? 1.0 : -1.0;
			}
			// printf("level=%d, (%d,%d), %f, child_i:%dth\n", level, i,j,val,child_i++);
			// if (val > 0.51 || val < -0.51)
			// {
			// 	this->print();
			// 	printf("not 0! %c wins\n", this->whoWins());
			// 	exit(0);
			// }
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
	char win_by()
	{
		int i = this->x, j = this->y;
		char stone = this->cb[i][j];
		int s = 0;
		// row
		for (int jj = max(0, j-5+1); jj < min(SIZE,j+5); ++jj)
		{
			if (stone == this->cb[i][jj])
			{
				s++;
				if (s == 5)
				{
					return stone;
				}
			} else {
				s = 0;
			}
		}
		// col
		for (int ii = max(0,i-5+1), s = 0; ii < min(SIZE,i+5); ++ii)
		{
			if (stone == this->cb[ii][j])
			{
				s++;
				if (s == 5)
				{
					return stone;
				}
			} else {
				s = 0;
			}
		}
		// /,
		for (int k = max(max(-5, i-SIZE),-j),s=0; k < 5 && k <= i && k < SIZE-j; ++k)
		{
			if (stone == this->cb[i-k][j+k])
			{
				s++;
				if (s == 5)
				{
					return stone;
				}
			} else {
				s = 0;
			}
		}
		// \,
		for (int k = max(max(-5, -i),-j),s=0; k < 5 && k < SIZE - i && k < SIZE-j; ++k)
		{
			if (stone == this->cb[i+k][j+k])
			{
				s++;
				if (s == 5)
				{
					return stone;
				}
			} else {
				s = 0;
			}
		}
		return '-';
	}
	bool in_battle_field(int i, int j) {
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
					return true;
				}
			}
		}
		return false;
	}
	bool in_board(int i)
	{
		return 0 <= i && i < SIZE;
	}
	bool in_board(int x, int y)
	{
		return in_board(x) && in_board(y);
	}
	bool AI_MoveX()
	{
		if (this->x == -1)
		{
			this->play(6,6,'X');
			return true;
		}
		int _x = this->x, _y = this->y;
		map<double,tuple<int,int>> m;
		this->walk_empty([&](int i, int j) {
			// 不会离已有的棋子太远 距离2
			// printf("(%d,%d) in_battle_field=%d\n", i,j,in_battle_field);
			if (!in_battle_field(i, j)) {
				return;
			}
			this->play(i, j, 'X');
			m[getNodeValue('X')] = make_tuple(i, j);
			this->cb[i][j] = ' ';
		});
		this->x = _x; this->y = _y;
		auto maxp = m.rbegin();
		if (maxp->first < 0)
		{
			return false;
		}
		int i, j, v;
		tie(i,j) = maxp->second;
		this->play(i,j,'X');
		return true;
	}
	// 当前棋子落点的价值（棋子已经落在这个点上）
	// 对当前的颜色的棋子的价值
	double get_point_value()
	{
		vector<double> vec;
		// 八个方向的其中四个，另外四个可以取相反数获得
		int dirs[4][2] = {
			{1,0},
			{1,1},
			{0,1},
			{-1,1}
		};
		// 活 0 | 半活 1 | 死 2 |
		int dead[2][4];
		int sum[2][4]; // 棋子数量
		int rel[2][4]; // 关系：1增加己方的，0挡住对方的
		char stone;
		int dir_map[2] = {-1, 1};
		for (int di = 0; di < 2; ++di)
		{
			int ds = di? 1 : -1;
			// printf("ds = %d\n", ds);
			for (int i = 0, stone = this->cb[this->x][this->y]; i < 4; ++i)
			{
				dead[di][i] = 0;
				sum[di][i] = 1;
				rel[di][i] = 1;
				int sx = ds * dirs[i][0];
				int sy = ds * dirs[i][1];
				// printf("add (%d,%d)\n", sx,sy);
				for (int k = 1; k < SIZE; ++k)
				{
					int x = this->x + k*sx;
					int y = this->y + k*sy;
					if (in_board(x, y))
					{
						// printf("check %d,%d\n", x,y);
						if (this->cb[x][y] == stone) {
							sum[di][i]++;
						} else if (this->cb[x][y] == ' ') {
							break;
						} else {
							if (k == 1) {
								stone = this->cb[x][y];
								// printf("stone chane to %c\n", stone);
								rel[di][i] = 0;
								sum[di][i] = 1;
							} else {
								dead[di][i]++;
								break;
							}
						}
					} else {
						dead[di][i]++;
						break;
					}
				}
				// printf("sum=%d\n", sum[di][i]);
			}
		}
		merge(rel,dead,sum);

		double s = 1;
		for (int i = 0; i < 2; ++i)
		{
			for (int k = 0; k < 4; ++k)
			{
				// printf("add %f\n", line_value(rel[i][k], dead[i][k], sum[i][k]));
				s *= 1 - line_value(rel[i][k], dead[i][k], sum[i][k]);
			}
		}
		return 1.0 - s;
	}
	void merge(int rel[][4], int dead[][4],int sum[][4])
	{
		// merge, OOO | OX
		for (int i = 0; i < 4; ++i)
		{
			for (int k = 0; k < 2; ++k)
			{
				// printf("%d,%d,%d\n", rel[k][i], dead[k][i], sum[k][i]);
			}
			if (rel[0][i] == 1 && rel[0][i] == 1
				&& dead[0][i] == 0 && dead[1][i] == 0)
			{
				// printf("merge %d\n", i);
				sum[0][i] += sum[1][i] - 1;
				sum[1][i] = 0;
				dead[0][i] += dead[1][i];
			} else if (rel[0][i] ^ rel[1][i]) {
				int kk = rel[0][i] == 1 ? 0 : 1;
				dead[kk][i]++;
			}
			for (int k = 0; k < 2; ++k)
			{
				// printf("after merge %d,%d,%d\n", rel[k][i], dead[k][i], sum[k][i]);
			}
		}
	}
	double line_value(int rel, int dead, int sum)
	{
		// printf("rel=%d, dead=%d, sum=%d\n", rel, dead, sum);
		double vm[2][2][5+1] = {
			{ // 挡
				{0.0, 0.3,  0.75, 0.85, 1.0, 1.0}, // 活
				{0.0, 0.25, 0.55, 0.75, 1.0, 1.0}  // 半活
			},
			{ // 延展自己的棋子
				{0.0, 0.4, 0.8,  0.9, 1.0,  1.0}, // 活
				{0.0, 0.2, 0.55, 0.7, 0.75, 1.0}  // 半活
			}
		};
		if (sum == 0)
		{
			return 0.0;
		}
		if (sum >= 5)
		{
			return 1.0;
		}
		if (dead == 2)
		{
			return 0.1;
		}
		return vm[rel][dead][sum];
	}
};

typedef FIR_T<13> FIR;
