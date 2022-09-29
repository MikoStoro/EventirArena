#include "board.h"
#include "field.h"
#include "graphichexagon.h"
#include "item.h"
#include "sword.h"
#include "shield.h"
#include "banner.h"
#include "spear.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPolygonF>
#include <QGraphicsPolygonItem>
#include <QGraphicsEllipseItem>
#include <QList>
#include <QGraphicsRotation>
#include <QPointF>
#include <math.h>
#include <string>
#include <QDebug>
#include <window.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsView* view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    Window win(view);
    win.setView(view);
    Board board(5,scene);
    win.setBoard(&board);

    Player* p1 = new Player(A);
    p1->setColor(180,0,0,255);
    p1->setName(QString("Red"));
    p1->initBasicItems();
    board.addPlayer(p1);

    Player* p2 = new Player(B);
    p2->setColor(0,0,180,128);
    p2->setName(QString("Blue"));
    p2->initBasicItems();
    board.addPlayer(p2);

    Player* p3 = new Player(C);
    p3->setColor(0,180,0,255);
    p3->setName(QString("Green"));
    p3->initBasicItems();
    board.addPlayer(p3);

    board.setActivePlayer(p1);



    board.generateStartingPositions();
    board.setupBoard();


//    Item* test = new Sword(p1);
//    board.setItem(1,1,test);
//    p1->activateItem(test);
//    Item* test2 = new Banner(p2);
//    board.setItem(5,5, test2);
//    p2->activateItem(test2);
//    Item* test5 = new Shield(p2);
//    board.setItem(4,4, test5);
//    p2->activateItem(test5);
//    Item* test3 = new Spear(p1);
//    board.setItem(0,2,test3);
//    Item* test6 = new Eye(p1);
//    board.setItem(1,2,test6);
//    p1->activateItem(test6);
//    Item* test4 = new Shield(p2);
//    board.setItem(5,6,test4);
//    p2->activateItem(test4);

    win.show();

    return a.exec();
}
