#include "mainwindow.h"

#include <BRepGProp.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <GProp_GProps.hxx>
#include <QDebug>
#include <TopoDS_Shape.hxx>
#include <gp_Pnt.hxx>

#include "ui_mainwindow.h"

void testOCCT() {
  BRepPrimAPI_MakeBox box(10.0, 20.0, 30.0);
  TopoDS_Shape shape = box.Shape();
  GProp_GProps props;
  BRepGProp::VolumeProperties(shape, props);
  double volume = props.Mass();
  qDebug() << "Box volume:" << volume;  // 应输出 6000
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  testOCCT();
}

MainWindow::~MainWindow() { delete ui; }
