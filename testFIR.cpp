#include <iostream>
#include <cassert>

#include "FIR.h"

using namespace std;

void testRow()
{
	FIR g;
	g.play(0,0, 'X');
	g.play(0,1, 'X');
	g.play(0,2, 'X');
	g.play(0,3, 'X');
	// g.print();
	// cout<<g.whoWins()<<endl;
	assert(g.whoWins() == '-');
	// cout<<"========="<<endl;
	g.play(0,4, 'X');
	g.play(1,1, 'O');
	// g.print();
	assert(g.whoWins() == 'X');
	// cout<<"========="<<endl;
}
void testCol()
{
	TicTacToe ttt;
	ttt.play(0,1, 'O');
	ttt.play(1,1, 'O');
	ttt.print();
	// cout<<ttt.whoWins()<<endl;
	assert(ttt.whoWins() == '-');
	cout<<"========="<<endl;
	ttt.play(2,1, 'O');
	ttt.play(1,0, 'O');
	ttt.print();
	assert(ttt.whoWins() == 'O');
	cout<<"========="<<endl;
}
void testX()
{
	TicTacToe ttt;
	ttt.play(0,0, 'O');
	ttt.play(1,1, 'O');
	ttt.print();
	// cout<<ttt.whoWins()<<endl;
	assert(ttt.whoWins() == '-');
	cout<<"========="<<endl;
	ttt.play(2,2, 'O');
	ttt.play(1,0, 'X');
	ttt.print();
	assert(ttt.whoWins() == 'O');
	cout<<"========="<<endl;
	ttt.play(0,2, 'X');
	ttt.play(1,1, 'X');
	ttt.play(2,0, 'X');
	ttt.print();
	assert(ttt.whoWins() == 'X');
	cout<<"========="<<endl;
}
void testFinish()
{
	TicTacToe ttt;
	assert(ttt.isGameOver() == false);
	testX(ttt);
	assert(ttt.isGameOver() == true);
	ttt.play(0,1, 'O');
	ttt.play(1,1, 'X');
	ttt.play(2,1, 'X');
	ttt.play(1,2, 'O');
	ttt.print();
	cout<<"========="<<endl;
	assert(ttt.isGameOver() == true);
}
int main(int argc, char const *argv[])
{
	testRow();
	testCol();
	testFinish();
	cout<<"4 cases PASSED."<<endl;
	return 0;
}
