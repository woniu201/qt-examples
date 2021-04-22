#include "WaterfallDialog.h"
#include "CursorDialog.h"
#include <QApplication>
#include "qcustomplot.h"

int main(int argc, char *argv[])
{
    if(QT_VERSION>=QT_VERSION_CHECK(5,6,0))
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication a(argc, argv);

    //热力图样例
    //WaterfallDialog w;

    //双游标图案例基于热力图
    CursorDialog w;
    w.show();

    return a.exec();
}
