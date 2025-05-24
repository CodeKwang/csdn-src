#ifndef SEARCHDISPLAYTREEWIDGET_H
#define SEARCHDISPLAYTREEWIDGET_H

#include <QLineEdit>
#include <QTreeWidget>

class SearchDisplayTreeWidget : public QTreeWidget {
 public:
  SearchDisplayTreeWidget(QWidget *parent = 0);
  ~SearchDisplayTreeWidget();

  void searchText(const QString &text);

 private:
  /**
   * @brief foreachSearchchildItem
   * @param searchLower  搜索字符串
   * @param isAncestorFind 父项或祖先项是否有搜索字符串，有的话子项就不能隐藏
   * @param parentItem 父项目
   * @return 所有是否有搜索到字符串
   */
  bool foreachSearchchildItem(const QString &searchLower,
                              const bool &isAncestorFind,
                              QTreeWidgetItem *parentItem);
};

#endif  // SEARCHDISPLAYTREEWIDGET_H
