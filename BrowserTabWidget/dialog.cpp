#include "dialog.h"

#include <QGridLayout>
#include <QLabel>

#include "browertabwidget.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent) {
  QGridLayout *gLay = new QGridLayout(this);
  tabWidget = new BrowerTabWidget(this);
  tabWidget->setMinimumSize(500, 300);

  tabWidget->addTab(new QLabel("Tab1"), "Tab1");

  connect(tabWidget, SIGNAL(tabAddRequested()), this, SLOT(addNewTab()));
  connect(tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
  connect(tabWidget, SIGNAL(tabMove(int, int)), this, SLOT(moveTab(int, int)));

  gLay->addWidget(tabWidget, 0, 0);
}

Dialog::~Dialog() {}

void Dialog::addNewTab() {
  int count = tabWidget->count();
  QString tabText = QString("Tab%1").arg(count + 1);
  tabWidget->addTab(new QLabel(tabText, this), tabText);
  tabWidget->setCurrentIndex(count);
}

void Dialog::closeTab(int index) {
  if (tabWidget->count() <= 1) {
    this->accept();
  } else {
    tabWidget->widget(index)->deleteLater();
    tabWidget->removeTab(index);
  }
}

void Dialog::moveTab(int from, int to) {}
