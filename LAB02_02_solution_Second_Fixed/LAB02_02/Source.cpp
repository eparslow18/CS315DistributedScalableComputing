#include <iostream>
#include <thread>
#include <mutex>
#include <ppl.h>
#include <condition_variable>
#include <mutex>
using namespace std;
using namespace concurrency;

condition_variable cv;
mutex m;

#define AMOUNT	20
class BankAccount {
private:	
	int amount;

public:
	BankAccount(int amount) : amount(amount) {}

	void Deposit(int dollar) {
		amount += dollar;	
		if (amount >= AMOUNT)
			cv.notify_one();
	}

	bool Withdraw(int dollar) {
		if (amount >= dollar) {
			amount -= dollar;
			return true;
		}
		else {
			return false;
		}
	}

	int Amount() {
		return amount;
	}
};

int main()
{
	BankAccount myAccount(0); // Open an account with an initial amount of $10

	parallel_for(0, 1000,[&myAccount](int tid) {
		unique_lock<mutex> lk(m);
		if (tid % 2 == 0) { // every other thread will withdraw 
			if (myAccount.Amount() < AMOUNT) {
				cv.wait(lk, [&myAccount]() {
					return myAccount.Amount() >= AMOUNT;
				});
			}
			myAccount.Withdraw(AMOUNT); // Withdraw some amount
		}
		else {
			myAccount.Deposit(AMOUNT); // Deposit some amount
		}
	});

	cout << "My account has $" << myAccount.Amount() << endl;

}