#include <iostream>
#include <cstdio>

#include "TicTacToe.h"

using namespace std;

int main(int argc, char const *argv[])
{
	TicTacToe ttt;
	ttt.play(0,0, 'X');
	ttt.print();
	cout<<"========="<<endl;
	cout<<ttt.isXNotFail()<<endl;
	return 0;
}
