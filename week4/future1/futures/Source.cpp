#include <iostream>
#include <future>
#include <string>
using namespace std;

int main()
{

	try {
		promise<string> prms;

		future<string> ftr = prms.get_future();

		prms.set_value("Hello");

		string ans = ftr.get();//if you get the value before setting it, it's an unkept promise
		cout << "Answer is " << ans << endl;

		// Try these statements one at a time!
		//ans = ftr.get(); //throws exception because it can only be read once 
		//prms.set_value("Again"); //throws exception because prms was already set and can only be set once 
	}
	catch (future_error &e) {
		cout << "Caught exception: " << e.what() << endl;
	}

}