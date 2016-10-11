#include <iostream>
#include <future>
#include <vector>
#include <numeric>
using namespace std;

template <typename T>
int psum2(T begin, T end, int init_value) {
	int size = end - begin;
	if (size < int(1e3)) 
		return accumulate(begin, end, init_value);

	auto middle = begin + size / 2;

	auto ftr1 = async(launch::async, psum2<T>, middle, end, init_value);
	auto ftr2 = async(launch::async, psum2<T>, begin, middle, 0);

	int sum = ftr1.get() + ftr2.get();

	return sum;
}

int main()
{
	vector<int> data(int(64000), 1);

	cout << "Sum is " << psum2(data.begin(), data.end(), 0) << endl;
}