#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include "ppl.h" //parallel invoke 
using namespace std;
using namespace concurrency; //for parallel invoke
#define DATA_SIZE	int(1e3)

random_device rd;
default_random_engine engine;
uniform_int_distribution<> distribution(0, DATA_SIZE); // Generate a uniform real distribution between 0, 1e8

/**
* Thread-safe C++11 pseudo-random number generator
* @return		returns a random value between 0 and 1e8
*/
int cs273_rand() {
	return distribution(engine);
}

/**
*	Find the target value within the vector range described by the start and end iterators
*
*	@param start iterator pointing to the start of the vector
*	@param end iterator pointing to the end of the vector
*	@parame target target value to find in the vector
*	@return the index position if the target is found, -1 otherwise
*/
//template <typename T>
//int find(T start, T end, int target) {
//	for (T it = start; it != end; ++it)
//		if (*it == target)
//			return (it - start); // return the index
//	return -1;
//}


//EX03_01 pfind 
template<typename T>
int pfind(T start, T end, int target) {

	int total = end - start; //so end is correctly assigned 

	if (end - start <= 3) //base case to make process go into blocks of three
	{
		for (T it = start; it != end; ++it)
			if (*it == target)
				return (it - start); // return the index
		return -1;//else return -1
	}
	else//splitting 
	{
		auto middle = start + total / 2; //middle index using total instead of end
		auto r1 =-1;
		auto r2 =-1;

		auto func = [&r1, &start, &middle, &target]() {
			r1 = pfind(start, middle, target);
			//if (r1 != -1) {
			//	r1 = r1 + start; //captured in the func
				return;
		};

	
		auto func2 = [&r2, &start, &middle, &end, &target]() {//return r2+middle 
			r2 = pfind(middle, end, target);
			if (r2 != -1) {
				r2 = (middle - start) +r2; //captured in func2
				return;

			}
		};

		parallel_invoke(func, func2);

		if (r1 != -1) {
			return r1;
		}
		if (r2 != -1) {
			return r2;
		}
		return -1;
	}
}



int main()
{
	cout << "Initializing haystack ... please wait ...\n";
	vector<int> haystack(DATA_SIZE);
	for (int i = 0; i < DATA_SIZE; i++)
		haystack[i] = cs273_rand();

	int needle;
	do {
		cout << "What number do you want to search for ?[0," << DATA_SIZE << "] ";
		if (cin >> needle && needle >= 0 && needle <= DATA_SIZE)
			break;
	} while (true); // repeat until a valid number is found

	cout << "Searching!\n";
	auto start_time = chrono::steady_clock::now();

	int index = pfind(haystack.begin(), haystack.end(), needle);

	auto end_time = chrono::steady_clock::now();
	auto sec = chrono::duration_cast<chrono::seconds>(end_time - start_time);
	cout << "Time taken: " << sec.count() << " seconds\n";

	if (index == -1)
		cout << "Did not find " << needle << endl;
	else
	{
		cout << "Found " << needle << " in index " << index << endl;
		// verify that the found index location is correct!
		if (needle == haystack[index])
			cout << "Index is correct!\n";
		else
			cout << "Sorry the indx is incorrect!\n";
	}
}