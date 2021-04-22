/*
 *  在热力图的基础上添加双游标，选取一段数据，获取起始和终止位置
 *  鼠标左键点击生成游标，右键点击取消游标
 *  鼠标左键双击固定第一个游标，再双击固定第二个游标
*/
#include "CursorDialog.h"
#include "ui_CursorDialog.h"

CursorDialog::CursorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CursorDialog)
{
    ui->setupUi(this);

    ui->lineEditStart->setText("0");
    ui->lineEditEnd->setText("0");

    customPlot = ui->widget;
    PlotWaterfall(customPlot);

    bTracer1 = false;
    bTracer2 = false;

    //信号连接槽函数
    connect(customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress(QMouseEvent*)));
    connect(customPlot, SIGNAL(mouseDoubleClick(QMouseEvent*)), this, SLOT(mouseDoubleClick(QMouseEvent*)));
    connect(customPlot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)));

}

CursorDialog::~CursorDialog()
{
    delete ui;
}

/**
 * @brief 画瀑布图函数
 * @param customPlot
 */
void CursorDialog::PlotWaterfall(QCustomPlot* customPlot)
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
    customPlot->xAxis->setTickLabelFont(QFont("黑体", 10, QFont::Light));

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

    //构造游标1
    tracer1 = new QCPItemTracer(customPlot);
    tracer1->setPen(QPen(Qt::SolidLine)); //实线游标
    tracer1->setStyle(QCPItemTracer::tsCrosshair);//十字星线
    tracer1->setSize(2.0);
    tracer1->setVisible(false);

    //构建游标2
    tracer2 = new QCPItemTracer(customPlot);
    tracer2->setPen(QPen(Qt::SolidLine)); //实线游标
    tracer2->setStyle(QCPItemTracer::tsCrosshair);//十字星线
    tracer2->setSize(2.0);
    tracer2->setVisible(false);

    //立即刷新
    customPlot->rescaleAxes();//自适应大小
    customPlot->replot();
}

/**
 * @brief 鼠标点击事件
 * @param e
 */
int clickNum = 0; //用于判断是偶数双击还是单数双击
void CursorDialog::mousePress(QMouseEvent* e)
{
    QCustomPlot *curCustomPlot = qobject_cast<QCustomPlot *>(sender());
    if(curCustomPlot == customPlot)
    {
        if(e->button() == Qt::LeftButton)
        {
            bTracer1 = true;
            tracer1->setVisible(true);

            bTracer2 = true;
            tracer2->setVisible(true);
        }
        if(e->button() == Qt::RightButton)
        {
            bTracer1 = false;
            tracer1->setVisible(false);

            bTracer2 = false;
            tracer2->setVisible(false);

            clickNum = 0;
        }

        curCustomPlot->replot();
    }
}

/**
 * @brief 鼠标双击事件
 * @param e
 */
void CursorDialog::mouseDoubleClick(QMouseEvent* e)
{
    QCustomPlot *curCustomPlot = qobject_cast<QCustomPlot *>(sender());
    if(curCustomPlot == customPlot)
    {
        if(clickNum%2 == 0)
        {
            bTracer1 = false;
            tracer1->setVisible(true);
        }
        else
        {
            bTracer2 = false;
            tracer2->setVisible(true);
            bTracer1 = false; //双击时会先触发单击事件，单击时会把bTracer1置为true，所以这里重新设置为false
        }
        clickNum++;
    }
}

/**
 * @brief 鼠标移动事件
 * @param e
 */
void CursorDialog::mouseMove(QMouseEvent *e)
{
    QCustomPlot *curCustomPlot = qobject_cast<QCustomPlot *>(sender());
    if(curCustomPlot == customPlot)
    {
        if(bTracer1)
        {
            int x = curCustomPlot->xAxis->pixelToCoord(e->pos().x());
            int pos = x;
            if(pos < 0)
            {
                return ;
            }
            qDebug() << "POS:" << pos;

            tracer1->position->setCoords(pos, 0);
            tracer1->setVisible(true);
            curCustomPlot->replot();
            ui->lineEditStart->setText(QString("%1").arg(x));
        }

        if(bTracer2)
        {
            int x = curCustomPlot->xAxis->pixelToCoord(e->pos().x());
            int pos = x;
            if(pos < 0)
            {
                return ;
            }

            tracer2->position->setCoords(pos, 0);
            tracer2->setVisible(true);
            curCustomPlot->replot();
            ui->lineEditEnd->setText(QString("%1").arg(x));
        }
    }
}
