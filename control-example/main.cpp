#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //保证设计窗口大小与实际运行时大小一致
    if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //设置程序的默认字体
    QFont font;
    font.setPointSize(12);
    font.setFamily("黑体");
    a.setFont(font);

    return a.exec();
}
