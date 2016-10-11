#include <iostream>
#include <vector>
#include <thread>
using namespace std;


//using lambda functions with Threads

template <typename T>
void caller(T func) {
	vector<thread> pool;
	for (int i = 0; i < 10; i++)
		pool.push_back(thread(func, i));
	for (int i = 0; i < 10; i++)
		pool[i].join();
}

//	func(1966);

int main()
{
	int X = 0, Y = 0;
	vector<int> problem(10, 0);  // allocate 10 elements, initialized with 0

	auto func = [&X, &Y, &problem](int tid) { //& is required to modify the value
		cout << "Hello from lambda: " << tid << endl;
		cout << "Lambda: X is " << X << endl;
		Y = tid;
		X = tid;
		problem[tid] = 100 * tid;
	};

	caller(func);

	cout << "X is " << X << " Y is " << Y << endl;
	for (int i = 0; i < 10; i++)
		cout << "problem[" << i << "] = " << problem[i] << endl;
}