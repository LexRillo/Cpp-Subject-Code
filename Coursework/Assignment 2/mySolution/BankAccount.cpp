/*
 * BankAccount.cpp
 *
 *  Created on: Nov 12, 2017
 *      Author: np183
 *      Module: CO3105
 *      Department of Computer Science
 *      University of Leicester
 */

#include <iostream>
#include "BankAccount.h"
#include <map>

using std::string;
using std::ostream;

// Constructors
Account::Account(std::string name)
{
	name_ = name;
	balance_ = 0.0;
}

Account::Account(std::string name, float balance)
{
	name_ = name;
	balance_ = balance;
}

// Destructor
Account::~Account()
{
}

// Returns balance
float Account::balance() const
{
	return balance_;
}

// Performs a deposit operation
bool Account::deposit(float val)
{
	// Fail if val is negative
	if(val < 0){
		return false;
	}
	// Update balance
	balance_ += val;
	return true;
}

// Virtual method; not implemented
bool Account::withdraw(float val)
{
	return false;
}

// Virtual method; not implemented
void Account::day()
{
}

// Virtual method; not implemented
void Account::month()
{
}

// Returns the name of the Account
string Account::name() const {
	return name_;
}

// Returns the type of Account this is
string Account::type() const
{
	return type_;
}

// Virtual method; not implemented
string Account::toString() const
{
	return "";
}

// Virtual method; not implemented
ostream& operator<<(ostream& o, const Account& a)
{
	o << a.toString();
	return o;
}

// Constructors
CurrentAccount::CurrentAccount(std::string name, float overdraft, float interest, float fee)
: Account(name)
{
	type_ = "Current Account";
	overdraft_ = overdraft;
	interest_ = interest;
	fee_ = fee;
}

CurrentAccount::CurrentAccount(std::string name, float balance, float overdraft, float interest, float fee)
: Account(name,balance)
{
	type_ = "Current Account";
	overdraft_ = overdraft;
	interest_ = interest;
	fee_ = fee;	
}

// Withdraw operation
bool CurrentAccount::withdraw(float val){
	// Fail if val is negative or the amount to be withdrown goes over the overdraft limit
	if(val < 0 || balance_ + overdraft_ < val){
		return false;
	}
	// Update balance
	balance_ -= val;
	return true;
}

// Method that simulates the passing of a day and updates the account accordingly
void CurrentAccount::day(){
	// If the account is in overdraft
	if(balance_ < 0.0){
		// Apply interest
		balance_ = balance_ + ((interest_/100)*balance_);
		// If the account is below the overdraft limit
		if(balance_ < (-overdraft_)){
			// Apply a fee of 25
			balance_ -= 25.0;
		}
	}
}

// Method that simulates the passing of a month and updates the account accordingly
void CurrentAccount::month(){
	// Apply the monthly fee
	balance_ -= fee_;
}

// Printing method
std::string CurrentAccount::toString() const{
	// Convert float values to strings
	std::string sbalance = std::to_string(balance_);
	std::string sfee = std::to_string(fee_);
	std::string soverdraft = std::to_string(overdraft_);
	std::string s = type() + " of " + name_ + " (" + sbalance + ") (" + sfee + "," + soverdraft + ")";
	return s;
}

// Destructor
CurrentAccount::~CurrentAccount()
{
}

// Constructors
SavingsAccount::SavingsAccount(std::string name, float interest)
: Account(name)
{
	type_ = "Savings Account";
	interest_ = interest;
}

SavingsAccount::SavingsAccount(std::string name, float balance, float interest)
: Account(name,balance)
{
	type_ = "Savings Account";
	interest_ = interest;
}

// Withdraw operation
bool SavingsAccount::withdraw(float val){
	// Fail if val is negative or higher than the present balance
	if(val < 0 || val > balance_){
		return false;
	}
	// Update balance
	balance_ -= val;
	return true;
}

// Method that simulates the passing of a month and updates the account accordingly
void SavingsAccount::month(){
	// Apply interest
	balance_ = balance_ + ((interest_/100)*balance_);
}

// Printing method
std::string SavingsAccount::toString() const{
	// Convert float values to strings
	std::string sbalance = std::to_string(balance());
	std::string sinterest = std::to_string(interest_);
	std::string s = type() + " of " + name_ + " (" + sbalance + ") (" + sinterest + "%)";
	return s;
}

// Destructor
SavingsAccount::~SavingsAccount()
{
}

// Constructors
StockAccount::StockAccount(std::string name)
: Account(name)
{
	type_ = "Stock Account";
}

StockAccount::StockAccount(std::string name, float balance)
: Account(name,balance)
{
	type_ = "Stock Account";
}

// Withdraw operation
bool StockAccount::withdraw(float val){
	// Fail if val is negative or higher than the present balance
	if(val < 0 || val > balance_){
		return false;
	}
	// Update balance
	balance_ -= val;
	return true;
}

// Printing method
std::string StockAccount::toString() const{
	// Convert float values to strings
	std::string sbalance = std::to_string(balance_);
	std::string s = type() + " of " + name_ + " (" + sbalance + ")";
	
//	// Alternative looping
//	for(map<string, pair<string,string> >::const_iterator it = stocks_.begin(); it != stocks_.end(); ++it)
//	{
//    		std::cout << "(" << it->first << " " << it->second.first << " " << it->second.second << ")";
//	}
	
	// Loop through the stocks
	for(auto it = stocks_.cbegin(); it != stocks_.cend(); ++it) {
		// Convert float values to strings
		std::string sAmount = std::to_string(it->second.first);
		// The value to print is the total value calculated as: single value * amount
		float valueStocks = it->second.second * it->second.first;
		std::string sValue = std::to_string(valueStocks);
		s = s + " (" + it->first + "," + sAmount + "," + sValue + ")";
	}
	return s;
}

// Destructor
StockAccount::~StockAccount()
{
}

// Method to buy stocks
bool StockAccount::buy (const std::string stock, float amount, float value)
{
	// Check if amount and value are positive
	if( amount < 0 || value < 0){
		return false;
	}
	// Check if account can afford it
	if(balance_ < amount * value){
		return false;
	}
	// Check if the stock is already present in the map
	if (stocks_.count(stock)){
		// Update the stock with new amount and value
		float newamount = amount + (stocks_.at(stock).first);
		stocks_.erase(stock);
		stocks_.insert(std::make_pair(stock, std::make_pair(newamount, value)));
		// Update balance
		balance_ -= amount * value;
	}else{
		stocks_.insert(std::make_pair(stock, std::make_pair(amount, value)));
		// Update balance
		balance_ -= amount * value;
	}
	return true;
}

// Method to sell stocks
bool StockAccount::sell(const std::string stock, float amount)
{
	// Check if amount is positive
	if( amount < 0){
		return false;
	}
	// Check if the stock is already present in the map and if we are trying to sell more than we have
	if(stocks_.count(stock) && stocks_.at(stock).first >= amount){
		// Update balance
		balance_ += amount * stocks_.at(stock).second;
		// If we are selling them all then erase the record
		if(stocks_.at(stock).first == amount){
			stocks_.erase(stock);
		}else{
		// Update the stock record
			float newamount = (stocks_.at(stock).first) - amount;
			float tempValue = stocks_.at(stock).second;
			stocks_.erase(stock);
			stocks_.insert(std::make_pair(stock, std::make_pair(newamount, tempValue)));
		}
		return true;
	}
	return false;
}

// Method to update the value of a stock
bool StockAccount::update(const std::string stock, float value)
{
	// Check if value is positive
	if(value < 0){
		return false;
	}
	// Check if the stock is already present in the map
	if(stocks_.count(stock)){
		// Update the value of the stock
		float tempAmount = stocks_.at(stock).first;
		stocks_.erase(stock);
		stocks_.insert(std::make_pair(stock, std::make_pair(tempAmount, value)));
		return true;
	}
	return false;
}

/*
 * BankAccount.h
 *
 *  Created on: Nov 12, 2017
 *      Author: np183
 *      Module: CO3105
 *      Department of Computer Science
 *      University of Leicester
 */
