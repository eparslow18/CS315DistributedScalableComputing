#include <iostream>
#include <vector>
#include <numeric>
#include <future>
using namespace std;


int main()
{
	vector<int> data(int(640000000), 1);

	vector<future<double>> ftr;
	int step = data.size() / 64;
	for (auto it = data.begin(); it != data.end(); it += step) {
		auto func = [=]() -> double {
			return accumulate(it, it + step, 0);
		};
		ftr.push_back(async(launch::async, func));
	}

	double sum = 0;
	for (int i = 0; i < ftr.size(); ++i) {
		sum += ftr[i].get();
	}

	cout << "Sum is "  << sum << endl;
}