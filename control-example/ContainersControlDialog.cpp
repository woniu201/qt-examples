#include "ContainersControlDialog.h"
#include "ui_ContainersControlDialog.h"
#include <QWidget>


ContainersControlDialog::ContainersControlDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContainersControlDialog)
{
    ui->setupUi(this);

    //取消窗口上带的问号
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    this->setWindowTitle("Containers");

//Scroll Area 控件
    ui->scrollAreaWidgetContents1->setMinimumSize(350, 250);

}

ContainersControlDialog::~ContainersControlDialog()
{
    delete ui;
}
