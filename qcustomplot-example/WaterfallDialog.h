#ifndef WATERFALLDIALOG_H
#define WATERFALLDIALOG_H

#include <QDialog>
#include "qcustomplot.h"

namespace Ui {
class WaterfallDialog;
}

class WaterfallDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WaterfallDialog(QWidget *parent = nullptr);
    ~WaterfallDialog();

    void PlotWaterfall(QCustomPlot* customPlot);

    QCustomPlot* customPlot;

    QCPColorMap* cpColorMap;

private:
    Ui::WaterfallDialog *ui;
};

#endif // WATERFALLDIALOG_H
