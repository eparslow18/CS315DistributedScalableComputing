#include <iostream>
#include <chrono>
#include <thread>
#include <condition_variable> //to use condition variable below
#include <mutex>

using namespace std;

int main()
{
	condition_variable cv; // 
	mutex m; //

	bool goodbye = false;

	auto func = [&]() {
		unique_lock<mutex> lk(m); //mutual exlusion varialbe will lock the critical section of code 
		while (!goodbye) {
			cv.wait(lk); //wait for continue from loop below
			cout << "Why ... Hello there handsome!\n";
		}

		cout << "So sad to see you go ...\n";
	};

	thread worker(func);

	while (!goodbye) {
		char ch;
		if (cin >> ch)
		{
			if (ch == 'q') {
				goodbye = true;
			}
			cv.notify_all(); //allows program to continue
		}
	}


	worker.join();
}
