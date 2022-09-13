#include "simple_atm.hpp"
#include <gtest/gtest.h>

TEST(ATM, BasicTests)
{
    BankServer bank_server;
    BankAccount::Ptr bank_account_ptr = bank_server.processPIN("12345");
    ASSERT_TRUE(bank_account_ptr != nullptr);
    
    BankAccount::balance_t amount = 100000;
    EXPECT_FALSE(bank_account_ptr->withdraw(amount));
    EXPECT_TRUE(bank_account_ptr->deposit(amount));
    EXPECT_TRUE(bank_account_ptr->withdraw(amount));
}

// int main(int argc, char** argv)
// {
//   ::testing::InitGoogleTEST(&argc, argv);
//   return RUN_ALL_TESTS();
// }