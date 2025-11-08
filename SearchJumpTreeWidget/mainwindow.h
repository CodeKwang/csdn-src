#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "searchjumptreewidget.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

 private slots:
  void slotSearch(const QString &searchText);
  void slotSelect(const SearchData &itemData);

 private:
  // 遍历搜索
  void foreachSearchItem(const QString &searchText, QTreeWidgetItem *itemParent,
                         QList<SearchData> &dataList, QList<int> &jumpPath);

 private:
  QTreeWidget *contextTreeWidget = nullptr;
  SearchJumpTreeWidget *searchTreeWidget = nullptr;
};

#endif  // MAINWINDOW_H
