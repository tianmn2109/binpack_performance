#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cstdio>
using namespace std;

int main(int argc, char **argv)
{
	if (argc < 6) {
		cerr << "Usage: [proName] [outfilename] [maxBinNum] [capacity] [minRange] [maxRange]" << endl;
	}
	int maxBinNum;
	int capacity;
	int minRange;
	int maxRange;
	
	maxBinNum = atoi(argv[2]);
	capacity = atoi(argv[3]);
	minRange = atoi(argv[4]);
	maxRange = atoi(argv[5]);
	int range = maxRange - minRange + 1;

	ofstream outfile(argv[1]);
	srand((int)time(NULL));
	int num = rand() % maxBinNum + 1;
	outfile << num << " " << capacity << " ";
	for (int i = 0; i < num; i ++)
		outfile << rand() % range + minRange << " ";
	outfile.close();
	

	return 0;
	
	
}
