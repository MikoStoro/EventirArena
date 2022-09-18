#ifndef FIELD_H
#define FIELD_H

#include <QString>
#include <QColor>
#include <QVector>
#include "pattern.h"

class GraphicHexagon;
class Board;
class Item;

class Field{
private:
    GraphicHexagon* hex = nullptr;
    Item* item = nullptr;
    int xPos = -1;
    int yPos = -1;
    Board* board;

public:
    void linkGraphicsHex(GraphicHexagon* hex);
    Field();
    Field(int x, int y, Board* b = nullptr, Item* i = nullptr);
    void setPos(int x, int y);
    QVector<Field*>* getAdjacentFields();
    QVector<Field*>* getFields(Pattern* pattern, bool includeAll = false);
    void setItem(Item* item);
    void setText(QString str);
    void clicked();
    void rightClicked();
    Board* getBoard();
    Item* getItem();

    int getX();
    int getY();
    double getTrueX();
    double getTrueY();

    void highlight(int mode);
    void setColor(QColor color);
    void setColor(int r, int g, int b, int a);
    void resetColor();


};

#endif // FIELD_H
