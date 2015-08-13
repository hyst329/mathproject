#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

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
    interpreterProcess = new QProcess(this);
    connect(interpreterProcess, SIGNAL(started()), SLOT(interpreterStarted()));
    connect(interpreterProcess, SIGNAL(finished(int)), SLOT(interpreterFinished(int));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::interpreterStarted()
{
    ui->actionRun_interpreter->setEnabled(0);
    ui->actionStop_interpreter->setEnabled(1);
}

void MainWindow::interpreterStopped(int exitcode)
{
    ui->actionRun_interpreter->setEnabled(1);
    ui->actionStop_interpreter->setEnabled(0);
    QMessageBox::information(this, tr("Interpreter finished"), tr("Interpreter finished with code %1").arg(exitcode));
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
    interpreterProcess->start("interpreter.exe", "-i");
}
