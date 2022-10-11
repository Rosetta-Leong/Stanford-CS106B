/*
 * CS 106B/X, Marty Stepp
 *
 * This file provides the implementation of the bodies of the member functions
 * and constructor for the BankAccount class declared in BankAccount.h.
 */

#include "bankaccount.h"

BankAccount::BankAccount(string n, double bal) {
    if (bal < 0) {
        throw bal;
    }
    name = n;
    balance = bal;
}

void BankAccount::deposit(double amount) {
    if (amount >= 0.00) {
        balance += amount;
    }
}

double BankAccount::getBalance() const {
    return balance;
}

string BankAccount::getName() const {
    return name;
}

void BankAccount::withdraw(double amount) {
    if (amount >= 0.00 && balance >= amount) {
        balance -= amount;
    }
}
