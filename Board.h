#ifndef BOARD
#define BOARD

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <vector>
#include <map>

#include "Network.h"

using namespace std;
class Board: public QGraphicsScene{
public:
    Board();

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    map<int, vector< vector<int> > > trainingSet;
    int aiInput [400];
    vector<QGraphicsRectItem *> stroke;
    Network ai;
    void render();
    void resetInput();
};

#endif // BOARD

