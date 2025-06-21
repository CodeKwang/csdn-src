#pragma execution_character_set("utf-8")
#include "mainwindow.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>

#include "secondarycombobox.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  QWidget *wid = new QWidget(parent);
  QVBoxLayout *vLay = new QVBoxLayout(wid);
  QHBoxLayout *hLay = new QHBoxLayout;

  QLabel *label = new QLabel("区号", this);
  hLay->addWidget(label, Qt::AlignLeft);
  SecondaryComboBox *box = new SecondaryComboBox(wid);
  hLay->addWidget(box, Qt::AlignLeft);

  vLay->addLayout(hLay);
  QLabel *infoLabel = new QLabel(wid);
  vLay->addWidget(infoLabel, Qt::AlignCenter);

  QList<QPair<QString, QString>> firstList;
  QList<QPair<QString, QString>> list;
  QList<QList<QPair<QString, QString>>> secondList;

  list.clear();
  firstList.push_back(QPair<QString, QString>("北京", "010"));
  secondList.push_back(list);

  list.clear();
  list.push_back(QPair<QString, QString>("广州", "020"));
  list.push_back(QPair<QString, QString>("深圳", "0755"));
  firstList.push_back(QPair<QString, QString>("广东", ""));
  secondList.push_back(list);

  list.clear();
  firstList.push_back(QPair<QString, QString>("上海", "021"));
  secondList.push_back(list);

  box->addLists(firstList, secondList);
  connect(box, &SecondaryComboBox::currentDataChange, [=]() {
    QString curText = box->currentText();
    QString curData = box->currentData();
    infoLabel->setText(curText + " " + curData);
  });

  box->setCurrentData("010");

  setCentralWidget(wid);
}

MainWindow::~MainWindow() {}
