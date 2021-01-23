#ifndef BUTTONSCONTROLWINDOW_H
#define BUTTONSCONTROLWINDOW_H

#include <QMainWindow>

namespace Ui {
class ButtonsControlWindow;
}

class ButtonsControlWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ButtonsControlWindow(QWidget *parent = nullptr);
    ~ButtonsControlWindow();

private slots:
    void on_pushButton1_clicked();

    void on_toolButton1_clicked();

    void on_testBtn1_clicked();

    void on_testBtn2_clicked();

    void on_testBtn3_clicked();

    void on_buttonBox_accepted();

private:
    Ui::ButtonsControlWindow *ui;
};

#endif // BUTTONSCONTROLWINDOW_H
