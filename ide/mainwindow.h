#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

    void on_actionNew_triggered();

    void on_actionRun_interpreter_triggered();

    void on_actionStop_interpreter_triggered();

private:
    Ui::MainWindow *ui;
    bool fileUntitled, fileModified;
    QString fileName;
    QProcess *interpreterProcess;
};

#endif // MAINWINDOW_H
