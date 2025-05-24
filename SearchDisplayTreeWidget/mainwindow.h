#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class SearchDisplayTreeWidget;
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

 private slots:
  void slotSearchTextChanged(const QString &text);

 private:
  SearchDisplayTreeWidget *treeWidget = nullptr;
};

#endif  // MAINWINDOW_H
