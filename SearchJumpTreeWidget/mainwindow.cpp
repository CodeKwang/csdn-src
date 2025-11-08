#pragma execution_character_set("utf-8")
#include "mainwindow.h"

#include <QVBoxLayout>

#include "searchjumptreewidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  QWidget *widget = new QWidget(this);
  setCentralWidget(widget);

  QVBoxLayout *vLay = new QVBoxLayout(widget);

  contextTreeWidget = new QTreeWidget(widget);
  vLay->addWidget(contextTreeWidget);
  contextTreeWidget->setHeaderHidden(true);
  contextTreeWidget->setColumnCount(1);

  searchTreeWidget = new SearchJumpTreeWidget(widget);
  vLay->addWidget(searchTreeWidget);
  connect(searchTreeWidget, SIGNAL(signalSearch(const QString &)),
          SLOT(slotSearch(QString)));
  connect(searchTreeWidget, SIGNAL(signalSelect(const SearchData &)),
          SLOT(slotSelect(const SearchData &)));

  QTreeWidgetItem *topItem =
      new QTreeWidgetItem(QStringList() << QString("顶级1"));
  contextTreeWidget->addTopLevelItem(topItem);
  QTreeWidgetItem *seniorItem =
      new QTreeWidgetItem(QStringList() << QString("高级1_1"));
  topItem->addChild(seniorItem);
  QTreeWidgetItem *intermediateItem =
      new QTreeWidgetItem(QStringList() << QString("中级1_1_1"));
  seniorItem->addChild(intermediateItem);
  QTreeWidgetItem *juniorItem =
      new QTreeWidgetItem(QStringList() << QString("初级1_1_1_1"));
  intermediateItem->addChild(juniorItem);
  juniorItem = new QTreeWidgetItem(QStringList() << QString("初级1_1_1_2"));
  intermediateItem->addChild(juniorItem);
  intermediateItem = new QTreeWidgetItem(QStringList() << QString("中级1_1_2"));
  seniorItem->addChild(intermediateItem);
  seniorItem = new QTreeWidgetItem(QStringList() << QString("高级1_2"));
  topItem->addChild(seniorItem);

  topItem = new QTreeWidgetItem(QStringList() << QString("顶级2"));
  contextTreeWidget->addTopLevelItem(topItem);
  seniorItem = new QTreeWidgetItem(QStringList() << QString("高级2_1"));
  topItem->addChild(seniorItem);
}

MainWindow::~MainWindow() {}

void MainWindow::slotSearch(const QString &searchText) {
  QList<SearchData> dataList;
  QString sTextLower = searchText.toLower();
  for (int i = 0; i < contextTreeWidget->topLevelItemCount(); i++) {
    QTreeWidgetItem *item = contextTreeWidget->topLevelItem(i);
    QString text = item->text(0);

    QList<int> jumpPath;
    jumpPath.push_back(i);
    if (text.toLower().contains(sTextLower)) {
      SearchData itemData;
      itemData.contextText = text;
      itemData.jumpPath = jumpPath;
      dataList.push_back(itemData);
    }
    foreachSearchItem(searchText, item, dataList, jumpPath);
    jumpPath.pop_back();
  }
  searchTreeWidget->setTreeContext(dataList);
}

void MainWindow::slotSelect(const SearchData &itemData) {
  QList<int> jumpPath = itemData.jumpPath;
  if (jumpPath.size() <= 0) return;
  int row = jumpPath.at(0);
  QTreeWidgetItem *item = contextTreeWidget->topLevelItem(row);
  for (int i = 1; i < jumpPath.size(); i++) {
    row = jumpPath.at(i);
    if (item) {
      item = item->child(row);
    } else {
      item = nullptr;
      break;
    }
  }
  if (item) {
    contextTreeWidget->setCurrentItem(item);
  }
  return;
}

void MainWindow::foreachSearchItem(const QString &searchText,
                                   QTreeWidgetItem *itemParent,
                                   QList<SearchData> &dataList,
                                   QList<int> &jumpPath) {
  if (!itemParent) return;
  QString sTextLower = searchText.toLower();
  for (int i = 0; i < itemParent->childCount(); i++) {
    QTreeWidgetItem *item = itemParent->child(i);
    QString text = item->text(0);

    jumpPath.push_back(i);
    if (text.toLower().contains(sTextLower)) {
      SearchData itemData;
      itemData.contextText = text;
      itemData.jumpPath = jumpPath;
      dataList.push_back(itemData);
    }
    foreachSearchItem(searchText, item, dataList, jumpPath);
    jumpPath.pop_back();
  }
}
