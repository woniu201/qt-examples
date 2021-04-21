#ifndef SQLDIALOG_H
#define SQLDIALOG_H

#include <QDialog>

namespace Ui {
class SQLDialog;
}

class SQLDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SQLDialog(QWidget *parent = nullptr);
    ~SQLDialog();

private:
    Ui::SQLDialog *ui;
};

#endif // SQLDIALOG_H
