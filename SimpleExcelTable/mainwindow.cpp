#include "mainwindow.h"

#include <QHeaderView>
#include <QVBoxLayout>

#include "simpleexceltable.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  QWidget *widget = new QWidget(this);
  setCentralWidget(widget);

  resize(450, 300);

  QVBoxLayout *vLay = new QVBoxLayout(widget);

  SimpleExcelTable *table = new SimpleExcelTable(widget);
  vLay->addWidget(table);
  table->horizontalHeader()->setStretchLastSection(true);
  table->setColumnCount(3);
  table->setRowCount(6);
  table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow() {}
