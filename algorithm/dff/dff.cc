#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int dff(vector<int> v, int capacity, vector<vector<int> > &bins) {
	int num = 0;
	vector<int> c;
	sort(v.begin(), v.end(), greater<int>());
	for (int i = 0; i < v.size(); i ++) {
		int j = 0;
		for (j = 0; j < bins.size(); j ++) {
			if (c[j] >= v[i]) {
				c[j] -= v[i];
				bins[j].push_back(v[i]);
				break;
			}
		}
		if (j == bins.size()) {
			c.push_back(capacity - v[i]);
			bins.push_back(vector<int>());
			bins[j].push_back(v[i]);
			num ++;
		}
	}
	return num;
}
double fitness(vector<vector<int> > &bins, int capacity) {
	double fit = 0.0;
	for (int i = 0; i < bins.size(); i ++) {
		double tempCap = 0;
		for (int j = 0; j < bins[i].size(); j ++)
			tempCap += bins[i][j];
		fit += tempCap / capacity * tempCap / capacity;
	}
	return fit / bins.size();
}

int main(int argc, char **argv)
{
	int num;
	int capacity;
	ifstream f(argv[1]);	
	f >> num;
	f >> capacity;
	vector<int> v(num);
	for (int i = 0; i < v.size(); i ++)
		f >> v[i];
	f.close();
	vector<vector<int> > bins;
	clock_t start = clock();
	cout << "bins num = " << dff(v, capacity, bins);
	cout << " fitness = " << fitness(bins, capacity);
/*	for (int i = 0 ; i < bins.size(); i ++) {
		cout << "bin number: " << i + 1 << ": ";
		for (int j = 0; j < bins[i].size(); j ++)
			cout << bins[i][j] << " ";
		cout << endl;
	}
*/	clock_t finish = clock();
	cout << " time = " << (double)(finish - start) / CLOCKS_PER_SEC << endl;
	return 0;

}
