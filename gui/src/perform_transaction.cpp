#include "common.h"
#include <QMessageBox>

/* 
  function to open the inner deposit/withdraw page for the chosen metal
  uses the arguments provided to it for the metal name and which balance
  to point at, same role as the parameters passed into manageInventory()
  in the original perform_transaction.cpp
  returns nothing
*/
void MainWindow::openMetalPage(const QString &metalName, float *balancePtr) {
  currentMetalName = metalName;
  currentBalancePtr = balancePtr;
  amountLineEdit->clear(); // clearing the text (instead of setValue(0))
                           // is what makes the "0.00" placeholder show
                           // up grayed out again
  refreshMetalPageLabel();
  stack->setCurrentWidget(metalPage);
}

/* 
  function to perform the deposit for the currently selected metal
  this is the GUI equivalent of the innerChoice == DEPOSIT branch
  inside the original manageInventory() while loop

  unlike the original, this checks each failure case separately so
  the warning message actually tells the user WHY it was invalid,
  instead of one generic "Invalid deposit amount!" for everything
  returns nothing
*/
void MainWindow::handleDeposit() {
  if (!currentBalancePtr) return; // safety check, shouldn't happen

  QString text = amountLineEdit->text();

  if (text.isEmpty()) {        // input validation check for empty field
    QMessageBox::warning(this, "Invalid Deposit", "Please enter an amount before depositing.");
    return;
  }

  bool ok{};
  float depoAmt = text.toFloat(&ok);

  if (!ok) {        // input validation check for inputting letters/garbage
    QMessageBox::warning(this, "Invalid Deposit", "Please enter a valid number (e.g. 12.5).");
    return;
  }

  if (depoAmt <= 0) {
    QMessageBox::warning(this, "Invalid Deposit", "Deposit amount must be greater than 0.");
    return;
  }

  if (depoAmt + *currentBalancePtr > MAX_LIMIT) {
    float roomLeft = MAX_LIMIT - *currentBalancePtr;
    QMessageBox::warning(this, "Invalid Deposit",
        QString("That would exceed the 100kg limit. You can deposit up to %1kg more.")
            .arg(roomLeft, 0, 'f', 2));
    return;
  }

  // if all checks above pass, the deposit is valid, same calculation
  // as the original isValidDeposit(), just walked through step by step
  *currentBalancePtr += depoAmt;
  refreshMetalPageLabel();
  amountLineEdit->clear();
}

/* 
  function to perform the withdrawal for the currently selected metal
  this is the GUI equivalent of the innerChoice == WITHDRAW branch
  inside the original manageInventory() while loop
  same step-by-step validation approach as handleDeposit() above
  returns nothing
*/
void MainWindow::handleWithdraw() {
  if (!currentBalancePtr) return; // safety check, shouldn't happen

  QString text = amountLineEdit->text();

  if (text.isEmpty()) {        // input validation check for empty field
    QMessageBox::warning(this, "Invalid Withdrawal", "Please enter an amount before withdrawing.");
    return;
  }

  bool ok{};
  float withdrawAmt = text.toFloat(&ok);

  if (!ok) {        // input validation check for inputting letters/garbage
    QMessageBox::warning(this, "Invalid Withdrawal", "Please enter a valid number (e.g. 12.5).");
    return;
  }

  if (withdrawAmt <= 0) {
    QMessageBox::warning(this, "Invalid Withdrawal", "Withdrawal amount must be greater than 0.");
    return;
  }

  if (withdrawAmt > *currentBalancePtr) {
    QMessageBox::warning(this, "Invalid Withdrawal",
        QString("You only have %1kg available to withdraw.")
            .arg(*currentBalancePtr, 0, 'f', 2));
    return;
  }

  // if all checks above pass, the withdrawal is valid, same
  // calculation as the original isValidWithdrawal(), step by step
  *currentBalancePtr -= withdrawAmt;
  refreshMetalPageLabel();
  amountLineEdit->clear();
}

/* 
  function to return to the main menu page
  this is the GUI equivalent of innerChoice == MAIN_MENU breaking out
  of the while loop in the original manageInventory()
  returns nothing
*/
void MainWindow::backToMainMenu() {
  currentBalancePtr = nullptr;
  stack->setCurrentWidget(mainMenuPage);
}