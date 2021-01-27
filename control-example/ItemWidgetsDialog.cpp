#include "ItemWidgetsDialog.h"
#include "ui_ItemWidgetsDialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QtDebug>
#include <QTime>

ItemWidgetsDialog::ItemWidgetsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItemWidgetsDialog)
{
    ui->setupUi(this);

    //取消窗口上带的问号
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

//*************List Widget***************
    //方法一：
    QIcon icon1(":/images/buttonOk.png");
    ui->listWidget->addItem(new QListWidgetItem(icon1, "开启"));
    QIcon icon2(":/images/buttonClose.png");
    ui->listWidget->addItem(new QListWidgetItem(icon2, "关闭"));
    QIcon icon3(":/images/CheckboxOn.png");
    ui->listWidget->addItem(new QListWidgetItem(icon3, "选择"));
    //方法二
    QIcon icon4(":/images/switchOn.png");
    QListWidgetItem* listItem1 = new QListWidgetItem(icon4, "开关");
    listItem1->setData(Qt::UserRole, 1);
    listItem1->setData(Qt::ToolTipRole, "角色1");
    ui->listWidget->addItem(listItem1);

    //ui->listWidget->addItem(new QListWidgetItem(icon4, "开关"));

    //设置图标大小
    ui->listWidget->setIconSize(QSize(20, 20));

    //连接信号槽
    connect(ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(OnItemDbClicked(QListWidgetItem *)));

//**************Tree Widget****************
    ui->treeWidget->clear();
    QStringList treeHeaders;
    treeHeaders.append("");
    treeHeaders.append("文件名称");
    treeHeaders.append("修改时间");
    //设置头
    ui->treeWidget->setColumnCount(3);
    ui->treeWidget->setHeaderLabels(treeHeaders);
    //可拖拽内容，设置拖拽使能
    ui->treeWidget->setAcceptDrops(true);
    ui->treeWidget->setDragEnabled(true);
    //设置单行居中
    ui->treeWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置列平分
    //ui->treeWidget->header()->setSectionResizeMode(QHeaderView::Stretch);
    //设置列宽
    ui->treeWidget->setColumnWidth(0, ui->treeWidget->width()/7*1);
    ui->treeWidget->setColumnWidth(1, ui->treeWidget->width()/7*3);
    ui->treeWidget->setColumnWidth(2, ui->treeWidget->width()/7*3);


    //连接信号槽
    connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(OnTreeItemDbClicked(QTreeWidgetItem *, int)));

//*************Table Widget*******************
    ui->tableWidget->clear();
    bAddTableDataFished = false;

    //设置头信息
    QStringList tableHeaders;
    tableHeaders.append("序号");
    tableHeaders.append("名字");
    tableHeaders.append("分数");
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(tableHeaders);
    ui->tableWidget->verticalHeader()->setVisible(false);//隐藏垂直头

    //设置列宽
    ui->tableWidget->setColumnWidth(0, ui->tableWidget->width()/7*1);
    ui->tableWidget->setColumnWidth(1, ui->tableWidget->width()/7*3);
    ui->tableWidget->setColumnWidth(2, ui->tableWidget->width()/7*3);

    //其他设置
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);   // 单个选中
    ui->tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);  // 可以选中多个


    //只显示横分割线，不显示竖分割线
   //ui->tableWidget->setShowGrid(false);

    //练级信号槽
    connect(ui->tableWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem *)), this, SLOT(OnItemDoubleClicked(QTableWidgetItem *)));
    connect(ui->tableWidget, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(OnItemChanged(QTableWidgetItem *)));

}

ItemWidgetsDialog::~ItemWidgetsDialog()
{
    delete ui;
}

//************List Widget************
void ItemWidgetsDialog::OnItemDbClicked(QListWidgetItem *item)
{
    QMessageBox::information(this, "温馨提示", item->text());

    QString str;
    int value = item->data(Qt::UserRole).toInt();
    str.sprintf("值为：%d", value);

    QMessageBox::information(this, "温馨提示", str);
}

//切换显示模式
void ItemWidgetsDialog::on_btnChangeViewMode_clicked()
{
    if(ui->listWidget->viewMode() == QListView::ListMode)
    {
        ui->listWidget->setViewMode(QListView::IconMode); //设置为图标模式
    }
    else
    {
        ui->listWidget->setViewMode(QListView::ListMode); //设置为列表模式
    }
}

//单个新增
void ItemWidgetsDialog::on_btnAddOneListView_clicked()
{
    QIcon icon1(":/images/buttonOk.png");
    ui->listWidget->addItem(new QListWidgetItem(icon1, "开启"));
}

//指定位置插入
void ItemWidgetsDialog::on_btnInsertOneListView_clicked()
{
    int row = ui->listWidget->currentRow();
    QIcon icon1(":/images/buttonOk.png");
    ui->listWidget->insertItem(row, new QListWidgetItem(icon1, "开启"));
}

//批量添加
void ItemWidgetsDialog::on_btnAddMulListView_clicked()
{
    QStringList FileNames = QFileDialog::getOpenFileNames(this,"打开",QDir::currentPath(),"所有文件(*.*);;文本文档(*.txt)");

//方法1 整体添加
    ui->listWidget->addItems(FileNames);

//方法2 逐个添加
    int count = FileNames.count();
    for(int i=0; i<count; i++)
    {
        qDebug() << FileNames.at(i);
        ui->listWidget->addItem(FileNames.at(i));
    }
}

//删除选定
void ItemWidgetsDialog::on_btnDelOneListView_clicked()
{
    int row = ui->listWidget->currentRow();
    ui->listWidget->takeItem(row);
}

//删除所有
void ItemWidgetsDialog::on_btnDelAllListView_clicked()
{
    int count = ui->listWidget->count();
    ui->listWidget->setFocus();
    for (int i=0; i<count; i++) {
        QListWidgetItem* item = ui->listWidget->takeItem(ui->listWidget->currentRow());
        if (item)
        {
            delete item;
        }
    }
}

//************Tree Widget************
//双击事件
void ItemWidgetsDialog::OnTreeItemDbClicked(QTreeWidgetItem *item, int column)
{
    QMessageBox::information(this, "温馨提示",  item->text(column));
}

//添加数据
void ItemWidgetsDialog::on_btnAddDataTreeView_clicked()
{
    QTreeWidgetItem* item1 = new QTreeWidgetItem;
    item1->setCheckState(0, Qt::Unchecked);
    item1->setIcon(1, QIcon(":/images/folder.png"));
    item1->setText(1, "照片");
    item1->setText(2, "2021-1-27 08:00");
    ui->treeWidget->addTopLevelItem(item1);

    QTreeWidgetItem* item1_1 = new QTreeWidgetItem(item1);
    item1_1->setCheckState(0, Qt::Unchecked);
    item1_1->setIcon(1, QIcon(":/images/file.png"));
    item1_1->setText(1, "1.jpg");
    item1_1->setText(2, "2021-1-27 08:00");

    QTreeWidgetItem* item1_2 = new QTreeWidgetItem(item1);
    item1_2->setCheckState(0, Qt::Unchecked);
    item1_2->setIcon(1, QIcon(":/images/file.png"));
    item1_2->setText(1, "2.jpg");
    item1_2->setText(2, "2021-1-27 08:00");
}

//获取选中数据
void ItemWidgetsDialog::on_btnGetDataTreeView_clicked()
{
    QTreeWidgetItemIterator it(ui->treeWidget);
    while(*it)
    {
        if((*it)->checkState(0) == Qt::Checked)
        {
            for(int i=0; i< (*it)->childCount(); i++)
            {
                QTreeWidgetItem* childItem = (*it)->child(i);
                QMessageBox::information(this, "温馨提示", childItem->text(1) + " " + childItem->text(2));
            }
        }
        ++it;
    }
}

//打开文件夹添加数据
void ItemWidgetsDialog::on_btnOpenFolderTreeView_clicked()
{
     QString srcDirPath = QFileDialog::getExistingDirectory(this, "选择文件夹","/");

     QDir dir(srcDirPath);
     if(!dir.exists())
     {
         return;
     }
     dir.setFilter(QDir::Dirs | QDir::Files);
     dir.setSorting(QDir::DirsFirst);//文件夹排在前面
     QFileInfoList list = dir.entryInfoList();

     QTreeWidgetItem* item1 = new QTreeWidgetItem;
     item1->setCheckState(0, Qt::Unchecked);
     item1->setIcon(1, QIcon(":/images/folder.png"));
     item1->setText(1, dir.dirName());
     item1->setText(2, "");
     ui->treeWidget->addTopLevelItem(item1);

     int i = 0;
     do
     {
         QFileInfo fileInfo = list.at(i);
         if(fileInfo.fileName() == "." | fileInfo.fileName() == "..")
         {
             ++i;
             continue;
         }

         if(fileInfo.isDir())
         {
            qDebug() << "文件夹：" << fileInfo.fileName() << fileInfo.lastModified().toString("yyyy-MM-dd hh:mm:ss");

            QTreeWidgetItem* item1_sub = new QTreeWidgetItem(item1);
            item1_sub->setCheckState(0, Qt::Unchecked);
            item1_sub->setIcon(1, QIcon(":/images/folder.png"));
            item1_sub->setText(1, fileInfo.fileName());
            item1_sub->setText(2, fileInfo.lastModified().toString("yyyy-MM-dd hh:mm:ss"));
         }
         else
         {
             //qDebug() << "groupId=" << fileInfo.groupId() << "lastModified=" << fileInfo.lastModified().toString("yyyy-MM-dd hh:mm:ss") << "absoluteFilePath=" << fileInfo.absoluteFilePath();
             qDebug() << "文件夹：" << fileInfo.fileName() << fileInfo.lastModified().toString("yyyy-MM-dd hh:mm:ss");
             QTreeWidgetItem* item1_sub = new QTreeWidgetItem(item1);
             item1_sub->setCheckState(0, Qt::Unchecked);
             item1_sub->setIcon(1, QIcon(":/images/file.png"));
             item1_sub->setText(1, fileInfo.fileName());
             item1_sub->setText(2, fileInfo.lastModified().toString("yyyy-MM-dd hh:mm:ss"));
         }
         ++i;
     }while(i < list.size());

}

//************Table Widget************
//添加数据
void ItemWidgetsDialog::on_btnAddDataTableView_clicked()
{

    //添加数据
    ui->tableWidget->setRowCount(20);
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem("1"));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(QIcon(":/images/man.png"), "张三"));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem("100"));

    ui->tableWidget->setItem(1, 0, new QTableWidgetItem("2"));
    ui->tableWidget->setItem(1, 1, new QTableWidgetItem(QIcon(":/images/man.png"), "李四"));
    ui->tableWidget->setItem(1, 2, new QTableWidgetItem("100"));

    ui->tableWidget->setItem(2, 0, new QTableWidgetItem("3"));
    ui->tableWidget->setItem(2, 1, new QTableWidgetItem(QIcon(":/images/man.png"), "王五"));
    ui->tableWidget->setItem(2, 2, new QTableWidgetItem("100"));

    //每个元素居中显示
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            ui->tableWidget->item(i, j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        }
    }

    bAddTableDataFished = true;
}

//双击表格元素槽函数
void ItemWidgetsDialog::OnItemDoubleClicked(QTableWidgetItem *item)
{
    QMessageBox::information(this, "温馨提示", item->text());
}

//表格编辑完成槽函数
void ItemWidgetsDialog::OnItemChanged(QTableWidgetItem *item)
{
    if(bAddTableDataFished){ //数据添加过程中不做处理
        QMessageBox::information(this, "温馨提示", item->text());
    }
}

//获取表格中数据
void ItemWidgetsDialog::on_btnGetDataTableView_clicked()
{
    int row = ui->tableWidget->rowCount();
    int column = ui->tableWidget->columnCount();

    QString data = "";
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<column; j++)
        {
            if(ui->tableWidget->item(i,j))
            {
                data += ui->tableWidget->item(i, j)->text() + ";";
            }
        }
        data += "\n";
    }
    QMessageBox::information(this, "温馨提示", data);
}
