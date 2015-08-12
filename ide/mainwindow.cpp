#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->actionNew->setIcon(QApplication::style()->standardIcon(QStyle::SP_FileIcon));
    ui->actionOpen->setIcon(QApplication::style()->standardIcon(QStyle::SP_DirOpenIcon));
    ui->actionSave->setIcon(QApplication::style()->standardIcon(QStyle::SP_DriveFDIcon));
    ui->actionRun_interpreter->setIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPlay));
    ui->actionStop_interpreter->setIcon(QApplication::style()->standardIcon(QStyle::SP_MediaStop));
}

MainWindow::~MainWindow()
{
    delete ui;
}
