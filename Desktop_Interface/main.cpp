#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef PLATFORM_ANDROID
    //Android default font sizes are just plain ridiculous
    QFont font = qApp->font();
    font.setPointSize(8);
    qApp->setFont(font);
#endif

    MainWindow w;
    w.show();

    return a.exec();
}
