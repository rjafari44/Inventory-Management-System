#pragma once

#include <QMainWindow>
#include <QStackedWidget>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleValidator>

// global variable for max storage amount allowed
inline const float MAX_LIMIT{100};

// struct for the different precious metals
struct Inventory {
  float platinum{}, gold{}, diamond{}, silver{}, copper{};
};

// function declarations for validate.cpp
// these are unchanged from the original console version
bool isValidDeposit(float depoAmt, float currentBalance);
bool isValidWithdrawal(float withdrawAmt, float currentBalance);

/*
  MainWindow is the GUI equivalent of what main.cpp's while loop +
  perform_transaction.cpp's manageInventory() used to do together.

  Qt requires GUI classes that respond to button clicks to inherit from
  QObject (QMainWindow already does this) and use the Q_OBJECT macro,
  which is what enables the "slots" below to be connected to button
  clicks. This is the one structural piece that doesn't have a console
  equivalent.
*/
class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);

private slots:
  // GUI EQUIVALENT OF: user selecting a metal from menu1 in main.cpp
  // this points the inner page at the chosen metal's balance
  void openMetalPage(const QString &metalName, float *balancePtr);

  // GUI EQUIVALENT OF: innerChoice == DEPOSIT branch in manageInventory()
  void handleDeposit();

  // GUI EQUIVALENT OF: innerChoice == WITHDRAW branch in manageInventory()
  void handleWithdraw();

  // GUI EQUIVALENT OF: case BALANCE in main.cpp's switch statement
  void showTotalBalance();

  // GUI EQUIVALENT OF: innerChoice == MAIN_MENU (break out of inner loop)
  void backToMainMenu();

private:
  // these three build the widgets that used to just be cout statements
  // display.cpp function names kept the same on purpose
  void displayIntro();   // sets up window title / intro text
  void displayMenu1();   // builds the main menu page (metal selection)
  void displayMenu2();   // builds the inner deposit/withdraw page

  void refreshMetalPageLabel(); // updates "Current X Balance is ___" label

  Inventory storage; // same struct, same role as in main.cpp

  QStackedWidget *stack;     // swaps between menu1 and menu2 pages
  QWidget *mainMenuPage;     // page 0, equivalent of displayMenu1()
  QWidget *metalPage;        // page 1, equivalent of displayMenu2()

  QLabel *metalBalanceLabel;     // shows "Current <metal> Balance is ___"
  QLabel *rulesLabel;            // explains the system's rules/constraints
  QLineEdit *amountLineEdit;     // replaces "cin >> depoAmt / withdrawAmt"
                                  // uses placeholder text "0.00" instead of
                                  // a real default value, so it's grayed
                                  // out and disappears the moment you type

  QString currentMetalName;  // same role as metalName parameter
  float *currentBalancePtr{nullptr}; // same role as metalChoiceBal reference
};