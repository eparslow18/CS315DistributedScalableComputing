#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <ppl.h>
#include <mutex> //for making a guard
using namespace std;
using namespace concurrency;

/**
	Sleep for some number of milliseconds
	@param time	number of milliseconds to sleep
*/
void millisecond_sleep(int time) {
	this_thread::sleep_for(chrono::milliseconds(time));
}

#define NUM_THREADS	10

mutex m; //name the guard

int main()
{
	int count = 0; 

	auto func = [&count](int tid) { // lambda function, auto is a function pointer
		millisecond_sleep(20);  // sleep for 20 milliseconds
		for (int i = 0; i < 10; i++) {
			//to protect count
			unique_lock<mutex> lk(m); //protects count as a critical section
			++count;
		}
	};

	int error = 0; // number of times our count is incorrect

	for (int test = 0; test < 100; test++) {

		count = 0; // initialize count to 0

		parallel_for(0, NUM_THREADS, func); // spawn NUM_THREADS threads executing func(int tid)
		
		cout << "count " << count << endl; // print count		
		
		if (count != 10 * NUM_THREADS)					// increment error if count is incorrect
			error++;
	}

	cout << "errors " << error << endl;
}