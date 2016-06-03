#include "Board.h"
#include <QDebug>

Board::Board()
{
   setSceneRect(0, 0, 400, 400);
   resetInput();

   // Define network topology
   vector<unsigned> topology;
   topology.push_back(400);
   topology.push_back(300);
   topology.push_back(200);
   topology.push_back(100);
   topology.push_back(10);
   ai.initializeNetwork(topology);

   // Initialize trainingset
   for(int i = 0; i < 10; ++i){
       vector< vector<int> > vector_set;
       trainingSet[i] = vector_set;
   }
}

void Board::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    render();
    /*
    string ans;
    cout << "Would you like to save this in trainset?" << endl;
    cin >> ans;
    if(ans.compare("y")){
        int val;
        cout << "what is the correct value?" << endl;
        cin >> val;
        vector<int> v(aiInput, aiInput + 400);
        trainingSet[val].push_back(v);
    }
    */
    //ai.feedForward(aiInput);
    //ai.backPropagate(correct, 0.7, 0.3);
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

