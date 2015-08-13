#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QProcess>

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

void MainWindow::on_actionNew_triggered()
{
    ui->tabWidget->setCurrentIndex(1);
    if(fileModified)
    {
        int res = QMessageBox::question(this, tr("Unsaved file"), tr("File is modified but unsaved. Save it?"));
        if(res == QMessageBox::Yes)
        {
            //TODO: Save file
        }
    }
    //TODO: Create new file
}

void MainWindow::on_actionRun_interpreter_triggered()
{
    QProcess p;
}
