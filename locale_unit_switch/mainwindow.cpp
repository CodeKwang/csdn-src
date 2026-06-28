#include "mainwindow.h"

#include <QAction>

#include "configmanager.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // 监听全局配置变化，自动刷新界面
  connect(theConfig, &ConfigManager::configChanged, this,
          &MainWindow::retranslateUi);

  connect(ui->actionChinese_Simple, SIGNAL(triggered(bool)),
          SLOT(slotActionChineseSimpleTriggered()));
  connect(ui->actionChinese_Trad, SIGNAL(triggered(bool)),
          SLOT(slotActionChineseTradTriggered()));
  connect(ui->actionEnglish, SIGNAL(triggered(bool)),
          SLOT(slotActionEnglishTriggered()));
  connect(ui->actionRussian, SIGNAL(triggered(bool)),
          SLOT(slotActionRussianTriggered()));
  connect(ui->actionMetric, SIGNAL(triggered(bool)),
          SLOT(slotActionMetricTriggered()));
  connect(ui->actionImperial, SIGNAL(triggered(bool)),
          SLOT(slotActionImperialTriggered()));

  retranslateUi();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::retranslateUi() {
  // 刷新所有翻译文本
  ui->menuSetting->setTitle(tr("Setting"));
  ui->actionChinese_Simple->setText(tr("Simplified Chinese"));
  ui->actionChinese_Trad->setText(tr("Traditional Chinese"));
  ui->actionEnglish->setText(tr("English"));
  ui->actionRussian->setText(tr("Russian"));

  ui->actionMetric->setText(tr("Metric(mm)"));
  ui->actionImperial->setText(tr("Imperial(inch)"));
  this->setWindowTitle(tr("Multi-Language & Unit Switch Tool"));

  // 刷新单位数值
  double originalMM = 200.0;
  auto cfg = theConfig;
  if (cfg->getUnit() == ConfigManager::UNIT_METRIC) {
    ui->labelValue->setText(tr("Current Length：%1 mm").arg(originalMM));
  } else {
    double inch = cfg->metricToImperial(originalMM);
    ui->labelValue->setText(tr("Current Length: %1 inch").arg(inch, 0, 'f', 3));
  }
}

void MainWindow::slotActionChineseSimpleTriggered() {
  theConfig->setLanguage(ConfigManager::LANG_CN_SIMPLE);
}

void MainWindow::slotActionChineseTradTriggered() {
  theConfig->setLanguage(ConfigManager::LANG_CN_TRAD);
}

void MainWindow::slotActionEnglishTriggered() {
  theConfig->setLanguage(ConfigManager::LANG_EN);
}

void MainWindow::slotActionRussianTriggered() {
  theConfig->setLanguage(ConfigManager::LANG_RU);
}

void MainWindow::slotActionMetricTriggered() {
  theConfig->setUnit(ConfigManager::UNIT_METRIC);
}

void MainWindow::slotActionImperialTriggered() {
  theConfig->setUnit(ConfigManager::UNIT_IMPERIAL);
}