#include "SqlDialog.h"
#include "ui_SqlDialog.h"

SQLDialog::SQLDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SQLDialog)
{
    ui->setupUi(this);
}

SQLDialog::~SQLDialog()
{
    delete ui;
}
