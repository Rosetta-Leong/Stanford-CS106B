/*
 * CS 106B/X, Marty Stepp
 * This file declares a class named BankAccount.
 * A class is a template or blueprint for a new type of objects.
 *
 * Each BankAccount object represents information about a single
 * person's bank account, such as their name and balance.
 *
 * Implementation of each class member, and comment documentation about each
 * member, are found in BankAccount.cpp.
 */

#ifndef _bankaccount_h
#define _bankaccount_h

#include <string>
using namespace std;

class BankAccount {
public:
    /* constructor - initializes the state of each newly created account. */
    BankAccount(string n, double bal = 0.00);

    /* Adds the given amount of money to this account's balance. */
    void deposit(double amount);

    /* Returns a read-only view of this account's balance. */
    double getBalance() const;

    /* Returns a read-only view of this account's name. */
    string getName() const;

    /* Subtracts the given amount of money from this account's balance. */
    void withdraw(double amount);

// private member variables (instance variables) - data within each object
private:
    string name;
    double balance;
};

#endif
