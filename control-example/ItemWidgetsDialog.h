#ifndef ITEMWIDGETSDIALOG_H
#define ITEMWIDGETSDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QTreeWidget>
#include <QTableWidget>

namespace Ui {
class ItemWidgetsDialog;
}

class ItemWidgetsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ItemWidgetsDialog(QWidget *parent = nullptr);
    ~ItemWidgetsDialog();

private:
    Ui::ItemWidgetsDialog *ui;
    bool bAddTableDataFished;

private slots:
    void OnItemDbClicked(QListWidgetItem *item);
    void on_btnChangeViewMode_clicked();
    void on_btnDelOneListView_clicked();
    void on_btnAddOneListView_clicked();
    void on_btnInsertOneListView_clicked();
    void on_btnAddMulListView_clicked();
    void on_btnDelAllListView_clicked();
    void on_btnAddDataTreeView_clicked();

    void OnTreeItemDbClicked(QTreeWidgetItem *item, int column);
    void on_btnGetDataTreeView_clicked();
    void on_btnOpenFolderTreeView_clicked();

    void on_btnAddDataTableView_clicked();
    void OnItemDoubleClicked(QTableWidgetItem *item);
    void OnItemChanged(QTableWidgetItem *item);
    void on_btnGetDataTableView_clicked();
};

#endif // ITEMWIDGETSDIALOG_H
