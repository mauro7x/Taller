#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <mutex>

class Account {
public:
  Account();
  void withdraw(int amount);
  void deposit(int amount);
  int getBalance() const;
private:
  int balance;
  std::mutex mutex;
};

#endif
