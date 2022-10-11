/*
 * CS 106B/X, Marty Stepp
 *
 * This program is a "client" that uses our BankAccount class.
 * The main purpose of writing new classes is so that
 * client programs can use your new objects.
 */

#include <iostream>
#include "console.h"
#include "bankaccount.h"
using namespace std;

int bank_main() {
    // create bank account objects using the constructor
    BankAccount ba1("Tyler", 1.25);
    BankAccount ba2("Mehran Sahami", 999995.00);

    // call methods on the accounts
    ba1.deposit(5.00);
    ba1.withdraw(12.00);
    cout << ba1.getName() << " $" << ba1.getBalance() << endl;

    ba2.deposit(1.00);
    cout << ba2.getName() << " $" << ba2.getBalance() << endl;

    cout << "Have a nice day." << endl;
    return 0;
}
