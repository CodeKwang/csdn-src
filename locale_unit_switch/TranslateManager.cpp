#include "TranslateManager.h"

#include <QApplication>

TranslateManager *TranslateManager::m_instance = nullptr;

TranslateManager *TranslateManager::Instance() {
  if (!m_instance) m_instance = new TranslateManager();
  return m_instance;
}

TranslateManager::TranslateManager(QObject *parent) : QObject(parent) {
  // 监听配置里的语言变化，自动重新加载翻译
  connect(theConfig, &ConfigManager::configChanged, this,
          [=]() { loadLanguage(theConfig->getLanguage()); });
}

void TranslateManager::loadLanguage(ConfigManager::LangType lang) {
  qApp->removeTranslator(&m_translator);
  QString path = QApplication::applicationDirPath() + "/lang/";

  switch (lang) {
    case ConfigManager::LANG_CN_SIMPLE:
      m_translator.load(path + "zh_CN.qm");
      break;
    case ConfigManager::LANG_CN_TRAD:
      m_translator.load(path + "zh_TW.qm");
      break;
    case ConfigManager::LANG_EN:
      m_translator.load(path + "en.qm");
      break;
    case ConfigManager::LANG_RU:
      m_translator.load(path + "ru.qm");
      break;
  }

  qApp->installTranslator(&m_translator);
}