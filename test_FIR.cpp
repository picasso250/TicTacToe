#include <iostream>
#include <cassert>


using namespace std;

void testRow()
{
	FIR g;
	g.play(0,0, 'X');
	g.play(0,1, 'X');
	g.play(0,2, 'X');
	g.play(0,3, 'X');
	// cout<<g.whoWins()<<endl;
	assert(g.whoWins() == '-');
	g.play(0,4, 'X');
	g.play(1,1, 'O');
	assert(g.whoWins() == 'X');

	g.play(0,0,'O');
	g.play(1,0,'O');
	g.play(1,1,'O');
	g.play(1,2,'O');
	g.play(1,3,'O');
	g.play(1,4,'O');
	assert(g.whoWins() == 'O');
	// cout<<"========="<<endl;
}
void testCol()
{
	FIR g;
	g.play(1,3,'O');
	g.play(2,3,'O');
	g.play(3,3,'O');
	g.play(4,3,'O');
	g.play(5,3,'O');
	assert(g.whoWins() == 'O');
	// cout<<"========="<<endl;
}
void testX()
{
	FIR g;
	// \ mid
	g.play(1,1,'O');
	g.play(2,2,'O');
	g.play(3,3,'O');
	g.play(4,4,'O');
	g.play(5,5,'O');
	assert(g.whoWins() == 'O');

	// \ bottom
	g.play(3,3,'X');
	g.play(4,3,'X');
	g.play(5,4,'X');
	g.play(6,5,'X');
	g.play(7,6,'X');
	g.play(8,7,'X');
	assert(g.whoWins() == 'X');

	// \ top
	g.play(6,5,'O');
	g.play(5,6,'O');
	g.play(6,7,'O');
	g.play(7,8,'O');
	g.play(8,9,'O');
	g.play(9,10,'O');
	assert(g.whoWins() == 'O');

	// / top
	g.play(9,10,'X');
	g.play(2,4,'X');
	g.play(1,5,'X');
	g.play(4,2,'X');
	g.play(5,1,'X');
	assert(g.whoWins() == 'X');

	// / bottom
	g.play(3,3,'O');
	g.play(7,8,'X');
	g.play(6,9,'X');
	g.play(5,10,'X');
	g.play(4,11,'X');
	assert(g.whoWins() == 'X');
}
void testWhoWins()
{
	FIR g;
	g.play(0,2,'O');
	g.play(0,3,'X');
	g.play(0,4,'X');
	g.play(0,5,'O');
	g.play(2,4,'O');
	g.play(2,10,'O');
	g.play(4,5,'X');
	g.play(4,8,'X');
	g.play(6,6,'X');
	g.play(6,7,'O');
	g.play(0,12,'X');
	assert(g.whoWins() == '-');
}
void testFinish()
{
	// since we test it on TicTacToe
}
void test_in_board()
{
	FIR g;
	assert(g.in_board(1) == true);
	assert(g.in_board(0) == true);
	assert(g.in_board(12) == true);
	assert(g.in_board(-1) == false);
	assert(g.in_board(13) == false);
	assert(g.in_board(-333) == false);
	assert(g.in_board(133333) == false);

	assert(g.in_board(1) == true);
	assert(g.in_board(2) == true);
	assert(g.in_board(3) == true);

	assert(g.in_board(12, 1));
	assert(!g.in_board(-1, 13));
	assert(!g.in_board(1, 13));
}
void test_in_battle_field()
{
	FIR g;
	// \ mid
	g.play(1,1,'O');
	g.play(2,2,'O');
	g.play(3,3,'O');
	g.play(4,4,'O');
	g.play(5,5,'O');
	assert(g.in_battle_field(10,10) == false);
	assert(g.in_battle_field(1,2) == true);
	assert(g.in_battle_field(1,3) == true);
	assert(g.in_battle_field(1,4) == true);
	assert(g.in_battle_field(1,5) == true);
	assert(g.in_battle_field(1,6) == false);
	assert(g.in_battle_field(1,7) == false);
}
void test_winby()
{
	FIR g;
	// test row
	g.play(0,0, 'X');
	g.play(0,1, 'X');
	g.play(0,2, 'X');
	g.play(0,3, 'X');
	assert(g.win_by() == '-');
	g.play(0,4, 'X');
	assert(g.win_by() == 'X');

	// test col
	g.play(1,3,'O');
	g.play(2,3,'O');
	g.play(3,3,'O');
	g.play(4,3,'O');
	g.play(5,3,'O');
	assert(g.win_by() == 'O');

	// \ mid
	g.play(1,1,'O');
	g.play(2,2,'O');
	g.play(3,3,'O');
	g.play(4,4,'O');
	g.play(5,5,'O');
	assert(g.win_by() == 'O');

	// / top
	g.play(1,5,'X');
	g.play(2,4,'X');
	g.play(3,3,'X');
	g.play(4,2,'X');
	g.play(5,1,'X');
	g.print();
	assert(g.win_by() == 'X');
}
void test_line_value()
{
	FIR g;
	assert(g.line_value(0, 2, 5) == 1.0);
	assert(g.line_value(0, 2, 4) == 0.1);
	assert(g.line_value(1, 0, 3) == 0.9);
	assert(g.line_value(0, 1, 1) == 0.25);
}
void test_merge_env()
{
	FIR g;
	int rel[2][4] = {
		{1,1,0,1},
		{1,1,1,1}
	};
	int dead[2][4] = {
		{0,0,1,0},
		{0,0,0,0}
	};
	int sum[2][4] = {
		{1,1,1,1},
		{1,1,1,1}
	};
	g.merge_env(rel,dead,sum);
	assert(sum[0][0] == 1);
	assert(sum[1][0] == 0);

	assert(dead[0][2] == 1);
	assert(dead[1][2] == 1);
	assert(sum[0][2] == 1);
	assert(sum[1][2] == 1);
}
double sum_p(vector<double> v)
{
	double s = 1.0;
	for (auto i = v.begin(); i != v.end(); ++i)
	{
		s *= 1.0 - *i;
	}
	return 1.0 - s;
}
void test_get_point_value()
{
	FIR g;
	g.play(6,6, 'X');
	g.play(6,7, 'O');
	// printf("%f <=> %f\n", g.get_point_value(),1-0.7*0.6*0.8*0.6*0.6);
	// assert(g.get_point_value() == sum_p({0.3,0.25,0.2,0.25,0.25}));
	// g.play(7,7, 'X');
	// assert(g.get_point_value() == sum_p({0.3,0.2,0.8,0.25,0.25}));
	// g.play(5,5, 'O');
	// assert(g.get_point_value() == sum_p({0.25,0.2,0.75,0.25,0.25}));
}
bool vector_equal(vector<string> a, vector<string> b)
{
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	// for (auto i = a.begin(); i != a.end(); ++i)
	// {
	// 	cout<<*i<<" ";
	// }
	// cout<<endl;
	// for (auto i = b.begin(); i != b.end(); ++i)
	// {
	// 	cout<<*i<<" ";
	// }
	// cout<<endl;
	return (b == a);
}
void test_get_point_relation()
{
	FIR g;
	vector<string> vec;
	g.play(6,6, 'X');
	g.play(6,7, 'O');
	assert(vector_equal(g.get_point_relation(), {"#+1","1","+1","+1","+1"}));

	g.play(7,7, 'X');
	assert(vector_equal(g.get_point_relation(), {"#+1","1","+2","+1","+1"}));
	g.play(5,5, 'O');
	assert(vector_equal(g.get_point_relation(), {"+1","1","#+2","+1","+1"}));
	g.play(8,6, 'X');
	assert(vector_equal(g.get_point_relation(), {"+1","+2","+1","+1"}));
}
void testAI_MoveX() //
{
	FIR g;
	// \ mid
	g.AI_MoveX();
	assert(g.isCurPlayer('X') == true);
	g.play(6,7,'O');
	assert(g.isCurPlayer('O') == true);
	g.AI_MoveX();
	g.print();
	assert(g.isCurPlayer('X') == true);
}
