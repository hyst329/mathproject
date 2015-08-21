#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // status bar labels etc.
    ui->statusbar->addPermanentWidget(ui->labelInterpreterState);

    //ui->plainTextEditCommand->setPrompt(""); // the prompt is provided by the interpreter
    ui->plainTextEditCommand->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
    ui->plainTextEditOutput->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
    ui->textEditFile->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));

    highlighter = new HEMSyntaxHighlighter(ui->textEditFile->document());

    interpreterProcess = new QProcess(this);
    interpreterFileProcess = new QProcess(this);
    connect(interpreterProcess, SIGNAL(started()), SLOT(interpreterStarted()));
    connect(interpreterProcess, SIGNAL(finished(int)), SLOT(interpreterStopped(int)));
    connect(interpreterProcess, SIGNAL(readyReadStandardOutput()), SLOT(interpreterStdout()));
    connect(interpreterProcess, SIGNAL(readyReadStandardError()), SLOT(interpreterStderr()));
    connect(interpreterProcess, SIGNAL(stateChanged(QProcess::ProcessState)), SLOT(interpreterStateChanged(QProcess::ProcessState)));
    connect(ui->plainTextEditCommand, SIGNAL(command(QString)), SLOT(interpreterCommand(QString)));

    connect(interpreterFileProcess, SIGNAL(started()), SLOT(interpreterFileStarted()));
    connect(interpreterFileProcess, SIGNAL(finished(int)), SLOT(interpreterFileStopped(int)));
    connect(interpreterFileProcess, SIGNAL(readyReadStandardOutput()), SLOT(interpreterFileStdout()));
    connect(interpreterFileProcess, SIGNAL(readyReadStandardError()), SLOT(interpreterFileStderr()));
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
    ui->listWidgetHistory->addItem(cmd);
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

void MainWindow::interpreterFileStarted()
{
    ui->actionRun_interpreter->setEnabled(0);
    ui->actionStop_interpreter->setEnabled(1);
    ui->textEditFile->setReadOnly(1);
    ui->plainTextEditOutput->clear();
}

void MainWindow::interpreterFileStopped(int exitcode)
{
    ui->actionRun_interpreter->setEnabled(1);
    ui->actionStop_interpreter->setEnabled(0);
    ui->textEditFile->setReadOnly(0);
    ui->plainTextEditOutput->appendHtml(tr("<b>Interpreter finished with code %1</b>").arg(exitcode));
}

void MainWindow::interpreterFileStdout()
{
    QString out = interpreterFileProcess->readAllStandardOutput();
    ui->plainTextEditOutput->appendHtml(tr("%1<br>").arg(out));
}

void MainWindow::interpreterFileStderr()
{
    QString out = interpreterFileProcess->readAllStandardError();
    ui->plainTextEditOutput->appendHtml(tr("<font color=\"#FF0000\">%1</font><br>").arg(out));
}

void MainWindow::on_actionNew_triggered()
{
    ui->tabWidget->setCurrentIndex(1);
    if(fileModified)
    {
        int res = QMessageBox::question(this, tr("Unsaved file"), tr("File is modified but unsaved. Save it?"));
        if(res == QMessageBox::Yes)
        {
            QString fn = QFileDialog::getSaveFileName(this, tr("Save script file"),
                                                      tr(""), "Script files (*.hem)");
            QFile f(fn);
            if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QMessageBox::critical(this, tr("Error"), tr("Cannot save to %1").arg(fn));
                return;
            }
            QTextStream s(&f);
            s << ui->textEditFile->toPlainText() << flush;
            f.close();
        }
    }
    fileModified = 1;
    fileUntitled = 1;
    fileName = "Untitled";
    ui->textEditFile->clear();
}

void MainWindow::on_actionRun_interpreter_triggered()
{
#ifdef Q_OS_WIN32
    QString interpreterPath = "interpreter.exe";
#else
#ifdef Q_OS_OSX
    QString interpreterPath = "./interpreter.app/Contents/MacOS/interpreter";
#else
    QString interpreterPath = "./interpreter";
#endif
    switch (ui->tabWidget->currentIndex()) {
    case 0: // Command Window
        interpreterProcess->start("interpreter -i");
        if(!interpreterProcess->waitForStarted(5000))
            QMessageBox::critical(this, tr("Error"),
                                  tr("Interpreter cannot be started because of the following error:\n %1")
                                  .arg(interpreterProcess->error()));
        if(!interpreterProcess->waitForReadyRead(6000))
            QMessageBox::critical(this, tr("Error"),
                                  tr("Interpreter cannot read because of the following error:\n %1")
                                  .arg(interpreterProcess->error()));
        break;
    case 1: // File Editor
        on_actionSave_triggered();
        interpreterFileProcess->start("interpreter", {fileName});
        if(!interpreterFileProcess->waitForStarted(5000))
            QMessageBox::critical(this, tr("Error"),
                                  tr("Interpreter cannot be started because of the following error:\n %1")
                                  .arg(interpreterFileProcess->error()));
        break;
    }
}

void MainWindow::on_actionStop_interpreter_triggered()
{
    switch (ui->tabWidget->currentIndex()) {
    case 0: // Command Window
        interpreterProcess->write("exit(1);\n");
        if(!interpreterProcess->waitForFinished(5000)) {
            QMessageBox::critical(this, tr("Error"),
                                  tr("Interpreter did not finished in time. Terminating..."));
            interpreterProcess->kill();
        }
        break;
    case 1: // File Editor
        if(!interpreterFileProcess->waitForFinished(5000)) {
            QMessageBox::critical(this, tr("Error"),
                                  tr("Interpreter did not finished in time. Terminating..."));
            interpreterFileProcess->kill();
        }
        break;
    }
}

void MainWindow::on_actionOpen_triggered()
{
    ui->tabWidget->setCurrentIndex(1);
    if(fileModified)
    {
        int res = QMessageBox::question(this, tr("Unsaved file"), tr("File is modified but unsaved. Save it?"));
        if(res == QMessageBox::Yes)
        {
            QString fn = QFileDialog::getSaveFileName(this, tr("Save script file"),
                                                      tr(""), tr("Script files (*.hem)"));
            QFile f(fn);
            if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QMessageBox::critical(this, tr("Error"), tr("Cannot save to %1").arg(fn));
                return;
            }
            QTextStream s(&f);
            s << ui->textEditFile->toPlainText() << flush;
            f.close();
        }
    }
    ui->textEditFile->clear();
    QString fn = QFileDialog::getOpenFileName(this, tr("Open script file"), tr(""), tr("Script files (*.hem)"));
    if(fn.isNull()) return;
    QFile f(fn);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, tr("Error"), tr("Cannot open %1").arg(fn));
        return;
    }
    QTextStream s(&f);
    ui->textEditFile->setText(s.readAll());
    f.close();
    fileModified = 0;
    fileName = fn;
    fileUntitled = 0;
}

void MainWindow::on_actionSave_As_triggered()
{
    QString fn = QFileDialog::getSaveFileName(this, tr("Save script file"),
                                              tr(""), tr("Script files (*.hem)"));
    if(fn.isNull()) return;
    QFile f(fn);
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, tr("Error"), tr("Cannot save to %1").arg(fn));
        return;
    }
    QTextStream s(&f);
    s << ui->textEditFile->toPlainText() << flush;
    f.close();
    fileModified = 0;
    fileName = fn;
    fileUntitled = 0;
}

void MainWindow::on_actionSave_triggered()
{
    if(fileUntitled) on_actionSave_As_triggered();
    if(!fileModified) return;
    QFile f(fileName);
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, tr("Error"), tr("Cannot save to %1").arg(fileName));
        return;
    }
    QTextStream s(&f);
    s << ui->textEditFile->toPlainText() << flush;
    f.close();
    fileModified = 0;
}

void MainWindow::on_textEditFile_textChanged()
{
    fileModified = 1;
}
