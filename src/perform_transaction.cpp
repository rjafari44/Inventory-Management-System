#include "common.hpp"

// to remove the need for adding std:: everytime I want to use cout and cin
using std::cin, std::cout;

/* 
  function to perform the transaction for the selected metal
  uses the argument provided to it for right metal
  returns nothing
*/
void manageInventory(float &metalChoiceBal, const std::string &metalName) {
  int innerChoice{};  // inner menu variable declaration

  while (true) {   // while the condition is true (while not breaking out to main menu)

    cout << "\nCurrent " << metalName << " Balance is " << metalChoiceBal << '\n';

    displayMenu2(metalName);     // display the inner menu
    cin >> innerChoice; 
    cout << '\n';

    if (cin.fail()) {         // input validation check for inputting letters
      cin.clear();            // clear fail state
      cin.ignore(1000, '\n'); // discard bad input
      cout << "Invalid input. Please enter a number!\n";
    } else if (innerChoice == DEPOSIT) {   // if user chooses to deposit
      float depoAmt{};     // declare variable of float type for deposit amount
      cout << "Enter deposit amount in kg: ";
      cin >> depoAmt;

      if (cin.fail()) {         // input validation check for inputting letters
        cin.clear();            // clear fail state
        cin.ignore(1000, '\n'); // discard bad input
        cout << "\nInvalid input. Please enter a number.\n";
      } else {
        if (isValidDeposit(depoAmt, metalChoiceBal)) {    // if the deposit is a valid amount
          metalChoiceBal += depoAmt;
          cout << "\nNew" << metalName << " Balance: " << metalChoiceBal << "kg\n";
        } else {
          cout << "Invalid deposit amount!\n";
        }
      }
    }

    else if (innerChoice == WITHDRAW) {    // if the user chooses to withdraw
      float withdrawAmt{};    // declare variable for float type for withdrawal amount
      cout << "Enter amount to withdraw in kg: ";
      cin >> withdrawAmt;

      if (cin.fail()) {         // input validation check for inputting letters
        cin.clear();            // clear fail state
        cin.ignore(1000, '\n'); // discard bad input
        cout << "\nInvalid input. Please enter a number.\n";
      } else {
        if (isValidWithdrawal(withdrawAmt, metalChoiceBal)) {   // if the withdrawal is a valid amount
          metalChoiceBal -= withdrawAmt;
          cout << "\nNew" << metalName << " Balance: " << metalChoiceBal << "kg\n";
        } else {
          cout << "Invalid withdrawal amount!\n";
        }
      }
    }

    else if (innerChoice == MAIN_MENU) {  // if the user chooses to return to menu, break out of the while loop
      break;
    }

    else {      // if the user inputs the wrong number
      cout << "Please enter a number between 1-3!\n";
    }
  }
}