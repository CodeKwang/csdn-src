#ifndef BROWERTABWIDGET_H
#define BROWERTABWIDGET_H

#include <QProxyStyle>
#include <QTabWidget>

class BrowerTabStyle : public QProxyStyle {
  Q_OBJECT
 public:
  explicit BrowerTabStyle(QObject *parent = nullptr);

  virtual QRect subElementRect(SubElement subElement,
                               const QStyleOption *option,
                               const QWidget *widget) const override;
};

class BrowerTabWidget : public QTabWidget {
  Q_OBJECT
 public:
  explicit BrowerTabWidget(QWidget *parent = nullptr);

 signals:
  void tabAddRequested();
  void tabMove(int from, int to);

 private slots:
  void addTabButtonClicked(bool checked);
  void moveTab(int from, int to);
};

#endif  // BROWERTABWIDGET_H
