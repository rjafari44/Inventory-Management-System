#include "common.hpp"

// to remove the need for adding std:: everytime I want to use cout and cin
using std::cout;

// function to display the intro/guidelines, returns nothing
void displayIntro() {
  cout << "********** Welcome to Ray's Precious Metal Inventory **********\n"
       << "Before getting started, here is a description of what we offer and some things to keep in mind:\n"
       << "Here we offer precious metal storage services, such as deposits, withdrawals, and display of balance.\n"
       << "Each customer will have a maximum storage capacity of 100 kg.\n"
       << "Customers are allowed to deposit and withdraw fractionals in kg.\n"
       << "Please ensure you are keeping track of the deposit and withdrawal amounts.\n"
       << "***************************************************************\n\n";
}

// function to display the first main menu, returns nothing
void displayMenu1() {

  cout << "Please select the precious metal you wish to deposit or withdraw from:\n"
       << "1. Platinum\n"
       << "2. Gold\n"
       << "3. Diamond\n"
       << "4. Silver\n"
       << "5. Copper\n"
       << "6. Display Total Balance\n"
       << "0. EXIT\n"
       << "Enter your choice: ";
}

// function to display the second inner menu, returns nothing
void displayMenu2(const std::string &metalName) {
  cout << "\nDo you want to deposit or withdraw " << metalName << "?"
       << "\n1. Deposit"
       << "\n2. Withdraw"
       << "\n3. Main Menu"
       << "\nChoice: ";
}

// function to display the total user balance, returns nothing
void displayTotalBalance(const Inventory& storage){
  cout << "\n***** TOTAL BALANCE *****";
  cout << "\nPlatinum: " << storage.platinum; 
  cout << "\nGold:     " << storage.gold;
  cout << "\nDiamond:  " << storage.diamond;
  cout << "\nSilver:   " << storage.silver;
  cout << "\nCopper:   " << storage.copper;
  cout << "\n*************************\n\n";
}