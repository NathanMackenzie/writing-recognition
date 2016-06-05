#include <QApplication>
#include <QCoreApplication>
#include <QGraphicsView>

#include "Board.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*
    QGraphicsView *view = new QGraphicsView(new Board());

    view->show();
    view->setFixedHeight(400);
    view->setFixedWidth(400);
    */
    MainWindow w;
    w.show();
    return a.exec();
}

