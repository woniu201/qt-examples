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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNewFile_triggered();

    void on_actionOpenFile_triggered();

    void on_btnButtonsControl_clicked();

    void on_btnItemWidgetsControl_clicked();

    void on_btnContainersControl_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
