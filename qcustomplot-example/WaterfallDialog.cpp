/*
*   实现画信号的瀑布图
*/
#include "WaterfallDialog.h"
#include "ui_WaterfallDialog.h"

WaterfallDialog::WaterfallDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaterfallDialog)
{
    ui->setupUi(this);

    customPlot = ui->widget;
    PlotWaterfall(customPlot);
}

WaterfallDialog::~WaterfallDialog()
{
    delete ui;
}

/**
 * @brief 画瀑布图函数
 * @param customPlot
 */
void WaterfallDialog::PlotWaterfall(QCustomPlot* customPlot)
{
    //背景为黑色
    QLinearGradient plotGradient;
    plotGradient.setColorAt(0, QColor(0, 0, 0));
    plotGradient.setColorAt(1, QColor(0, 0, 0));
    customPlot->setBackground(plotGradient);

    //坐标轴为白色
    customPlot->xAxis->setBasePen(QPen(Qt::white, 1));
    customPlot->yAxis->setBasePen(QPen(Qt::white, 1));

    //坐标轴的提示信息为白色
    customPlot->xAxis->setTickLabelColor(Qt::white);
    customPlot->yAxis->setTickLabelColor(Qt::white);

    //可拖拽+可滚轮缩放
    customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);

    //添加标题
    customPlot->plotLayout()->insertRow(0);
    QCPTextElement* title = new QCPTextElement(customPlot, "信号瀑布图", QFont("黑体", 15, QFont::Bold));
    title->setTextColor(QColor(255, 255, 0));
    customPlot->plotLayout()->addElement(0, 0, title);

    //设置坐标轴范围，提示标签样式
    customPlot->xAxis->setRange(0, 1000);
    customPlot->yAxis->setRange(-6000,6000);
    customPlot->yAxis->ticker()->setTickCount(6);
    customPlot->yAxis->setTickLabelFont(QFont("黑体", 10, QFont::Light));

    //设置色谱范围
    cpColorMap = new QCPColorMap(customPlot->xAxis,customPlot->yAxis);
    cpColorMap->data()->setSize(1000, 12000); //设置X轴1000个点，Y轴12000个点
    cpColorMap->data()->setRange(QCPRange(0,1000),QCPRange(-6000,6000));

    //信号范围在-4000到+4000,设置数据
    for(int x=0; x<1000; x++)
    {
        for(int y=2000; y<2000+8000; y++)
        {
            cpColorMap->data()->setCell(x, y, qCos(x/10.0)+qSin(y/10.0));
        }
    }

    //构建色条
    QCPColorScale *colorScale = new QCPColorScale(customPlot);
    colorScale->setType(QCPAxis::atRight); // 刻度应为垂直条，刻度线/坐标轴标签右侧（实际上，右侧已经是默认值）
    colorScale->axis()->setLabelColor(Qt::white);
    colorScale->axis()->setTickLabelColor(Qt::white);
    colorScale->axis()->setTickLabels(false);
    colorScale->axis()->setTickLabelFont(QFont(("Arial"),10));
    colorScale->axis()->setLabel("信号强度变化");
    colorScale->axis()->setLabelFont(QFont(("Arial"), 10));
    cpColorMap->setColorScale(colorScale); // 将颜色图与色标关联

    //设置色条的颜色变化
    QCPColorGradient gradient;  // 色条使用的颜色渐变
    if(true) //默认颜色变化
    {
        cpColorMap->setGradient(QCPColorGradient::gpJet);
        cpColorMap->rescaleDataRange(true);
    }
    else    //自定义颜色变化
    {
        gradient.setColorStopAt(0.0, QColor("#f6efa6"));   // 设置色条开始时的颜色
        gradient.setColorStopAt(1.0, QColor("#bf444c"));  // 设置色条结束时的颜色
        cpColorMap->setGradient(gradient);
    }
    cpColorMap->rescaleDataRange(true);
    customPlot->plotLayout()->addElement(1, 1, colorScale); // 将其添加到主轴矩形的右侧

    //立即刷新
    customPlot->replot();
}
