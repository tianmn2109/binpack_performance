#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;
struct T {
	int num;
	int c;
	vector<vector<int> > v;
	vector<int> left;
	double f;
	T(int cap) {
		c = cap;
	}
	T(const T &t) {
		num = t.num;
		c = t.c;
		v.resize(num);
		left.resize(num);
		for (int i = 0; i < num; i ++)
			left[i] = t.left[i];
		for (int i = 0; i < num; i ++) {
			for (int j = 0; j < t.v[i].size(); j ++)
				v[i].push_back(t.v[i][j]);
		}
/*		cout << "cpoy size = " << num << endl;
		for (int i = 0; i < v.size(); i ++) {
			for (int j = 0; j < v[i].size(); j ++)
				cout << v[i][j] << " ";
			cout << endl;
		}
*/	}
	double fitness() {
		double fit = 0.0;
		for (int i = 0; i < left.size(); i ++) {
			fit += (double)(c - left[i]) * (double)(c - left[i]) / (double)c / (double)c;
		}
		f = fit / left.size();
		return fit / left.size();
	}
	void add(int w) {
		int i = 0;
		for (i = 0; i < v.size(); i ++)
			if (left[i] >= w) {
				v[i].push_back(w);
				left[i] -= w;
				break;
			}
		if (i == v.size()) {
			v.push_back(vector<int>(1));
			v[v.size() - 1][0] = w;
			left.push_back(c);
			left[left.size() - 1]  -= w;
		}
		num = left.size();

	}
};

void firstFit(vector<int> input, T &t) {
	for (int i = 0; i < input.size(); i ++)
		t.add(input[i]);
/*	cout << "bin size = " << t.num << endl;
	for (int i = 0; i < t.v.size(); i ++) {
		for (int j = 0; j < t.v[i].size(); j ++)
			cout << t.v[i][j] << " ";
		cout << endl;
	}
*/}

T  produceNew(T &t) {
	T newT = t;
	vector<int> res;
	int i = rand() % newT.num;
//	cout << "random i = " << i << endl;
	i ++;
	int k = i;
	for (int j = 0; j < newT.v[i - 1].size(); j ++)
		res.push_back(newT.v[i - 1][j]);
//	cout << "left" << endl;
//	for (int j = 0; j < newT.left.size(); j ++)
//		cout << newT.left[j] << endl;
	for (; i < newT.num; i ++) {
		newT.v[i - 1].clear();
		newT.left[i - 1] = newT.left[i];
		for (int j = 0; j < newT.v[i].size(); j ++)
			newT.v[i - 1].push_back(newT.v[i][j]);
	}
	newT.v.pop_back();
	newT.left.pop_back();
	newT.num --;
/*	for (int i = 0; i < newT.v.size(); i ++) {
		for (int j = 0; j < newT.v[i].size(); j ++)
			cout << newT.v[i][j] << " ";
		cout << endl;
	}
	cout << "res" << endl;
	for (int i = 0; i < res.size(); i++)
		cout << res[i] << " ";
	cout << endl;
	sort(res.begin(), res.end());
*/	firstFit(res, newT);
	return newT;
	
}

double accept(double num, double newNum, double t) {
	if (newNum > num)
		return 1.0;
	return exp((num - newNum) / t);
}

int main(int argc, char **argv)
{
	srand((unsigned)time(NULL));
//	int a[] = {2, 3, 4, 5, 6 ,7 ,3 ,4 ,1 ,3};
	ifstream ifs(argv[1]);
	int num = 0;
	int c = 0;
	ifs >> num;
	ifs >> c;
	vector<int> aa(num, 0);
	if (num == 0)
		return 0;
	for(int i = 0; i < num; i ++)
		ifs >> aa[i];
	ifs.close();
	T t(c);
	clock_t start, finish;
	start = clock();
	firstFit(aa, t);
	double temp = 1000;
	T best = t;
	double cool = 0.003;
	int minNum = 6553666;
	
	while (temp > 1) {
		T newT = produceNew(best);
/*		if (accept(best.num, newT.num, temp) > (((double)(rand() % 1000)) / 1000)) {
			best = newT;
		}	
*/
		if (accept(best.fitness(), newT.fitness(), temp) > (((double)(rand() % 1000)) / 1000)) {
			best = newT;
		}	
//		cout << "fitness = " << best.fitness() << endl;
		if (best.num < minNum)
			minNum = best.num;
		temp *= 1- cool;
	}
	finish = clock();
	cout << "bins number = " << minNum << " fitness = " << best.fitness();
	cout << " time = " << (double)(finish - start) / CLOCKS_PER_SEC << endl;
//	produceNew(t);
//	cout << "min bin = " << minNum << " time = " << (double)(finish - start) / CLOCKS_PER_SEC << endl;
/*	for (int i = 0; i < best.v.size(); i ++) {
		cout << "bin num " ;
		for (int j = 0; j < best.v[i].size(); j ++)
			cout << best.v[i][j] << " ";
			cout << endl;
	}
*/	return 0;
}
