#ifndef __SIMPLE_ATM_HPP__
#define __SIMPLE_ATM_HPP__

#include <iostream>
#include <string>
#include <regex>
#include <atomic>
#include <shared_mutex>
#include <string>
#include <memory>
#include <unordered_map>

class BankAccount
{
  public:
    typedef signed long long int balance_t;
    typedef unsigned long long int account_t;
    typedef std::shared_ptr<BankAccount> Ptr;
    BankAccount() 
    {
      minimum_balance_ = 0;
      balance_ = 0;
      account_holder_ = "";
      account_number_ = 0;
    }

    const void printAccount() const;
    const balance_t getBalance() const;
    const void printBalance() const;
    bool withdraw(balance_t& amount);
    bool deposit(balance_t& amount);
 
    private:
      balance_t minimum_balance_;
      std::atomic<balance_t> balance_;
      std::string account_holder_;
      account_t account_number_;

      // balance_t transaction_deposit_limit_;
      // balance_t transaction_withdraw_limit_;
  
};

// Dummy class to that handles Bank server API, which holds information
class BankServer {
  private:
    // Should be server internal
    std::unordered_map<std::string, BankAccount::Ptr> bank_accounts_;
    std::string url_;
    BankAccount::Ptr bank_account_;
  public: 
    BankServer(const std::string& url = "") {
      url_ = url;
      accessServer(url_);
      //Make Dummy account
      bank_account_ = std::make_shared<BankAccount>();
    }
    bool accessServer(const std::string& url);
    BankAccount::Ptr getAccount(const std::string& pin);
    BankAccount::Ptr insertCard();
    BankAccount::Ptr processPIN(const std::string& pin);
    bool validatePIN(const std::string& pin);

};
#endif