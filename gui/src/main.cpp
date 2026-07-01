#include "common.h"
#include <QApplication>

// main function
int main(int argc, char *argv[]) {

  QApplication app(argc, argv); // sets up the Qt application, required once per program

  MainWindow window; // object for the GUI window, replaces Inventory storage being local to main()
  window.show();     // shows the window, GUI equivalent of starting the while loop

  // hands control to Qt's event loop. This is what "waits" for button clicks the way cin >> used to wait for keyboard input
  return app.exec();
}
