#include <iostream>
#include <thread>

int main() {
	unsigned int n = std::thread::hardware_concurrency(); //use unsigned so there will never be a negative int 
	std::cout << "The amount of concurrent threads are supported: " << n << std::endl; 

	return 0;
}