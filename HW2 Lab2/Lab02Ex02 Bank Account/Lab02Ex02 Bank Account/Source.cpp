#include <iostream>
#include <thread>
#include <ppl.h>
#include <mutex> //ex02 q3
#include <condition_variable> //ex04

using namespace std;
using namespace concurrency;

#define AMOUNT	20
class BankAccount {
private:
	int amount;
	mutex m; //ex02 q3
	condition_variable cv; //ex04

public:
	BankAccount(int amount) : amount(amount) {}

	/**
	*	Deposits money into account
	*/
	void Deposit(int dollar) {

		if (amount >= AMOUNT) //ex04
			cv.notify_one();

		unique_lock<mutex> lk(m); //ex02 q3
		
		amount += dollar;
	}

	/**
	*	Withdraws money from account
	*	If account has less money than the amount requested,
	*	it does not perform the withdrawal.
	*/
	bool Withdraw(int dollar) {
		unique_lock<mutex> lk(m); //ex02 q3

		if (amount < AMOUNT) { //ex04
			cv.wait(lk, [this]() {
				return this->amount >= AMOUNT;
			});
		}


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
	BankAccount myAccount(0); // Open an account with an initial balance of $0

	parallel_for(0, 1000, [&](int tid) {
		if (tid % 2 == 0) { // every other thread will withdraw 
			myAccount.Withdraw(AMOUNT); // Withdraw some amount
		}
		else {
			myAccount.Deposit(AMOUNT); // Deposit some amount
		}
	});

	cout << "My account has $" << myAccount.Amount() << endl;
}