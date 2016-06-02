#include <QApplication>
#include <QCoreApplication>
#include <QGraphicsView>

#include "Board.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsView *view = new QGraphicsView(new Board());

    view->show();
    view->setFixedHeight(400);
    view->setFixedWidth(400);
    return a.exec();
}

