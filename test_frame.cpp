#include <iostream>
#include <cassert>

#include ".test_tmp_dep.h"

using namespace std;

int main(int argc, char const *argv[])
{
#include ".test_tmp_testing.cpp"
return 0;
}
