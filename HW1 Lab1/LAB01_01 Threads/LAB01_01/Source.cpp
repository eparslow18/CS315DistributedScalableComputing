#include <iostream>
#include <random>
#include <vector> 
#include <thread>
#include <ppl.h>
using namespace std;
using namespace concurrency;

const int DIM_SIZE = 1000000;

/**
	Vector addition
	@param a	vector a
	@param b	vector b
	@param result	vector (a+b)
*/
void vector_add(const vector<int> &a, const vector<int> &b, vector<int> &result) { //create a lambda function 
	result.resize(a.size());  // ensure that result has sufficient elements allocated
	//for (int i = 0; i < a.size(); i++) {
	//	result[i] = a[i] + b[i];
	

	///////////////////////////////////////////////EX01_01 addition 
	auto funcAdd = [&a, &b, &result](int tid) {


		//creating 10 threads of the vector 
		int start = a.size() / 10 * tid;
		int end;
		if (tid == 9) // last thread
			end = a.size();
		else
			end = a.size() / 10 * (tid + 1);

		for (int i = 0; i < end; i++) { //adding the vectors together 
			result[i] = a[i] + b[i];
		}

	};

		vector<thread> threadPool; //creeating the pool of 10 threads 
		for (int i = 0; i < 10; i++)
			threadPool.push_back(thread(funcAdd, i));

		for (int i = 0; i < 10; i++)
			threadPool[i].join();


	/////////////////////////////////////////////////////////////
}

/**
	Vector subtraction
	@param a	vector a
	@param b	vector b
	@param result	vector (a-b)
*/
void vector_subtract(const vector<int> &a, const vector<int> &b, vector<int> &result) {
	result.resize(a.size());  // ensure that result has sufficient elements allocated
	/*for (int i = 0; i < a.size(); i++) {
		result[i] = a[i] - b[i];
	}*/

		///////////////////////////////////////////////EX01_01 subtraction 
		auto funcSubtract = [&a, &b, &result](int tid) {


			//creating 10 threads of the vector 
			int start = a.size() / 10 * tid;
			int end;
			if (tid == 9) // last thread
				end = a.size();
			else
				end = a.size() / 10 * (tid + 1);

			for (int i = 0; i < end; i++) { //subtracting the vectors together 
				result[i] = a[i] - b[i];
			}

		};

		vector<thread> threadPool; //creeating the pool of 10 threads 
		for (int i = 0; i < 10; i++)
			threadPool.push_back(thread(funcSubtract, i));

		for (int i = 0; i < 10; i++) //joins the threads together
			threadPool[i].join();


		/////////////////////////////////////////////////////////////
}

int main()
{
	vector<int> A, B, C1, C2;

	for (int i = 0; i < DIM_SIZE; i++) // Initialize vectors A and B
	{
		A.push_back(i + 1);
		B.push_back(i);
	}

	vector_add(A, B, C1); // C1 = A + B

	bool wrong = false;
	for (int i = 0; i < DIM_SIZE; i++) { // verify C1
		if (C1[i] != 2 * i + 1) {
			wrong = true;
		}
	}
	if (wrong)
		cout << "Sorry your vector_add() is incorrect\n";
	else
		cout << "vector_add() appears to be okay\n";

	vector_subtract(A, B, C2); // C2 = A - B

	wrong = false;
	for (int i = 0; i < DIM_SIZE; i++) { // verify C2
		if (C2[i] != 1)
			wrong = true;
	}
	if (wrong)
		cout << "Sorry your vector_subtract() is incorrect\n";
	else
		cout << "vector_subtract() appears to be okay\n";
}