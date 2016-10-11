#include <iostream>
#include <string>
#include <future>
#include <chrono>
#include <thread>

using namespace std;

int main()
{
	promise<string> prms;

	auto ftr = prms.get_future();

	auto func = [&]() {
		cout << "Start chopping wood...\n";
		this_thread::sleep_for(chrono::seconds(5));
		prms.set_value("Wood chopping finished");
		cout << "Start building home\n";
		//this_thread::sleep_for(chrono::seconds(5));
		cout << "Finished building home\n";
	};

	thread thr(func);

	cout << ftr.get() << endl;//comes out third when line 20 is uncmonnented because the thread goes to sleep and main is still awake and thus runs this line 

	thr.join();
}