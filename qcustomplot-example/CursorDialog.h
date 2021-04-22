#ifndef CURSORDIALOG_H
#define CURSORDIALOG_H

#include <QDialog>
#include "qcustomplot.h"

namespace Ui {
class CursorDialog;
}

class CursorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CursorDialog(QWidget *parent = nullptr);
    ~CursorDialog();

    void PlotWaterfall(QCustomPlot* customPlot);

    QCustomPlot* customPlot;
    QCPColorMap* cpColorMap;

    QCPItemTracer* tracer1;
    QCPItemTracer* tracer2;
    bool    bTracer1;
    bool    bTracer2;

private slots:
    void mousePress(QMouseEvent* e);
    void mouseDoubleClick(QMouseEvent* e);
    void mouseMove(QMouseEvent *e);

private:
    Ui::CursorDialog *ui;
};

#endif // CURSORDIALOG_H
