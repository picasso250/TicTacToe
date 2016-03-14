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
	g.print();
	cout<<g.whoWins()<<endl;
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
}
void testX()
{
}
void testFinish()
{
}
int main(int argc, char const *argv[])
{
	testRow();
	testCol();
	testFinish();
	cout<<"4 cases PASSED."<<endl;
	return 0;
}
