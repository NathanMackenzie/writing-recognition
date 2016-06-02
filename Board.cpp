#include "Board.h"
#include <QDebug>

Board::Board()
{
   setSceneRect(0, 0, 400, 400);
   resetInput();
}

void Board::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    render();
}

void Board::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //Render point on board
    int x = int (event->scenePos().x());
    int y = int (event->scenePos().y());
    QGraphicsRectItem * rect = new QGraphicsRectItem(0, 0, 10, 10);
    rect->setBrush(QBrush(Qt::blue));
    rect->setX(event->scenePos().x()-5);
    rect->setY(event->scenePos().y()-5);
    addItem(rect);

    //Add input for AI
    aiInput[((y/20)*20)+(x/20)] = 1;
}

void Board::render()
{
    // Clear board
    qDeleteAll(this->items());

    //Render AI inputs on board
    for(int c = 0; c < 20; ++c){
        for(int r = 0; r < 20; ++r){
            if(aiInput[(r*20)+c] == 1){
                QGraphicsRectItem * rect = new QGraphicsRectItem(0, 0, 20, 20);
                rect->setBrush(QBrush(Qt::black));
                rect->setX(c*20);
                rect->setY(r*20);
                addItem(rect);
            }
        }
    }
}

void Board::resetInput()
{
    for(int i = 0; i < 400; ++i){
        aiInput[i] = 0;
    }
}

