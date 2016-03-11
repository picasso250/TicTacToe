#include <iostream>
#include <cassert>

#include "TicTacToe.h"

using namespace std;

void testRow()
{
	TicTacToe ttt;
	ttt.play(0,0, 'X');
	ttt.play(0,1, 'X');
	// ttt.print();
	// cout<<ttt.whoWins()<<endl;
	assert(ttt.whoWins() == '-');
	// cout<<"========="<<endl;
	ttt.play(0,2, 'X');
	ttt.play(1,1, 'O');
	// ttt.print();
	assert(ttt.whoWins() == 'X');
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
void testX(TicTacToe &ttt)
{
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
int testXNotFail()
{
	TicTacToe ttt;
	ttt.play(0,0, 'X');
	ttt.play(0,1, 'X');
	ttt.play(0,2, 'X');
	// cout<<ttt.isXNotFail()<<endl;
	assert(ttt.getNodeValue('X') == 1);
	assert(ttt.getNodeValue('O') == -1);
	ttt.play(0,1, ' ');
	ttt.play(1,1, 'O');
	assert(ttt.getNodeValue('X') == 1);
	ttt.play(2,2, 'X'); // 构成绝杀
	assert(ttt.getNodeValue('X') == 1);
	ttt.play(1,2, 'X'); // 还差一步赢棋
	ttt.print();
	assert(ttt.getNodeValue('X') == 1);
	ttt.play(1,2, 'O');
	ttt.print();
	cout<<"========="<<endl;
	cout<<ttt.getNodeValue('X')<<endl;
	// assert(ttt.getNodeValue('X') == 0);
	ttt.play(1,0, 'X');
	ttt.print();
	cout<<ttt.getNodeValue('X')<<endl;
	// assert(ttt.getNodeValue('X') == 0);
	cout<<"========="<<endl;
	ttt.play(0,1, 'O');
	ttt.print();
	cout<<ttt.getNodeValue('X')<<endl;
	// assert(ttt.getNodeValue('X') == 0);
	cout<<"========="<<endl;
	ttt.play(2,1, 'X');
	ttt.print();
	cout<<ttt.getNodeValue('X')<<endl;
	assert(ttt.getNodeValue('X') == 0);
	cout<<"========="<<endl;

}
int main(int argc, char const *argv[])
{
	TicTacToe ttt;
	testRow();
	testCol();
	testX(ttt);
	testFinish();
	testXNotFail();
	cout<<"4 cases PASSED."<<endl;
	return 0;
}
