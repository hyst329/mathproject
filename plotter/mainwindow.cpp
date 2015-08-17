#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QGraphicsView"
#include "QGraphicsScene"
#include "QPen"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->graphicsView);
}

MainWindow::~MainWindow()
{
    delete ui;
}
