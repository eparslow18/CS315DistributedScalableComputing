/**
LAB04_02
Description: Parallelize this using async to asynchronously start multiple functions concurrently.  
Store the future object returned from each async in a vector, i.e. vector<future<double>>.   
Iterate through this vector of futures to get the final sum, and display it.
*/
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main()
{
	int N;

	cout << "Sum of squares to? ";
	cin >> N;

	double sum = 0;
	for (int i = 1; i <= N; ++i) {
		sum += pow(i, 2); // i^2
		// Ed: for your solution, you may want to create a lambda function, with capture-by-copy specification
		// you do not want to capture-by-reference because "i" will change on every iteration
	}

	cout << "Sum of squares is " << sum << endl;
}