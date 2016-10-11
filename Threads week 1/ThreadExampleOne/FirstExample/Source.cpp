#include <iostream>'
#include <thread>
#include <vector>
using namespace std;

void func(int tid) {
	cout << "Hello world! " << tid << "\n";
}

int main() {
	//thread thr(func, 0); //runs a single thread
	//thr.join();

	vector<thread> thr_pool;

	for (int i = 0; i < 10; i++)
		thr_pool.push_back(thread(func, i));

	for (int i = 0; i < 10; i++)
		thr_pool[i].join();

}