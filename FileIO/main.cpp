#include "FileIO.h"

using namespace std;

int main()
{
	ifstream fin;
	fin.open("test.txt", ios_base::in);
	FileIO::PrintIntegers(fin, cout);
	fin.close();
	fin.open("test2.txt", ios_base::in);
	FileIO::PrintMaxFloat(fin, cout);
	fin.close();
	return 0;
}