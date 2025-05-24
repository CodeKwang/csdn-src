#include "searchdisplaytreewidget.h"
SearchDisplayTreeWidget::SearchDisplayTreeWidget(QWidget* parent)
    : QTreeWidget(parent) {}

SearchDisplayTreeWidget::~SearchDisplayTreeWidget() {}

void SearchDisplayTreeWidget::searchText(const QString& text) {
  QString searchLower = text.toLower();
  for (int i = 0; i < this->topLevelItemCount(); i++) {
    QTreeWidgetItem* item = this->topLevelItem(i);
    bool isFind = false;
    for (int j = 0; j < this->columnCount(); j++) {
      QString textLower = item->text(j).toLower();
      isFind = textLower.contains(searchLower);
      if (isFind) break;
    }
    bool isFindChild = foreachSearchchildItem(searchLower, isFind, item);
    if (isFind || isFindChild) {
      if (isFindChild && !searchLower.isEmpty()) {
        // 是在子项找到的，展开子项
        this->setItemExpanded(item, true);
      } else {
        this->setItemExpanded(item, false);
      }
      this->setItemHidden(item, false);
    } else {
      this->setItemHidden(item, true);
    }
  }
}

bool SearchDisplayTreeWidget::foreachSearchchildItem(
    const QString& searchLower, const bool& isAncestorFind,
    QTreeWidgetItem* parentItem) {
  if (!parentItem) return false;
  bool retFind = false;
  for (int i = 0; i < parentItem->childCount(); i++) {
    QTreeWidgetItem* item = parentItem->child(i);
    bool isFind = false;
    for (int j = 0; j < this->columnCount(); j++) {
      QString textLower = item->text(j).toLower();
      isFind = textLower.contains(searchLower);
      if (isFind) break;
    }
    bool isFindChild =
        foreachSearchchildItem(searchLower, isAncestorFind || isFind, item);
    if (isAncestorFind || isFind || isFindChild) {
      if (isFindChild && !searchLower.isEmpty()) {
        // 是在子项找到的，展开子项
        this->setItemExpanded(item, true);
      } else {
        this->setItemExpanded(item, false);
      }
      this->setItemHidden(item, false);
      if (isFind || isFindChild) retFind = retFind || true;
    } else {
      this->setItemHidden(item, true);
      retFind = retFind || false;
    }
  }
  return retFind;
}
