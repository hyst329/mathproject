#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // status bar labels etc.
    ui->statusbar->addPermanentWidget(ui->labelInterpreterState);

    ui->actionNew->setIcon(QApplication::style()->standardIcon(QStyle::SP_FileIcon));
    ui->actionOpen->setIcon(QApplication::style()->standardIcon(QStyle::SP_DirOpenIcon));
    ui->actionSave->setIcon(QApplication::style()->standardIcon(QStyle::SP_DriveFDIcon));
    ui->actionRun_interpreter->setIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPlay));
    ui->actionStop_interpreter->setIcon(QApplication::style()->standardIcon(QStyle::SP_MediaStop));

    //ui->plainTextEditCommand->setPrompt(""); // the prompt is provided by the interpreter
    ui->plainTextEditCommand->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));

    interpreterProcess = new QProcess(this);
    connect(interpreterProcess, SIGNAL(started()), SLOT(interpreterStarted()));
    connect(interpreterProcess, SIGNAL(finished(int)), SLOT(interpreterStopped(int)));
    connect(interpreterProcess, SIGNAL(readyReadStandardOutput()), SLOT(interpreterStdout()));
    connect(interpreterProcess, SIGNAL(readyReadStandardError()), SLOT(interpreterStderr()));
    connect(interpreterProcess, SIGNAL(stateChanged(QProcess::ProcessState)), SLOT(interpreterStateChanged(QProcess::ProcessState)));
    connect(ui->plainTextEditCommand, SIGNAL(command(QString)), SLOT(interpreterCommand(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::interpreterStarted()
{
    ui->actionRun_interpreter->setEnabled(0);
    ui->actionStop_interpreter->setEnabled(1);
    ui->plainTextEditCommand->setReadOnly(0);
    ui->plainTextEditCommand->clear();
}

void MainWindow::interpreterStopped(int exitcode)
{
    ui->actionRun_interpreter->setEnabled(1);
    ui->actionStop_interpreter->setEnabled(0);
    ui->plainTextEditCommand->setReadOnly(1);
    QMessageBox::information(this, tr("Interpreter finished"), tr("Interpreter finished with code %1").arg(exitcode));
}

void MainWindow::interpreterStdout()
{
    ui->plainTextEditCommand->result(interpreterProcess->readAllStandardOutput());
}

void MainWindow::interpreterStderr()
{
    ui->plainTextEditCommand->result(interpreterProcess->readAllStandardError());
}

void MainWindow::interpreterCommand(QString cmd)
{
    int b = interpreterProcess->write(cmd.toLatin1());
    interpreterProcess->write("\r\n"); // simulate enter
    interpreterProcess->waitForBytesWritten(3000);
    ui->plainTextEditCommand->append(QString("%1 bytes written!").arg(b));
    if(!interpreterProcess->waitForReadyRead(5000)) ui->plainTextEditCommand->result("No output...");
}

void MainWindow::interpreterStateChanged(QProcess::ProcessState ps)
{
    QString state = tr("No information");
    switch (ps) {
    case QProcess::NotRunning:
        state = tr("Not running");
        break;
    case QProcess::Starting:
        state = tr("Starting");
        break;
    case QProcess::Running:
        state = tr("Running");
        break;
    default:
        break;
    }
    ui->labelInterpreterState->setText(tr("Interpreter: %1").arg(state));
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
    interpreterProcess->start("interpreter.exe -i");
    if(!interpreterProcess->waitForStarted(5000))
        QMessageBox::critical(this, tr("Error"),
                              tr("Interpreter cannot be started because of the following error:\n %1")
                              .arg(interpreterProcess->error()));
    if(!interpreterProcess->waitForReadyRead(6000))
        QMessageBox::critical(this, tr("Error"),
                              tr("Interpreter cannot read because of the following error:\n %1")
                              .arg(interpreterProcess->error()));
}

void MainWindow::on_actionStop_interpreter_triggered()
{
    interpreterProcess->write("exit(1);\n");
    if(!interpreterProcess->waitForFinished(5000)) {
        QMessageBox::critical(this, tr("Error"),
                              tr("Interpreter did not finished in time. Terminating..."));
        interpreterProcess->kill();
    }
}
