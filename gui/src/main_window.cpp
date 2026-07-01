#include "common.h"

/* 
  constructor for MainWindow
  sets up the intro, builds both pages, and starts on the main menu
  this plays the same role as the top portion of the original main()
  before the while loop started (displayIntro() + initial state setup)
*/
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  displayIntro();   // display the introduction / window setup

  stack = new QStackedWidget(this);
  setCentralWidget(stack);

  displayMenu1();   // build the first main menu page
  displayMenu2();   // build the second inner menu page

  stack->addWidget(mainMenuPage); // index 0
  stack->addWidget(metalPage);    // index 1
  stack->setCurrentIndex(0);      // start on the main menu, same as original
}
