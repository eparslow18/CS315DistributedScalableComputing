#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include "ppl.h"

using namespace std;
using namespace concurrency;

#define DATA_SIZE	int(1e4)
#define MAX_ELEMENT_VALUE	int(1e3)

// Counter to record the majority counts in range [0,MAX_ELEMENT_VALUE]
// Remember to protect this with a vector of mutexes when you are accessing this with threads!
// Each mutex element will be responsible for protecting it's companion element in the counter vector
vector<int> counter(MAX_ELEMENT_VALUE+1, 0); 

random_device rd;
default_random_engine engine;
uniform_int_distribution<> distribution(0, MAX_ELEMENT_VALUE); // Generate a uniform real distribution between 0, 1e8

/**
* Thread-safe C++11 pseudo-random number generator
* @return		returns a random value between 0 and 1e8
*/
int cs273_rand() {
	return distribution(engine);
}


/**
* Counts the number of time a value occurs in the vector defined by the start and end iterator
* 
* @param start Iterator pointing to the start of the vector
* @param end Iterator pointing to the end of the vector
*/
template <typename T>
void majority(T start, T end) {
	for (T it = start; it != end; ++it) {
		counter[*it]++; // update counter for value (i.e. *it) encountered 
	}
}

//////////////////////////////////////////////////////////////////////EX03_02
template <typename T> 
void pmajority(T start, T end) {
	
	int total = end - start; //so end is correctly assigned 

	if (end - start <= 3) {
		for (T it = start; it != end; ++it) {
			counter[*it]++; // update counter for value (i.e. *it) encountered 
		}
	}

	else {
		auto middle = start + total / 2;

		auto func = [&start, &middle]() { //no need to return 
		pmajority(start, middle);
		};

		auto func2 = [&start, &middle, &end]() { //no need to return 
			pmajority(middle, end);
			};

		parallel_invoke(func, func2); 

		}
}
///////////////////////////////////////////////////////////////////////////////





int main()
{
	cout << "Initializing ... please wait ...\n";
	vector<int> population(DATA_SIZE);
	for (int i = 0; i < DATA_SIZE; i++)
		population[i] = cs273_rand();

	
	cout << "Counting the majority!\n";
	auto start_time = chrono::steady_clock::now();

	pmajority(population.begin(), population.end());

	auto end_time = chrono::steady_clock::now();
	auto sec = chrono::duration_cast<chrono::seconds>(end_time - start_time);
	cout << "Time taken: " << sec.count() << " seconds\n";

	cout << "The winner is:\n";
	int max_value = -1;
	int i_index = -1;
	// Look for the highest count in the counter vector
	for (int i = 0; i < counter.size(); ++i) {
		if (max_value < counter[i]) {
			max_value = counter[i];
			i_index = i;
		}
	}
	cout << i_index << " with frequency " << max_value << endl;

}