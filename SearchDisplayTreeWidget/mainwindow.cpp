#pragma execution_character_set("utf-8")
#include "mainwindow.h"

#include <QLineEdit>
#include <QVBoxLayout>

#include "searchdisplaytreewidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  resize(300, 350);
  QWidget *widget = new QWidget(this);
  setCentralWidget(widget);

  QVBoxLayout *vLay = new QVBoxLayout(widget);
  QLineEdit *searchLineEdit = new QLineEdit(widget);
  connect(searchLineEdit, SIGNAL(textChanged(QString)), this,
          SLOT(slotSearchTextChanged(QString)));
  vLay->addWidget(searchLineEdit);

  treeWidget = new SearchDisplayTreeWidget(widget);
  vLay->addWidget(treeWidget);
  treeWidget->setHeaderHidden(true);
  treeWidget->setColumnCount(2);

  QTreeWidgetItem *continentItem =
      new QTreeWidgetItem(QStringList() << QString("亚洲"));
  treeWidget->addTopLevelItem(continentItem);
  QTreeWidgetItem *countryItem =
      new QTreeWidgetItem(QStringList() << QString("中国"));
  continentItem->addChild(countryItem);
  QTreeWidgetItem *cityItem =
      new QTreeWidgetItem(QStringList() << QString("北京") << QString("海淀"));
  countryItem->addChild(cityItem);
  cityItem =
      new QTreeWidgetItem(QStringList() << QString("广州") << QString("天河"));
  countryItem->addChild(cityItem);
  cityItem =
      new QTreeWidgetItem(QStringList() << QString("深圳") << QString("福田"));
  countryItem->addChild(cityItem);
  countryItem = new QTreeWidgetItem(QStringList() << QString("日本"));
  continentItem->addChild(countryItem);
  cityItem = new QTreeWidgetItem(QStringList() << QString("东京"));
  countryItem->addChild(cityItem);

  continentItem = new QTreeWidgetItem(QStringList() << QString("北美洲"));
  treeWidget->addTopLevelItem(continentItem);
  countryItem = new QTreeWidgetItem(QStringList() << QString("美国"));
  continentItem->addChild(countryItem);
  cityItem = new QTreeWidgetItem(QStringList() << QString("纽约"));
  countryItem->addChild(cityItem);

  continentItem = new QTreeWidgetItem(QStringList() << QString("南美洲"));
  treeWidget->addTopLevelItem(continentItem);
  countryItem = new QTreeWidgetItem(QStringList() << QString("阿根廷"));
  continentItem->addChild(countryItem);

  continentItem = new QTreeWidgetItem(QStringList() << QString("欧洲"));
  treeWidget->addTopLevelItem(continentItem);
  countryItem = new QTreeWidgetItem(QStringList() << QString("法国"));
  continentItem->addChild(countryItem);
  countryItem = new QTreeWidgetItem(QStringList() << QString("德国"));
  continentItem->addChild(countryItem);

  continentItem = new QTreeWidgetItem(QStringList() << QString("非洲"));
  treeWidget->addTopLevelItem(continentItem);
  countryItem = new QTreeWidgetItem(QStringList() << QString("南非"));
  continentItem->addChild(countryItem);

  continentItem = new QTreeWidgetItem(QStringList() << QString("大洋洲"));
  treeWidget->addTopLevelItem(continentItem);
  countryItem = new QTreeWidgetItem(QStringList() << QString("新西兰"));
  continentItem->addChild(countryItem);

  continentItem = new QTreeWidgetItem(QStringList() << QString("南极洲"));
  treeWidget->addTopLevelItem(continentItem);
}

MainWindow::~MainWindow() {}

void MainWindow::slotSearchTextChanged(const QString &text) {
  if (treeWidget) treeWidget->searchText(text);
}
