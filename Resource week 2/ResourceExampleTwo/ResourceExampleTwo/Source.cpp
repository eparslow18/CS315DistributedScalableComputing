#include <iostream>
#include <ppl.h>//library holds mutex 

using namespace std;
using namespace concurrency;
mutex m; 

int main()
{
	parallel_for(0, 100, [](int tid) {
		lock_guard<mutex> lk(m); //unqiue lock handles errors better than a lock guard with exception handling if one thread fails 
		cout << "Hello from " << tid << endl;
	});
}