#pragma execution_character_set("utf-8")
#include "searchjumptreewidget.h"

#include <QHeaderView>
#include <QPainter>
#include <QTextDocument>
#include <QVBoxLayout>

SearchJumpTreeWidget::SearchJumpTreeWidget(QWidget *parent) : QWidget(parent) {
  QVBoxLayout *mainLay = new QVBoxLayout(this);

  searchEdit = new QLineEdit(this);
  searchEdit->setPlaceholderText("请输入搜索内容");
  mainLay->addWidget(searchEdit);
  treeWidget = new QTreeWidget(this);
  mainLay->addWidget(treeWidget);
  treeWidget->setHeaderLabel("内容");
  treeWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
  treeWidget->setEditTriggers(QTreeView::NoEditTriggers);
  treeWidget->header()->setVisible(false);
  searchDelegate = new SearchDelegate(this);
  treeWidget->setItemDelegate(searchDelegate);
  connect(treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)),
          SLOT(slotTreeDoubleClicked(QTreeWidgetItem *, int)));

  connect(searchEdit, SIGNAL(returnPressed()),
          SLOT(slotSearchEditReturnPressed()));
}

void SearchJumpTreeWidget::setTreeContext(const QList<SearchData> &dataList) {
  treeWidget->clear();
  treeWidget->header()->setVisible(false);
  for (const SearchData &data : dataList) {
    QTreeWidgetItem *item = new QTreeWidgetItem(treeWidget);
    item->setText(0, data.contextText);
    QVariant var = QVariant::fromValue(data);
    item->setData(0, Qt::UserRole + 1, var);
    treeWidget->addTopLevelItem(item);
  }
  if (dataList.size() > 0) {
    searchDelegate->setSearchText(searchEdit->text());
    treeWidget->header()->setVisible(true);
  }
}

void SearchJumpTreeWidget::slotSearchEditReturnPressed() {
  QString searchStr = searchEdit->text();
  if (searchStr.isEmpty()) {
    treeWidget->clear();
    treeWidget->header()->setVisible(false);
  } else {
    emit signalSearch(searchStr);
  }
}

void SearchJumpTreeWidget::slotTreeDoubleClicked(QTreeWidgetItem *item,
                                                 int column) {
  if (!item) return;
  QVariant var = item->data(0, Qt::UserRole + 1);
  if (var.canConvert<SearchData>()) {
    SearchData itemData = var.value<SearchData>();
    emit signalSelect(itemData);
  }
}

SearchDelegate::SearchDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

void SearchDelegate::paint(QPainter *painter,
                           const QStyleOptionViewItem &option,
                           const QModelIndex &index) const {
  QStyleOptionViewItem opt = option;
  initStyleOption(&opt, index);

  // 绘制选中背景颜色
  painter->save();
  QString defaultStr("<span style='color: black;'>%1</span>");
  if (opt.state & QStyle::State_Selected) {
    painter->fillRect(opt.rect, QBrush(QColor(15, 130, 220)));
  }
  painter->restore();

  // 整理文字
  QString text = index.data(Qt::DisplayRole).toString();
  const int len = searchText.length();
  QString html("<style>body { white-space: pre; }</style>");
  int pos = 0;
  while ((pos = text.indexOf(regExp, pos)) != -1) {
    QString preText = text.left(pos);
    QString curText = text.mid(pos, len);
    if (!preText.isEmpty()) {
      html += defaultStr.arg(preText);
    }
    if (!curText.isEmpty()) {
      html += QString("<span style='color: red;'>%1</span>").arg(curText);
    }
    text = text.mid(pos + len);
    pos = 0;
  }
  if (!text.isEmpty()) {
    html += defaultStr.arg(text);
  }
  QTextDocument doc;
  doc.setHtml(html);
  //    doc.setTextWidth(opt.rect.width());

  // 绘制文字
  painter->save();
  painter->translate(opt.rect.left(), opt.rect.top());
  QRect clip(0, 0, opt.rect.width(), opt.rect.height());
  doc.drawContents(painter, clip);
  painter->restore();
}

void SearchDelegate::setSearchText(const QString &text) {
  searchText = text;
  regExp =
      QRegularExpression(searchText, QRegularExpression::CaseInsensitiveOption);
}
