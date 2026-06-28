#ifndef TRANSLATEMANAGER_H
#define TRANSLATEMANAGER_H

#include <QObject>
#include <QTranslator>

#include "ConfigManager.h"

class TranslateManager : public QObject {
  Q_OBJECT
 public:
  static TranslateManager* Instance();

  // 根据语言加载qm文件
  void loadLanguage(ConfigManager::LangType lang);

 private:
  explicit TranslateManager(QObject* parent = nullptr);
  static TranslateManager* m_instance;

  QTranslator m_translator;
};

#define theTranslate TranslateManager::Instance()

#endif  // TRANSLATEMANAGER_H
