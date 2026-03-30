#include "common.hpp"

// to remove the need for adding std:: everytime I want to use cout and cin
using std::cout, std::cin;

// main function
int main() {

  int metalChoice{};   // option variable for the menu
  Inventory storage;   // object for variable of type Inventory

  displayIntro();      // display the introduction and instructions

  while (true) {       // while loop for repeating the program

    displayMenu1();    // display first menu
    cin >> metalChoice;

    if (cin.fail()) {         // input validation check for inputting letters
      cin.clear();            // clear fail state
      cin.ignore(1000, '\n'); // discard bad input
      cout << "\nInvalid input. Please enter a number.\n";
    } else {

      switch (metalChoice) {    // switch statement for selected metal
        case PLATINUM:                         // if user selects platinum
          manageInventory(storage.platinum, "platinum");   // perform inventory transaction for platinum
          break;
        case GOLD:                             // if user selects gold
          manageInventory(storage.gold, "gold");       // perform inventory transaction for gold
          break;
        case DIAMOND:                          // if user selects diamond
          manageInventory(storage.diamond, "diamond");    // perform inventory transaction for diamond
          break;
        case SILVER:                           // if user selects silver
          manageInventory(storage.silver, "silver");     // perform inventory transaction for silver
          break;
        case COPPER:                           // if user selects copper
          manageInventory(storage.copper, "copper");     // perform inventory transaction for copper
          break;
        case BALANCE:                          // if user selects to display the balance
          displayTotalBalance(storage);        // display the total balance
          break;
        case EXIT:                             // if user chooses to exit the program
          {
            cout << "\nThank you for using our services!\n";
            return 0;
          }
        default:                               // default case to protect against wrong numbers
          cout << "\nPlease select a NUMBER between 1-5!\n";
          break;
      }
    }
  }
}