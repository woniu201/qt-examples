#include "MapDialog.h"
#include "ui_MapDialog.h"
#include <QMessageBox>
#include <QKeyEvent>

MapDialog::MapDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapDialog)
{
    ui->setupUi(this);
    //取消窗口上带的问号
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

//    view = new QWebEngineView;
//    view->load(QUrl("http://www.baidu.com/"));
//    view->show();

    //ui->webWidget->load(QUrl("http://www.baidu.com/"));
    ui->webWidget->load(QUrl("file:///E:/project/toec/DBLocation/Debug/gmap3.html"));

}

MapDialog::~MapDialog()
{
    delete ui;
}

/**
 * @brief 检测按键
 */
int w = 0;
int h = 0;
int ax = 0;
int ay = 0;
QSize webWidgetSize ;
void MapDialog::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_F5)
    {
        //QMessageBox::information(this, "", "");
        if(!ui->webWidget->isFullScreen())
        {
            ui->webWidget->size();
            w = ui->webWidget->width();
            h = ui->webWidget->height();
            ax = ui->webWidget->geometry().x();
            ay = ui->webWidget->geometry().y();
            ui->webWidget->setWindowFlags(Qt::Window);
            ui->webWidget->showFullScreen();
        }
        else
        {
            ui->webWidget->setWindowFlags(Qt::SubWindow);
            ui->webWidget->resize(w, h);
            ui->webWidget->move(ax, ay);
            ui->webWidget->showNormal();
        }
        return;
    }

    QWidget::keyPressEvent(ev);
}
