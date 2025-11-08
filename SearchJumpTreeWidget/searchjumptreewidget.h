#ifndef SEARCHJUMPTREEWIDGET_H
#define SEARCHJUMPTREEWIDGET_H

#include <QDebug>
#include <QLineEdit>
#include <QStyledItemDelegate>
#include <QTreeWidget>
#include <QWidget>

struct SearchData {
  QString contextText;  // 项的内容
  QList<int> jumpPath;  // jump位置，tree的位置
};
Q_DECLARE_METATYPE(SearchData)

class SearchDelegate;
class SearchJumpTreeWidget : public QWidget {
  Q_OBJECT
 public:
  explicit SearchJumpTreeWidget(QWidget *parent = 0);

  void setTreeContext(const QList<SearchData> &dataList);

 signals:
  void signalSearch(const QString &text);
  void signalSelect(const SearchData &itemData);

 private slots:
  void slotSearchEditReturnPressed();
  void slotTreeDoubleClicked(QTreeWidgetItem *item, int column);

 private:
  QLineEdit *searchEdit = nullptr;
  QTreeWidget *treeWidget = nullptr;
  SearchDelegate *searchDelegate = nullptr;
};

// 自定义代理，将搜索文字改变颜色
class SearchDelegate : public QStyledItemDelegate {
  Q_OBJECT

 public:
  SearchDelegate(QObject *parent = nullptr);

  void setSearchText(const QString &text);

  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const override;

 private:
  QString searchText;
  QRegularExpression regExp;
};
#endif  // SEARCHJUMPTREEWIDGET_H
