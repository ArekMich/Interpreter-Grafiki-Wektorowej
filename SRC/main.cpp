#include "mainwindow.h"
#include <QApplication>
#include <QPainter>
#include <QStyleFactory>

// <a href="https://icons8.com/icon/8555/Delete-Message-Filled">Delete message filled and other icons by Icons8</a>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << QStyleFactory::keys();
    a.setStyle(QStyleFactory::create("Fusion"));
    a.setWindowIcon(QIcon(":/MyFiles/myappico.ico"));
    MainWindow w;  //creating object MainWindow
    MainWindow *windowPtr = &w;
    windowPtr->setWindowTitle("Interpreter Grafiki Wektorowej");
    w.show(); // here we show the window
    return a.exec();
}

