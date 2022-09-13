#include "simple_atm.hpp"

const void BankAccount::printAccount() const {
  std::cout << "Account Holders Name: " << account_holder_ << std::endl;
  printBalance();
}

const BankAccount::balance_t BankAccount::getBalance() const {
  return balance_; 
}

const void BankAccount::printBalance() const {
  std::cout << "\Current Balance: $" << balance_ << std::endl;
}
    
bool BankAccount::withdraw(BankAccount::balance_t& amount) {
  auto remaining = balance_ - amount;
  bool success = remaining >= minimum_balance_;

  if (!success) {
    std::cout << "Withdraw failed, Insufficient Balance: $" << remaining - minimum_balance_ << std::endl;
    }
  else {
    balance_ -= amount;
    std::cout << "Successfully Withdrawn $" << amount << std::endl;
    printBalance();
  }
  return success;
}

bool BankAccount::deposit(balance_t& amount) {
    balance_ += amount;
    std::cout << "Successfully Deposited $" << amount << std::endl;
    printBalance();
    return true;
}

bool BankServer::accessServer(const std::string& url) {
  // Dummy - Always success to access server
  // bank_accounts_ = 
  return true;
}

BankAccount::Ptr BankServer::getAccount(const std::string& pin) {
  // Return new empty account since don't have database
  return std::make_shared<BankAccount>();
  //return bank_account_ = bank_accounts_[pin];
}

BankAccount::Ptr BankServer::insertCard() {
  std::cout << "Please Insert Card \n";
  std::cout << "Please Enter PIN: ";
  std::string pin;
  std::cin >> pin;
  BankAccount::Ptr account_ptr = processPIN(pin);
  account_ptr->printAccount();
  return account_ptr;
}

BankAccount::Ptr BankServer::processPIN(const std::string& pin) {
  if (validatePIN(pin)) {
    return getAccount(pin);
  } else {
    std::cout << "Incorrect PIN: " + pin << std::endl;
  }
  return nullptr;
}

bool BankServer::validatePIN(const std::string& pin) {
  // PIN should be 4-12 digits integer ranged (0-9)
  // acoording to https://en.wikipedia.org/wiki/Personal_identification_number
  std::regex re("^\\d{4,12}");
  bool valid = std::regex_match(pin, re);
  return valid;
}