#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "hemsyntaxhighlighter.h"

#include <QMainWindow>
#include <QProcess>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void interpreterStarted();
    void interpreterStopped(int exitcode);
    void interpreterStdout();
    void interpreterStderr();
    void interpreterCommand(QString cmd);
    void interpreterStateChanged(QProcess::ProcessState ps);

    void interpreterFileStarted();
    void interpreterFileStopped(int exitcode);
    void interpreterFileStdout();
    void interpreterFileStderr();

    void on_actionNew_triggered();
    void on_actionRun_interpreter_triggered();
    void on_actionStop_interpreter_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_As_triggered();
    void on_actionSave_triggered();

    void on_textEditFile_textChanged();

private:
    Ui::MainWindow *ui;
    bool fileUntitled = 1, fileModified = 0;
    QString fileName = "Untitled";
    QProcess *interpreterProcess;
    QProcess *interpreterFileProcess;
    HEMSyntaxHighlighter *highlighter;
};

#endif // MAINWINDOW_H
