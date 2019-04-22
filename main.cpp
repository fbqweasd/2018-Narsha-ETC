#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //인코딩 setup
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("eucKR"));


    w.show();

    return a.exec();
}
