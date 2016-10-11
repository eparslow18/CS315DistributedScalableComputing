#include <iostream>
#include <vector>
#include <ppl.h>
using namespace std;
using namespace concurrency;


int main() {
	vector<int> problem(100, 0); // Allocate 100 elements, each initalized to 0
	// Problem: Initialize each element if vector problem to 100*i, where i is the index of the element
	
	for (int i = 0; i < 100; i++)
	problem[i] = i * 100;

	parallel_for(0, 100, [&](int tid) {
		problem[tid] = tid * 100;
	});


	for (int i = 0; i < 100; i++)
		cout << "problem[" << i << "] = " << problem[i] << endl;

}