#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_actionNew_triggered();

    void on_actionRun_interpreter_triggered();

private:
    Ui::MainWindow *ui;
    bool fileUntitled, fileModified;
    QString fileName;
};

#endif // MAINWINDOW_H
