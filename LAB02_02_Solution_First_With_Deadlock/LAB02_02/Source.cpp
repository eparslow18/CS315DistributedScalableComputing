#include <iostream>
#include <thread>
#include <mutex>
#include <ppl.h>
#include <condition_variable>

using namespace std;
using namespace concurrency;

#define AMOUNT	20


class BankAccount {
private:	
	int amount;
	mutex m;
	condition_variable cv;

public:
	BankAccount(int amount) : amount(amount) {}

	/**
	*	Deposits money into account
	*/
	void Deposit(int dollar) {
		unique_lock<mutex> lk(m);
		amount += dollar;	
		cout << "Deposit. Bank has " << amount << endl;
		if (amount >= AMOUNT)
			cv.notify_all();
	}

	/**
	*	Withdraws money from account
	*	If account has less money than the amount requested, 
	*	return false.
	*/
	bool Withdraw(int dollar) {
		unique_lock<mutex> lk(m);
		if ( amount < AMOUNT) {
			//cv.wait(lk, [this]() {  // will deadlock about 50% of the time
			 cv.wait_for(lk, 1s, [this]() {   // one possible solution
				return this->amount >= AMOUNT;
			});
		}

		if (amount >= dollar) {  // double check the ammount! Don't assume!
			amount -= dollar;
			cout << "Withdrawal. Bank has " << amount << endl;
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
	BankAccount myAccount(0); // Open an account with an initial amount of $0

	parallel_for(0, 1000,[&myAccount](int tid) {

		if (tid % 2 == 0) { // every other thread will withdraw 
			myAccount.Withdraw(AMOUNT); // Withdraw some amount
		}
		else {
			myAccount.Deposit(AMOUNT); // Deposit some amount
		}
	});

	cout << "My account has " << myAccount.Amount() << endl;

}