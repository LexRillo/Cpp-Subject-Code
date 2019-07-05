/*
 * BankAccountTester.cpp
 *
 *  Created on: Dec 2, 2017
 *      Author: np183
 */

#include <sstream>
#include <algorithm>
#include <map>
#include <vector>
#include <iostream>
#include <math.h>
#include <cfloat>

#include "BankAccountTester.h"

typedef unsigned int uint;

using std::string;
using std::remove_if;
using std::stringstream;
using std::map;
using std::vector;
using std::pair;
using std::make_pair;
using std::to_string;
using std::cout;
using std::endl;

const string LPAREN = "("; // )
const string RPAREN = /*(*/ ")";

BankAccountTester::BankAccountTester(int i) : TesterBase(i) {
}

BankAccountTester::~BankAccountTester() {
}

void BankAccountTester::testCurrentConstructor() {
  func_("testCurrentConstructor");

  string temp = randString_(10);
  float balance = static_cast<float>(rand()%10000);
  CurrentAccount a1(temp,0.0,0.0,0.0);
  CurrentAccount a2(temp,balance,0.0,0.0,0.0);

  if (neq_(a1.balance(),0.0) || neq_(a2.balance(),balance))  {
	  errorOut_("balance not inititalized correctly");
  }
  if (a1.name() != temp || a2.name() != temp) {
	  errorOut_("name is not initialized correctly",1);
  }

  passOut_("tested basic construction of current account");
}

void BankAccountTester::testSavingsConstructor() {
  func_("testSavingsConstructor");
  string temp = randString_(10);
  float balance = static_cast<float>(rand()%10000);
  SavingsAccount a1(temp,0.0);
  SavingsAccount a2(temp,balance,0.0);

  if (neq_(a1.balance(),0.0) || neq_(a2.balance(),balance))  {
	  errorOut_("balance not inititalized correctly");
  }
  if (a1.name() != temp || a2.name() != temp) {
	  errorOut_("name is not initialized correctly",1);
  }

  passOut_("tested basic construction of savings account");
}

void BankAccountTester::testStockConstructor() {
  func_("testStockConstructor");
  string temp = randString_(10);
  float balance = static_cast<float>(rand()%10000);
  StockAccount a1(temp);
  StockAccount a2(temp,balance);

  if (neq_(a1.balance(),0.0) || neq_(a2.balance(),balance))  {
	  errorOut_("balance not inititalized correctly");
  }
  if (a1.name() != temp || a2.name() != temp) {
	  errorOut_("name is not initialized correctly",1);
  }

  passOut_("tested basic construction of stock account");
}

void BankAccountTester::testBalance() {
  func_("testBalance");
  {
	  CurrentAccount a1("blah",0.0,0.0,0.0,0.0);
	  SavingsAccount a2("blah",0.0,0.0);
	  StockAccount a3("blah",0.0);
	  Account* accounts[3] {&a1, &a2, &a3};

	  float balance = 0.0;
	  for (unsigned int i=0 ; i<10 && !errorSet_(1) ; ++i) {
		  float deposit = static_cast<float>(rand()%100);
		  balance += deposit;
		  for (unsigned j=0 ; j<3 ; ++j) {
			  accounts[j]->deposit(deposit);
			  if (neq_(accounts[j]->balance(),balance)) {
				  errorOut_("deposit leads to wrong balance");
			  }
		  }
	  }
  }

  {
	  CurrentAccount a1("blah",1000.0,1000.0,0.0,0.0);
	  SavingsAccount a2("blah",1000.0,0.0);
	  StockAccount a3("blah",1000.0);
	  Account* accounts[3] {&a1, &a2, &a3};

	  float balance[3] =  { 1000.0, 1000.0 , 1000.0};
	  float overdraft[3] = { 1000.0 , 0.0 , 0.0 };

	  char frozen=0;
	  while ((!(frozen&1) || !(frozen&2) || !(frozen&4)) &&
			  (!errorSet_(1<<1) || !errorSet_(1<<2) ||  !errorSet_(1<<3))) {
		  float withdraw = static_cast<float>(rand()%100+1);
		  for (unsigned j=0 ; j<3 ; ++j) {
			  if (balance[j] + overdraft[j] >= withdraw) {
				  balance[j] -= withdraw;
				  if (!accounts[j]->withdraw(withdraw)) {
					  errorOut_("withdraw not allowed with available funds",1);
					  continue;
				  }
				  if (neq_(accounts[j]->balance(),balance[j])) {
					  errorOut_("withdraw leads to wrong balance",2);
				  }
			  } else {
				  frozen |= 1<<j;
				  if (accounts[j]->withdraw(withdraw)) {
					  errorOut_("withdraw allowed when no funds available",3);
				  }
			  }
		  }
	  }
  }
  passOut_("check the balance after deposit and withdraw");
}

void BankAccountTester::testType() {
  func_("testType");
  string temp = randString_(10);
  CurrentAccount a1(temp,1000.0,1000.0,0.0,0.0);
  SavingsAccount a2(temp,1000.0,0.0);
  StockAccount a3(temp,1000.0);
  Account* accounts[3] {&a1, &a2, &a3};

  if (accounts[0]->type() != "Current Account" &&
	  accounts[0]->type() != "current account" &&
	  accounts[0]->type() != "Current account") {
	  errorOut_("current account has wrong type");
  }
  if (accounts[1]->type() != "Savings Account" &&
	  accounts[1]->type() != "savings account" &&
	  accounts[1]->type() != "Savings account") {
	  errorOut_("savings account has wrong type",1);
  }
  if (accounts[2]->type() != "Stock Account" &&
	  accounts[2]->type() != "stock account" &&
	  accounts[2]->type() != "Stock account") {
	  errorOut_("stock account has wrong type",2);
  }
  passOut_("tested the type");
}
void BankAccountTester::testToString() {
  func_("testToString");
  string name = randString_(10);
  float balance = static_cast<float>(rand()%1000+1);
  float overdraft = static_cast<float>(rand()%1000+1);
  float interest = static_cast<float>(rand()%100+1);
  float fee = static_cast<float>(rand()%10+1);

  CurrentAccount a1(name,balance,overdraft,interest,fee);
  SavingsAccount a2(name,balance,interest);
  StockAccount a3(name,balance);
  Account* accounts[3] {&a1, &a2, &a3};
  string res[3];
  res[0] = "Current Account of " + name + " " + LPAREN;
  res[0] += to_string(balance);
  res[0] += RPAREN + " " + LPAREN;
  res[0] += to_string(fee);
  res[0] += ",";
  res[0] += to_string(overdraft);
  res[0] += RPAREN;

  res[1] = "Savings Account of " + name + " " + LPAREN;
  res[1] += to_string(balance);
  res[1] += RPAREN + " " + LPAREN;
  res[1] += to_string(interest);
  string savingaccountaltres = res[1] + RPAREN;
  res[1] += "%" + RPAREN;

  res[2] = "Stock Account of " + name + " " + LPAREN;
  res[2] += to_string(balance);
  res[2] += RPAREN;

  unsigned int i=0;
  string output = accounts[i]->toString();
  if (output != res[i]) {
	  if (removeSpaces_(output) == removeSpaces_(res[i])) {
		  errorOut_("string of current account not as expected with only space difference",1);
	  } else if (lc_(output) == lc_(res[i])) {
		  errorOut_("string of current account not as expected with only case difference",2);
	  } else if (removeSpaces_(lc_(output)) == removeSpaces_(lc_(res[i]))) {
		  errorOut_("string of current account not as expected with only case and spaces difference",3);
	  } else {
		  errorOut_("string of current account not as expected");
	  }
  }

  ++i;
  output = accounts[i]->toString();
  if (output != res[i] && output != savingaccountaltres) {
	  if (removeSpaces_(output) == removeSpaces_(res[i]) ||
	  	  removeSpaces_(output) == removeSpaces_(savingaccountaltres)) {
		  errorOut_("string of savings account not as expected with only space difference",5);
	  } else if (lc_(output) == lc_(res[i]) ||
			  	 lc_(output) == lc_(savingaccountaltres)) {
		  errorOut_("string of savings account not as expected with only case difference",6);
	  } else if (removeSpaces_(lc_(output)) == removeSpaces_(lc_(res[i])) ||
			     removeSpaces_(lc_(output)) == removeSpaces_(lc_(savingaccountaltres))) {
		  errorOut_("string of savings account not as expected with only case and spaces difference",7);
	  } else {
		  errorOut_("string of savings account not as expected",4);
	  }
  }

  ++i;
  string stocks[3];
  for (unsigned int j=0 ; j<3 ; ++j) {
	  string stock = randString_(5);
	  float quantity = static_cast<float>(rand()%100+1);
	  float value = static_cast<float>(rand()%100+1);
	  accounts[2]->deposit(value*quantity);
	  StockAccount* sa = dynamic_cast<StockAccount*>(accounts[2]);
	  sa->buy(stock,quantity,value);
	  stocks[j] = LPAREN + stock + "," + to_string(quantity);
	  stocks[j] += ",";
	  stocks[j] += to_string(quantity*value) + RPAREN;
  }
  vector<string> sres;
  sres.push_back(res[2] + " " + stocks[0] + " " + stocks[1] + " " + stocks[2]);
  sres.push_back(res[2] + " " + stocks[0] + " " + stocks[2] + " " + stocks[1]);
  sres.push_back(res[2] + " " + stocks[1] + " " + stocks[0] + " " + stocks[2]);
  sres.push_back(res[2] + " " + stocks[1] + " " + stocks[2] + " " + stocks[0]);
  sres.push_back(res[2] + " " + stocks[2] + " " + stocks[0] + " " + stocks[1]);
  sres.push_back(res[2] + " " + stocks[2] + " " + stocks[1] + " " + stocks[0]);

  output = accounts[i]->toString();

  if (std::all_of(sres.begin(),sres.end(),[&](const string& s) { return s!=output; })) {
	  if (std::any_of(sres.begin(),sres.end(),[&](const string& s) { return this->removeSpaces_(s) == this->removeSpaces_(output);})) {
		  errorOut_("string of stock account not as expected with only space difference",9);
	  } else if (std::any_of(sres.begin(),sres.end(),[&](const string& s) { return lc_(output) == lc_(s); })) {
		  errorOut_("string of stock account not as expected with only case difference",10);
	  } else if (std::any_of(sres.begin(),sres.end(),[&](const string& s) { return removeSpaces_(lc_(output)) == removeSpaces_(lc_(s)); })) {
		  errorOut_("string of stock account not as expected with only case and spaces difference",11);
	  } else {
		  errorOut_("string of stock account not as expected",8);
	  }
  }

  passOut_("conveted all accounts to strings");
}
void BankAccountTester::testOperatorRedir() {
  func_("testOperatorRedir");
  string name = randString_(10);
  float balance = static_cast<float>(rand()%1000+1);
  float overdraft = static_cast<float>(rand()%1000+1);
  float interest = static_cast<float>(rand()%100+1);
  float fee = static_cast<float>(rand()%10+1);

  CurrentAccount a1(name,balance,overdraft,interest,fee);
  SavingsAccount a2(name,balance,interest);
  StockAccount a3(name,balance);
  Account* accounts[3] {&a1, &a2, &a3};
  string res[3];
  res[0] = "Current Account of " + name + " " + LPAREN;
  res[0] += to_string(balance) + RPAREN + " " + LPAREN + to_string(fee);
  res[0] += ",";
  res[0] += to_string(overdraft) + RPAREN;

  res[1] = "Savings Account of " + name + " " + LPAREN;
  res[1] += to_string(balance) + RPAREN + " " + LPAREN + to_string(interest);
  string savingaccountaltres = res[1] + "%" + RPAREN;
  res[1] += RPAREN;

  res[2] = "Stock Account of " + name + " " + LPAREN;
  res[2] += to_string(balance) + RPAREN;

  unsigned int i=0;
  string output;
  {
	  stringstream stream;
	  stream << *accounts[i];
	  output = stream.str();
  }
  if (output != res[i]) {
	  if (removeSpaces_(output) == removeSpaces_(res[i])) {
		  errorOut_("string of current account not as expected with only space difference",1);
	  } else if (lc_(output) == lc_(res[i])) {
		  errorOut_("string of current account not as expected with only case difference",2);
	  } else if (removeSpaces_(lc_(output)) == removeSpaces_(lc_(res[i]))) {
		  errorOut_("string of current account not as expected with only case and spaces difference",3);
	  } else {
		  errorOut_("string of current account not as expected");
	  }
  }

  ++i;
  {
	  stringstream stream;
	  stream << *accounts[i];
	  output = stream.str();
  }
  if (output != res[i] && output != savingaccountaltres) {
	  if (removeSpaces_(output) == removeSpaces_(res[i]) ||
	  	  removeSpaces_(output) == removeSpaces_(savingaccountaltres)) {
		  errorOut_("string of savings account not as expected with only space difference",5);
	  } else if (lc_(output) == lc_(res[i]) ||
			  	 lc_(output) == lc_(savingaccountaltres)) {
		  errorOut_("string of savings account not as expected with only case difference",6);
	  } else if (removeSpaces_(lc_(output)) == removeSpaces_(lc_(res[i])) ||
			     removeSpaces_(lc_(output)) == removeSpaces_(lc_(savingaccountaltres))) {
		  errorOut_("string of savings account not as expected with only case and spaces difference",7);
	  } else {
		  errorOut_("string of savings account not as expected",4);
	  }
  }

  ++i;
  string stocks[3];
  for (unsigned int j=0 ; j<3 ; ++j) {
	  string stock = randString_(5);
	  float quantity = static_cast<float>(rand()%100+1);
	  float value = static_cast<float>(rand()%100+1);
	  accounts[2]->deposit(value*quantity);
	  StockAccount* sa = dynamic_cast<StockAccount*>(accounts[2]);
	  sa->buy(stock,quantity,value);
	  stocks[j] = LPAREN + stock + "," + to_string(quantity);
	  stocks[j] += ",";
	  stocks[j] += to_string(quantity*value) + RPAREN;
  }
  vector<string> sres;
  sres.push_back(res[2] + " " + stocks[0] + " " + stocks[1] + " " + stocks[2]);
  sres.push_back(res[2] + " " + stocks[0] + " " + stocks[2] + " " + stocks[1]);
  sres.push_back(res[2] + " " + stocks[1] + " " + stocks[0] + " " + stocks[2]);
  sres.push_back(res[2] + " " + stocks[1] + " " + stocks[2] + " " + stocks[0]);
  sres.push_back(res[2] + " " + stocks[2] + " " + stocks[0] + " " + stocks[1]);
  sres.push_back(res[2] + " " + stocks[2] + " " + stocks[1] + " " + stocks[0]);

  {
	  stringstream stream;
	  stream << *accounts[i];
	  output = stream.str();
  }
  if (std::all_of(sres.begin(),sres.end(),[&](const string& s) { return s!=output; })) {
	  if (std::any_of(sres.begin(),sres.end(),[&](const string& s) { return this->removeSpaces_(s) == this->removeSpaces_(output);})) {
		  errorOut_("string of stock account not as expected with only space difference",9);
	  } else if (std::any_of(sres.begin(),sres.end(),[&](const string& s) { return lc_(output) == lc_(s); })) {
		  errorOut_("string of stock account not as expected with only case difference",10);
	  } else if (std::any_of(sres.begin(),sres.end(),[&](const string& s) { return removeSpaces_(lc_(output)) == removeSpaces_(lc_(s)); })) {
		  errorOut_("string of stock account not as expected with only case and spaces difference",11);
	  } else {
		  errorOut_("string of stock account not as expected",8);
	  }
  }
  passOut_("redirected all types of accounts");
}

void BankAccountTester::testDay() {
  func_("testDay");
  string name = randString_(10);
  float balance = static_cast<float>(rand()%1000+1);
  float overdraft = static_cast<float>(rand()%1000+2);
  float interest = static_cast<float>(rand()%100+1);
  float fee = static_cast<float>(rand()%10+1);

  CurrentAccount a1(name,balance,overdraft,interest,fee);
  SavingsAccount a2(name,balance,interest);
  StockAccount a3(name,balance);
  Account* accounts[3] {&a1, &a2, &a3};

  for (unsigned int i = 0 ; i<3 ; ++i) {
	  accounts[i]->day();
  }

  if (neq_(accounts[0]->balance(),balance)) {
	  errorOut_("wrong balance in current account in plus");
  }
  if (neq_(accounts[1]->balance(),balance)) {
	  errorOut_("wrong balance in savings account after day",1);
  }
  if (neq_(accounts[2]->balance(),balance)) {
	  errorOut_("wrong balance in stock account after day",2);
  }

  accounts[0]->withdraw(balance+1);
  accounts[0]->day();
  if (neq_(accounts[0]->balance(),-1.0*(1.0 + interest/100.0))) {
	  errorOut_("wrong balance in current account after day in overdraft",3);
  }

  CurrentAccount a4(name,balance,overdraft,interest,fee);
  accounts[0] = &a4;
  accounts[0]->withdraw(balance+overdraft);
  accounts[0]->day();
  accounts[0]->day();

  float d1exp[2];
  d1exp[0] = (-1.0 - interest/100.0)*overdraft;
  d1exp[1] = d1exp[0]-25.0;
  float d2exp[4];
  for (unsigned int i=0 ; i<2 ; ++i) {
	  d2exp[2*i] = (d1exp[i]-25.0)*(interest/100.0+1.0);
	  d2exp[2*i+1] = d1exp[i]*(interest/100.0+1.0)-25.0;
  }

  for (unsigned int i=0 ; i<4 ; ++i) {
	  if (eq_(accounts[0]->balance(),d2exp[i])) {
		  passOut_("played with the passage of days");
		  return;
	  }
  }
  errorOut_("wrong balance in current account after day below overdraft limit",4);
  passOut_("played with the passage of days");
}
void BankAccountTester::testMonth() {
  func_("testMonth");
  string name = randString_(10);
  float balance = static_cast<float>(rand()%1000+1);
  float overdraft = static_cast<float>(rand()%1000+1);
  float interest = static_cast<float>(rand()%100+1);
  float fee = static_cast<float>(rand()%10+1);

  CurrentAccount a1(name,balance,overdraft,interest,fee);
  SavingsAccount a2(name,balance,interest);
  StockAccount a3(name,balance);
  Account* accounts[3] {&a1, &a2, &a3};

  for (unsigned int i = 0 ; i<3 ; ++i) {
	  accounts[i]->month();
  }

  if (neq_(accounts[0]->balance(),balance-fee)) {
	  errorOut_("wrong balance in current account after fee reduction");
  }
  if (neq_(accounts[1]->balance(),balance + balance *(interest / 100.0))) {
	  errorOut_("wrong balance in savings account after interest credit",1);
  }
  if (neq_(accounts[2]->balance(),balance)) {
	  errorOut_("wrong balance in stock account after month",2);
  }

  passOut_("played with the passage of months");
}
void BankAccountTester::testBuySell() {
  func_("testBuySell");
  StockAccount a("blah",0.0);

  map<string,pair<float,float>> stocks_m;
  vector<string> stocks_v;

  for (unsigned int j=0 ; j<150 ; ++j) {
	  switch (rand()%15) {
	  case 0: // Buy new stock succeed
	  case 1:
	  case 2:
	  case 3:
	  case 4:
	  {
		  string stock = randString_(10);
		  while (stocks_m.find(stock)!= stocks_m.end()) {
			  stock=randString_(10);
		  }
		  float amount = static_cast<float>(rand()%100+1);
		  float value = static_cast<float>(rand()%1000+1);
		  a.deposit(amount*value);
		  if (a.buy(stock,amount,value)) {
			  stocks_m.insert(make_pair(stock,make_pair(amount,value)));
			  stocks_v.push_back(stock);
		  } else {
		    errorOut_("failed to buy stock with sufficient funds");
		  }
	  }
	  break;
	  case 5: // Buy new stock fail
	  {
		  string stock = randString_(10);
		  while (stocks_m.find(stock)!= stocks_m.end()) {
			  stock=randString_(10);
		  }
		  float amount = static_cast<float>(rand()%100+1);
		  float value = static_cast<float>(rand()%1000+1);
		  if (a.buy(stock,amount,value)) {
		    errorOut_("bought stock without funds",1);
		  }
	  }
	  break;
	  case 6: // Buy existing stock (including amount 0.0)
	  case 7:
	  case 8:
	  {
		  if (stocks_v.size()>0) {
			  string stock = stocks_v[rand()%stocks_v.size()];

			  float amount = static_cast<float>(rand()%100+1);
			  float value = static_cast<float>(rand()%1000+1);
			  a.deposit(amount*value);
			  if (a.buy(stock,amount,value)) {
				  auto it = stocks_m.find(stock);
				  it->second.first +=  amount;
				  it->second.second = value;
				  stocks_v.push_back(stock);
			  } else {
			    errorOut_("failed to buy stock with sufficient funds",2);
			  }
		  } else {
			  --j;
		  }
	  }
	  break;
	  case 9: // Sell existing stock succeed
	  case 10:
	  {
		  if (stocks_v.size() > 0) {
			  string stock = stocks_v[rand()%stocks_v.size()];
			  auto it = stocks_m.find(stock);
			  float amount = it->second.first;
			  float value = it->second.second;
			  if (neq_(amount,0.0)) {
				  // Just sell everything
				  if (a.sell(stock,amount)) {
					  if (neq_(amount*value,a.balance())) {
					    errorOut_("sale of stock leads to wrong balance",3);
					  }
					  it->second.first = 0.0;
					  a.withdraw(a.balance());
				  } else {
				    errorOut_("failed to sell existing stock",4);
				  }
			  } else {
				  --j;
			  }
		  } else {
			  --j;
		  }
	  }
		  break;
	  case 11: // Sell existing stock fail
	  {
		  if (stocks_v.size() > 0) {
			  string stock = stocks_v[rand()%stocks_v.size()];
			  auto it = stocks_m.find(stock);
			  float amount = it->second.first;
			  float value = it->second.second;
			  if (a.sell(stock,amount+1.0)) {
			    errorOut_("sold stocks in a quantity larger than existing",5);
				  // Attempt to get the balance to 0
				  a.withdraw(a.balance());
			  }
		  } else {
			  --j;
		  }
	  }
		  break;
	  case 12: // Sell non-existing stock
	  {
		  string stock = randString_(10);
		  while (stocks_m.find(stock)!= stocks_m.end()) {
			  stock = randString_(10);
		  }
		  float amount = 1.0;
		  if (a.sell(stock,amount)) {
		    errorOut_("sold non existing stocks",6);
			  // Attempt to get the balance to 0
			  a.withdraw(a.balance());
		  }
	  }
		  break;
	  case 13: // Update stock price
	  {
		  if (stocks_v.size() > 0) {
			  string stock = stocks_v[rand()%stocks_v.size()];
			  auto it=stocks_m.find(stock);
			  float value = static_cast<float>(rand()%1000);
			  if (!a.update(stock,value)) {
			    errorOut_("failed to update an existing stock",7);
			  } else {
				  it->second.second=value;
			  }
		  } else {
			  --j;
		  }
	  }
	  break;
	  case 14: // update non existing stock
	  {
		  string stock = randString_(10);
		  while (stocks_m.find(stock)!= stocks_m.end()) {
			  stock = randString_(10);
		  }
		  float value = 1.0;
		  if (a.update(stock,value)) {
		    errorOut_("updated non-existing stock",8);
		  }
	  }
	  break;
	  }
  }
  passOut_("bought and sold various stocks");
}

// Taken from
// https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
bool BankAccountTester::eq_(float A, float B)
{
	// Calculate the difference.
	float diff = fabs(A - B);
	A = fabs(A);
	B = fabs(B);
	// Find the largest
	float largest = (B > A) ? B : A;
	// cout << "A " << A << " B " << B << " TOL " << largest * FLT_EPSILON * 100.0f << endl;
	if (diff <= largest * FLT_EPSILON * 100.0f)
		return true;
	return false;
}

bool BankAccountTester::neq_(float A, float B) {
	return !eq_(A,B);
}
