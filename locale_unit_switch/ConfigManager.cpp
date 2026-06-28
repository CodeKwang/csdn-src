#include "ConfigManager.h"

#include <QApplication>
#include <QFile>

ConfigManager *ConfigManager::m_instance = nullptr;

ConfigManager *ConfigManager::Instance() {
  if (!m_instance) m_instance = new ConfigManager();
  return m_instance;
}

ConfigManager::ConfigManager(QObject *parent)
    : QObject(parent),
      m_settings(QApplication::applicationDirPath() + "/config.ini",
                 QSettings::IniFormat) {
  // 读取保存的配置，默认中文+公制
  m_lang = (LangType)m_settings.value("Language", LANG_CN_SIMPLE).toInt();
  m_unit = (UnitType)m_settings.value("Unit", UNIT_METRIC).toInt();
}

ConfigManager::LangType ConfigManager::getLanguage() const { return m_lang; }

void ConfigManager::setLanguage(LangType lang) {
  if (m_lang == lang) return;
  m_lang = lang;
  m_settings.setValue("Language", lang);
  emit configChanged();
}

ConfigManager::UnitType ConfigManager::getUnit() const { return m_unit; }

void ConfigManager::setUnit(UnitType unit) {
  if (m_unit == unit) return;
  m_unit = unit;
  m_settings.setValue("Unit", unit);
  emit configChanged();
}

// mm 转 inch
double ConfigManager::metricToImperial(double mm) { return mm / 25.4; }

// inch 转 mm
double ConfigManager::imperialToMetric(double inch) { return inch * 25.4; }
