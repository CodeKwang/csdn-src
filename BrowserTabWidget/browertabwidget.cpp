#include "browertabwidget.h"

#include <QPushButton>
#include <QTabBar>

BrowerTabStyle::BrowerTabStyle(QObject *parent) : QProxyStyle() {
  setParent(parent);
}

QRect BrowerTabStyle::subElementRect(SubElement subElement,
                                     const QStyleOption *option,
                                     const QWidget *widget) const {
  // 修改QTabWidget右上角控件的位置
  if (subElement == QStyle::SE_TabWidgetRightCorner) {
    QRect tabRect =
        QProxyStyle::subElementRect(QStyle::SE_TabWidgetTabBar, option, widget);
    QRect rightCornerRect = QProxyStyle::subElementRect(
        QStyle::SE_TabWidgetRightCorner, option, widget);

    rightCornerRect.setRect(tabRect.left() + tabRect.width() + 4, 3,
                            rightCornerRect.width(), rightCornerRect.height());

    return rightCornerRect;
  }

  return QProxyStyle::subElementRect(subElement, option, widget);
}

BrowerTabWidget::BrowerTabWidget(QWidget *parent) : QTabWidget(parent) {
  setStyle(new BrowerTabStyle(this));
  setTabsClosable(true);  // 网页关闭使能
  setMovable(true);       // 网页移动使能
  QPushButton *addButton = new QPushButton("+", this);
  addButton->setFixedSize(25, 25);
  connect(addButton, SIGNAL(clicked(bool)), this,
          SLOT(addTabButtonClicked(bool)));
  connect(tabBar(), SIGNAL(tabMoved(int, int)), this, SLOT(moveTab(int, int)));
  setCornerWidget(addButton);
}

void BrowerTabWidget::addTabButtonClicked(bool checked) {
  Q_UNUSED(checked)
  emit tabAddRequested();
}

void BrowerTabWidget::moveTab(int from, int to) { emit tabMove(from, to); }
