#ifndef BOARD
#define BOARD

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <vector>

using namespace std;
class Board: public QGraphicsScene{
public:
    Board();

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    int aiInput [400];
    vector<QGraphicsRectItem *> stroke;
    void render();
    void resetInput();
};

#endif // BOARD

