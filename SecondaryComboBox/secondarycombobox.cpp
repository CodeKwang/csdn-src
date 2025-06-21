#include "secondarycombobox.h"

#include <QVBoxLayout>

const char propertyStr[5] = "data";

SecondaryComboBox::SecondaryComboBox(QWidget *parent) : QWidget(parent) {
  QVBoxLayout *lay = new QVBoxLayout(this);
  lay->setMargin(0);
  toolBtn = new QToolButton(this);
  toolMenu = new QMenu(this);
  toolBtn->setMinimumSize(100, 30);
  toolBtn->setPopupMode(QToolButton::MenuButtonPopup);
  toolBtn->setMenu(toolMenu);
  lay->addWidget(toolBtn);
}

SecondaryComboBox::~SecondaryComboBox() {}

QString SecondaryComboBox::currentData() const {
  QString retStr;
  QVariant var = toolBtn->property(propertyStr);
  if (var.canConvert<UserData>()) {
    UserData uData = var.value<UserData>();
    retStr = uData.dataStr;
  }
  return retStr;
}

QString SecondaryComboBox::currentText() const { return toolBtn->text(); }

void SecondaryComboBox::setCurrentData(const QString &data) {
  bool isFind = false;
  UserData newData;
  for (int i = 0; i < userDataList.size(); i++) {
    UserData uData = userDataList.at(i);
    if (uData.dataStr == data) {
      isFind = true;
      newData = uData;
      break;
    }
  }
  QVariant var = toolBtn->property(propertyStr);
  if (!isFind) {
    if (userDataList.size() == 0) return;
    newData = userDataList.at(0);
  }
  if (var.canConvert<UserData>()) {
    UserData curData = var.value<UserData>();
    if (curData.dataStr != newData.dataStr) {
      toolBtn->setText(newData.textStr);
      QVariant var = QVariant::fromValue(newData);
      toolBtn->setProperty(propertyStr, var);
      emit currentDataChange();
    }
  } else {
    toolBtn->setText(newData.textStr);
    QVariant var = QVariant::fromValue(newData);
    toolBtn->setProperty(propertyStr, var);
    emit currentDataChange();
  }
}

void SecondaryComboBox::addLists(
    const QList<QPair<QString, QString>> &firstList,
    const QList<QList<QPair<QString, QString>>> &secondList) {
  if (firstList.size() != secondList.size()) return;
  QString firstText;
  UserData firstUseData;
  bool isFirst = true;
  for (int i = 0; i < firstList.size(); i++) {
    const QPair<QString, QString> &pair = firstList.at(i);
    const QList<QPair<QString, QString>> &list = secondList.at(i);
    if (list.size() == 0) {
      QAction *act = new QAction(pair.first, this);
      UserData uData;
      uData.textStr = pair.first;
      uData.dataStr = pair.second;
      uData.act = act;
      QVariant var = QVariant::fromValue(uData);
      act->setProperty(propertyStr, var);
      userDataList.push_back(uData);
      toolMenu->addAction(act);
      if (isFirst) {
        firstText = pair.first;
        firstUseData = uData;
        isFirst = false;
      }
      connect(act, &QAction::triggered, [=]() {
        bool isChange = true;
        QVariant var = toolBtn->property(propertyStr);
        if (var.canConvert<UserData>()) {
          UserData uData = var.value<UserData>();
          if (uData.act == act) {
            isChange = false;
          }
        }
        if (isChange) {
          toolBtn->setText(act->text());
          toolBtn->setProperty(propertyStr, act->property(propertyStr));
          emit currentDataChange();
        }
      });
    } else {
      QMenu *menu = new QMenu(pair.first, this);
      for (int j = 0; j < list.size(); j++) {
        QPair<QString, QString> pair = list.at(j);
        QAction *act = new QAction(pair.first, this);
        UserData uData;
        uData.textStr = pair.first;
        uData.dataStr = pair.second;
        uData.act = act;
        QVariant var = QVariant::fromValue(uData);
        act->setProperty(propertyStr, var);
        userDataList.push_back(uData);
        menu->addAction(act);
        if (isFirst) {
          firstText = pair.first;
          firstUseData = uData;
          isFirst = false;
        }
        connect(act, &QAction::triggered, [=]() {
          bool isChange = true;
          QVariant var = toolBtn->property(propertyStr);
          if (var.canConvert<UserData>()) {
            UserData uData = var.value<UserData>();
            if (uData.act == act) {
              isChange = false;
            }
          }
          if (isChange) {
            toolBtn->setText(act->text());
            toolBtn->setProperty(propertyStr, act->property(propertyStr));
            emit currentDataChange();
          }
        });
      }
      toolMenu->addMenu(menu);
    }
  }
}
