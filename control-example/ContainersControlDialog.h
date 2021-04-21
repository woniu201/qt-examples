#ifndef CONTAINERSCONTROLDIALOG_H
#define CONTAINERSCONTROLDIALOG_H

#include <QDialog>

namespace Ui {
class ContainersControlDialog;
}

class ContainersControlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ContainersControlDialog(QWidget *parent = nullptr);
    ~ContainersControlDialog();

private:
    Ui::ContainersControlDialog *ui;
};

#endif // CONTAINERSCONTROLDIALOG_H
