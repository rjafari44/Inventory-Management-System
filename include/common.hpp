#pragma once

#include <string>
#include <iostream>

// global variable for max storage amount allowed
inline const int MAX_LIMIT{100};

// struct for the different precious metals
struct Inventory {
  float platinum{}, gold{}, diamond{}, silver{}, copper{};
};

// enumerated type for the first outer menu
enum Metals { EXIT, PLATINUM, GOLD, DIAMOND, SILVER, COPPER, BALANCE };

// enumerated type for the second inner menu
enum Operation { QUIT, DEPOSIT, WITHDRAW, MAIN_MENU };


// function declarations
void displayIntro();
void displayMenu1();
void displayMenu2(const std::string &metalName);
bool isValidDeposit(float depoAmt, float currentBalance);
bool isValidWithdrawal(float withdrawAmt, float currentBalance);
void manageInventory(float &metalChoiceBal, const std::string &metalName);
void displayTotalBalance(const Inventory& storage);