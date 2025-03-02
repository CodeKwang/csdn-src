#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

class BrowerTabWidget;
class Dialog : public QDialog {
  Q_OBJECT

 public:
  Dialog(QWidget *parent = 0);
  ~Dialog();

 private slots:
  void addNewTab();
  void closeTab(int index);
  void moveTab(int from, int to);

 private:
  BrowerTabWidget *tabWidget = nullptr;
};

#endif  // DIALOG_H
