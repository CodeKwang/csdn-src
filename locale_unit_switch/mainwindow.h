#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  // 刷新文字+单位数值
  void retranslateUi();

 private slots:
  void slotActionChineseSimpleTriggered();
  void slotActionChineseTradTriggered();
  void slotActionEnglishTriggered();
  void slotActionRussianTriggered();
  void slotActionMetricTriggered();
  void slotActionImperialTriggered();

 private:
  Ui::MainWindow *ui;
};

#endif  // MAINWINDOW_H
