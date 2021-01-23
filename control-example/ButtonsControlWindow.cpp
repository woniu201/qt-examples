#include "ButtonsControlWindow.h"
#include "ui_ButtonsControlWindow.h"
#include <QMessageBox>

ButtonsControlWindow::ButtonsControlWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ButtonsControlWindow)
{
    ui->setupUi(this);

    //设置pushbutton4的样式
    ui->pushButton4->setStyleSheet(QString("QPushButton{border:1px;border-radius:35px;background-color:rgba(0,255,0,255);}")
                                           + "QPushButton:hover{background-color:rgba(0,0,255,255);}"
                                           +"QPushButton:pressed{background-color:rgba(255,0,0,255);}");

    //ToolButton

    ui->toolButton2->setIcon(QIcon(":/images/buttonOk.png"));
    ui->toolButton2->setIconSize(QSize(30, 30));
    ui->toolButton2->setText( QString::fromLocal8Bit("更新设置"));

}

ButtonsControlWindow::~ButtonsControlWindow()
{
    delete ui;
}

void ButtonsControlWindow::on_pushButton1_clicked()
{
    QMessageBox::information(this, QString::fromLocal8Bit("温馨提示"),  QString::fromLocal8Bit("这个一个按钮点击事件！"));
}

void ButtonsControlWindow::on_toolButton1_clicked()
{
    QMessageBox::information(this, QString::fromLocal8Bit("温馨提示"), QString::fromLocal8Bit("这是一个ToolButton点击事件！"));
}

void ButtonsControlWindow::on_testBtn1_clicked()
{
    if(ui->radioButton1->isChecked())
    {
        QMessageBox::information(this, QString::fromLocal8Bit("温馨提示"), ui->radioButton1->text());
    }
    if(ui->radioButton2->isChecked())
    {
        QMessageBox::information(this, QString::fromLocal8Bit("温馨提示"), ui->radioButton2->text());
    }
    if(ui->radioButton3->isChecked())
    {
        QMessageBox::information(this, QString::fromLocal8Bit("温馨提示"), ui->radioButton3->text());
    }
}

void ButtonsControlWindow::on_testBtn2_clicked()
{
    if(ui->radioButton4->isChecked())
    {
        QMessageBox::information(this, QString::fromLocal8Bit("温馨提示"), ui->radioButton4->text());
    }
    if(ui->radioButton5->isChecked())
    {
        QMessageBox::information(this, QString::fromLocal8Bit("温馨提示"), ui->radioButton5->text());
    }
}

void ButtonsControlWindow::on_testBtn3_clicked()
{
    QString str = "";
    if(ui->checkBox1->isChecked())
    {
        str += ui->checkBox1->text();
    }
    if(ui->checkBox2->isChecked())
    {
        str += "; " + ui->checkBox2->text();
    }
    if(ui->checkBox3->isChecked())
    {
        str += "; " + ui->checkBox3->text();
    }
    QMessageBox::information(this, QString::fromLocal8Bit("温馨提示"), str);
}

void ButtonsControlWindow::on_buttonBox_accepted()
{
    QWidget::close();
}
