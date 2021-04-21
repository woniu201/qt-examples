#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>
#include <QLabel>
#include "ButtonsControlWindow.h"
#include "ItemWidgetsControlDialog.h"
#include "ContainersControlDialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//状态栏======================================================最多一个
    QStatusBar * stBar = statusBar();
    //设置到窗口
    setStatusBar(stBar);

    //放标签空间
    QLabel* label1 = new QLabel("码农code之路", this);
    stBar->addWidget(label1);

    //右侧提示信息
    QLabel* label2 = new QLabel("Qt控件样例!", this);
    stBar->addPermanentWidget(label2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNewFile_triggered()
{
    QMessageBox::information(this, "温馨提示", "这是一个文件新建操作！");
}

void MainWindow::on_actionOpenFile_triggered()
{
    QMessageBox::information(this, "温馨提示", "这是一个文件打开操作");
}

/**
 * @brief 启动按钮控件样例窗口
 */
void MainWindow::on_btnButtonsControl_clicked()
{
    ButtonsControlWindow* buttonsControlWindow = new ButtonsControlWindow;
    buttonsControlWindow->show();
}

/**
 * @brief 启动Item Widgets窗口
 */
void MainWindow::on_btnItemWidgetsControl_clicked()
{
    ItemWidgetsDialog* itemWidgetsDialog = new ItemWidgetsDialog;
    itemWidgetsDialog->show();
}

/**
 * @brief 启动Containers 控件窗口
 */
void MainWindow::on_btnContainersControl_clicked()
{
    ContainersControlDialog* containersControlDialog = new ContainersControlDialog;
    containersControlDialog->show();
}
