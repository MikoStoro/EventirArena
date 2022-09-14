#include "board.h"
#include "field.h"
#include "graphichexagon.h"
#include "item.h"
#include "sword.h"
#include "shield.h"
#include "banner.h"
#include "spear.h"
#include "eye.h"

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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsView* view = new QGraphicsView(scene);

    Board board(5,scene);

    Player* p1 = new Player(A);
    p1->setColor(255,0,0,128);
    board.addPlayer(p1);
    Player* p2 = new Player(B);
    p2->setColor(0,0,255,128);
    board.setActivePlayer(p1);
    board.addPlayer(p2);

    Item* test = new Sword(p1);
    board.setItem(1,1,test);
    p1->activateItem(test);
    Item* test2 = new Banner(p2);
    board.setItem(5,5, test2);
    p2->activateItem(test2);
    Item* test5 = new Shield(p2);
    board.setItem(4,4, test5);
    p2->activateItem(test5);
    Item* test3 = new Spear(p1);
    board.setItem(0,2,test3);
    Item* test6 = new Eye(p1);
    board.setItem(1,2,test6);
    p1->activateItem(test6);
    Item* test4 = new Shield(p2);
    board.setItem(5,6,test4);
    p2->activateItem(test4);


    view->show();

    return a.exec();
}
