#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QObject>
#include <QSettings>

class ConfigManager : public QObject {
  Q_OBJECT
 public:
  // 单例
  static ConfigManager* Instance();

  // 语言枚举
  enum LangType {
    LANG_CN_SIMPLE,  // 简体中文
    LANG_CN_TRAD,    // 繁体中文
    LANG_EN,         // 英文
    LANG_RU          // 俄语
  };

  // 单位枚举
  enum UnitType {
    UNIT_METRIC,   // 公制 mm kg
    UNIT_IMPERIAL  // 英制 inch lb
  };

  // 读写语言
  LangType getLanguage() const;
  void setLanguage(LangType lang);

  // 读写单位
  UnitType getUnit() const;
  void setUnit(UnitType unit);

  // 单位换算接口
  double metricToImperial(double mm);
  double imperialToMetric(double inch);

 signals:
  // 配置变更信号，所有UI绑定此信号刷新界面
  void configChanged();

 private:
  explicit ConfigManager(QObject* parent = nullptr);
  static ConfigManager* m_instance;

  LangType m_lang;
  UnitType m_unit;
  QSettings m_settings;  // 持久化到ini
};

#define theConfig ConfigManager::Instance()

#endif  // CONFIGMANAGER_H
