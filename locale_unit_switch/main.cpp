#include <QApplication>

#include "ConfigManager.h"
#include "TranslateManager.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  theTranslate->loadLanguage(theConfig->getLanguage());
  MainWindow w;
  w.show();
  return QApplication::exec();
}
