#include "common.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QFont>

/* 
  function to set the window title and intro text
  this is the GUI replacement for the old cout intro block
  returns nothing
*/
void MainWindow::displayIntro() {
  setWindowTitle("Ray's Precious Metal Inventory");
  resize(420, 480);
}

/* 
  function to build the first main menu page
  CONTROLS: one button per metal (platinum/gold/diamond/silver/copper),
  a "Display Total Balance" button, and an Exit button
  each metal button click is what used to be picking 1-5 in main.cpp's switch
  returns nothing
*/
void MainWindow::displayMenu1() {
  mainMenuPage = new QWidget;
  QVBoxLayout *layout = new QVBoxLayout(mainMenuPage);

  QLabel *title = new QLabel("Select the precious metal you wish to deposit or withdraw from:");
  title->setWordWrap(true);
  QFont titleFont = title->font();
  titleFont.setBold(true);
  title->setFont(titleFont);
  layout->addWidget(title);

  // one button per metal where each connects to openMetalPage() with a
  // pointer to that metal's balance in storage, same idea as passing
  // storage.platinum by reference into manageInventory() in the original
  QPushButton *platinumBtn = new QPushButton("Platinum");
  QPushButton *goldBtn     = new QPushButton("Gold");
  QPushButton *diamondBtn  = new QPushButton("Diamond");
  QPushButton *silverBtn   = new QPushButton("Silver");
  QPushButton *copperBtn   = new QPushButton("Copper");
  QPushButton *balanceBtn  = new QPushButton("Display Total Balance");
  QPushButton *exitBtn     = new QPushButton("Exit");

  connect(platinumBtn, &QPushButton::clicked, this, [this]() {
    openMetalPage("Platinum", &storage.platinum);
  });
  connect(goldBtn, &QPushButton::clicked, this, [this]() {
    openMetalPage("Gold", &storage.gold);
  });
  connect(diamondBtn, &QPushButton::clicked, this, [this]() {
    openMetalPage("Diamond", &storage.diamond);
  });
  connect(silverBtn, &QPushButton::clicked, this, [this]() {
    openMetalPage("Silver", &storage.silver);
  });
  connect(copperBtn, &QPushButton::clicked, this, [this]() {
    openMetalPage("Copper", &storage.copper);
  });
  connect(balanceBtn, &QPushButton::clicked, this, &MainWindow::showTotalBalance);
  connect(exitBtn, &QPushButton::clicked, this, &QWidget::close);

  layout->addWidget(platinumBtn);
  layout->addWidget(goldBtn);
  layout->addWidget(diamondBtn);
  layout->addWidget(silverBtn);
  layout->addWidget(copperBtn);
  layout->addSpacing(12);
  layout->addWidget(balanceBtn);
  layout->addStretch();
  layout->addWidget(exitBtn);
}

/* 
  function to build the second inner page (deposit/withdraw/back)
  CONTROLS: this single page is reused for every metal, whichever
  button was clicked on menu1 decides which balance this page edits

  the amount field is a QLineEdit with placeholder text "0.00" instead
  of a QDoubleSpinBox. placeholder text shows as grayed-out text that
  is NOT an actual value sitting in the field, so the moment you type,
  it disappears completely instead of getting typed into/around (no
  more "0|.00" turning into "023.00"). a QDoubleValidator is attached
  so letters and other bad characters are rejected as you type, same
  spirit as the cin.fail() checks in the original, just preventing the
  bad input before it ever gets in instead of catching it after
  returns nothing
*/
void MainWindow::displayMenu2() {
  metalPage = new QWidget;
  QVBoxLayout *layout = new QVBoxLayout(metalPage);

  // CONTROLS: shows "Current <metal> Balance is ___", same wording as
  // the original cout line at the top of manageInventory()'s while loop
  metalBalanceLabel = new QLabel;
  QFont labelFont = metalBalanceLabel->font();
  labelFont.setPointSize(labelFont.pointSize() + 2);
  metalBalanceLabel->setFont(labelFont);
  layout->addWidget(metalBalanceLabel);

  // CONTROLS: explains the rules of the system, equivalent in spirit to
  // the original displayIntro() cout block, but shown on the page where
  // it's actually relevant instead of only once at program start
  rulesLabel = new QLabel(
      "Rules: max storage per metal is 100kg. Deposits cannot push the "
      "balance over 100kg. Withdrawals cannot exceed the current balance. "
      "Decimal amounts are allowed (e.g. 12.5). Letters and negative "
      "numbers are not accepted.");
  rulesLabel->setWordWrap(true);
  rulesLabel->setStyleSheet("color: gray; font-size: 11px;");
  layout->addWidget(rulesLabel);

  QLabel *amountLabel = new QLabel("Enter amount in kg:");
  layout->addWidget(amountLabel);

  // CONTROLS: the deposit/withdraw amount, equivalent to depoAmt/withdrawAmt
  amountLineEdit = new QLineEdit;
  amountLineEdit->setPlaceholderText("0.00"); // grayed-out hint text only,
                                               // not a real typed value
  // only allows numbers 0.00 through 9999.99, blocks letters/symbols
  // outright as the user types with same role cin.fail() played before
  QDoubleValidator *amountValidator = new QDoubleValidator(0.0, 9999.99, 2, amountLineEdit);
  amountValidator->setNotation(QDoubleValidator::StandardNotation);
  amountLineEdit->setValidator(amountValidator);
  layout->addWidget(amountLineEdit);

  QHBoxLayout *btnRow = new QHBoxLayout;

  // CONTROLS: equivalent of typing 1 (DEPOSIT) at the inner menu
  QPushButton *depositBtn = new QPushButton("Deposit");
  // CONTROLS: equivalent of typing 2 (WITHDRAW) at the inner menu
  QPushButton *withdrawBtn = new QPushButton("Withdraw");

  connect(depositBtn, &QPushButton::clicked, this, &MainWindow::handleDeposit);
  connect(withdrawBtn, &QPushButton::clicked, this, &MainWindow::handleWithdraw);

  btnRow->addWidget(depositBtn);
  btnRow->addWidget(withdrawBtn);
  layout->addLayout(btnRow);

  layout->addStretch();

  // CONTROLS: equivalent of typing 3 (MAIN_MENU) to break the inner loop
  QPushButton *backBtn = new QPushButton("Main Menu");
  connect(backBtn, &QPushButton::clicked, this, &MainWindow::backToMainMenu);
  layout->addWidget(backBtn);
}

/* 
  function to update the "Current <metal> Balance is ___" label
  called any time the balance changes or a new metal page is opened
  this is the GUI replacement for the cout line at the top of the
  original manageInventory() while loop
  returns nothing
*/
void MainWindow::refreshMetalPageLabel() {
  if (!currentBalancePtr) return;

  metalBalanceLabel->setText(
      QString("Current %1 Balance is %2 kg")
          .arg(currentMetalName)
          .arg(*currentBalancePtr, 0, 'f', 2));
}

/* 
  function to display the total user balance
  GUI replacement for displayTotalBalance() in the original display.cpp
  uses a popup message box instead of printing to console
  returns nothing
*/
void MainWindow::showTotalBalance() {
  QString msg = QString(
      "Platinum: %1 kg\nGold:     %2 kg\nDiamond:  %3 kg\nSilver:   %4 kg\nCopper:   %5 kg")
      .arg(storage.platinum, 0, 'f', 2)
      .arg(storage.gold, 0, 'f', 2)
      .arg(storage.diamond, 0, 'f', 2)
      .arg(storage.silver, 0, 'f', 2)
      .arg(storage.copper, 0, 'f', 2);

  QMessageBox::information(this, "Total Balance", msg);
}