#include <iostream>
#include <string>
#include <stdexcept>
#include <future>
#include <thread>

using namespace std;

int sum(int N)
{
	if (N < 0) {
		throw invalid_argument("N cannot be negative");
	}
	int acc = 0;
	for (int i = 1; i <= N; ++i)
		acc += i;
	return acc;
}

int main()
{
	promise<int> arg_prms;
	promise<int> sum_prms;

	auto func = [&]() {
		auto arg_ftr = arg_prms.get_future();
		try {
			int s = sum(arg_ftr.get());
			sum_prms.set_value(s);
		}
		catch (...) {
			sum_prms.set_exception(current_exception());
		}
	};

	// Start the thread. Func will block at get_future()
	thread thr(func);

	cout << "Enter N: ";
	int N;
	cin >> N; 

	// After we set the value for the promise, func can continue
	arg_prms.set_value(N);

	try {
		// block till we get the answer
		auto sum_ftr = sum_prms.get_future();
		int ans = sum_ftr.get();
		cout << "Answer is " << ans << endl;
	}
	catch (exception &e) {
		cout << "Caught exception: " << e.what() << endl;
	}

	thr.join();
}