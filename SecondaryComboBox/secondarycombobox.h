#ifndef SECONDARYCOMBOBOX_H
#define SECONDARYCOMBOBOX_H

#include <QMenu>
#include <QToolButton>
#include <QWidget>

struct UserData {
  QString textStr;
  QString dataStr;
  QAction *act = nullptr;
};
Q_DECLARE_METATYPE(UserData)

/** 需求：二级选项框，一级选项有子项就没有选项功能，没有子项就有功能;
 *
 */
class SecondaryComboBox : public QWidget {
  Q_OBJECT
 public:
  explicit SecondaryComboBox(QWidget *parent = 0);
  ~SecondaryComboBox();

  QString currentData() const;
  QString currentText() const;

  void setCurrentData(const QString &data);

  // 一次加入全部数据
  void addLists(const QList<QPair<QString, QString>> &firstList,
                const QList<QList<QPair<QString, QString>>> &secondList);

 signals:
  void currentDataChange();

 private:
  QToolButton *toolBtn = nullptr;
  QMenu *toolMenu = nullptr;
  QList<UserData> userDataList;
};

#endif  // SECONDARYCOMBOBOX_H
