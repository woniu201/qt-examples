#ifndef MAPDIALOG_H
#define MAPDIALOG_H

#include <QDialog>
#include <QWebEngineView>

namespace Ui {
class MapDialog;
}

class MapDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MapDialog(QWidget *parent = nullptr);
    ~MapDialog();

    QWebEngineView* view;

private:
    Ui::MapDialog *ui;

    virtual void keyPressEvent(QKeyEvent *event);

};

#endif // MAPDIALOG_H
