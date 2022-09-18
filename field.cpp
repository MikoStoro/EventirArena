#include "field.h"
#include "board.h"
#include "item.h"
#include "pattern.h"
#include "directions.h"
#include "graphichexagon.h"
#include <QDebug>

Field::Field()
{
    this->item = nullptr;
}

void Field::linkGraphicsHex(GraphicHexagon* hex){
    this->hex = hex;
    hex->setGameHex(this);
    this->setItem(item);
}

Field::Field(int x, int y, Board* b, Item* i){
    board = b;
    item = i;
    xPos = x;
    yPos = y;
    this->item = nullptr;
}

void Field::setPos(int x, int y){
    this->xPos = x;
    this->yPos = y;
}

void Field::setText(QString str){
    this->hex->setText(str);
}

QVector<Field*>* Field::getAdjacentFields(){
    if(this->board == nullptr){return nullptr;}

    QVector<Field*>* res = new QVector<Field*>;

    Pattern pattern(board->size());
    pattern.addOffset(0,1);
    pattern.addOffset(0,-1);
    pattern.addOffset(1,-1);
    pattern.addOffset(1,0);
    pattern.addOffset(-1,-1);
    pattern.addOffset(-1,0);


    QVector<Coords> transformed = pattern.transform(this->xPos, this->yPos);
    foreach (Coords i, transformed) {
        Field* temp = board->getField(i.x, i.y);
        if(temp != nullptr){
            res->append(temp);
        }
    }

    return res;
}

QVector<Field*>* Field::getFields(Pattern* pattern, bool includeAll){
    if(this->board == nullptr){return nullptr;}

    QVector<Field*>* res = new QVector<Field*>;

    QVector<Coords> transformed = pattern->transform(this->xPos, this->yPos);
    foreach (Coords i, transformed) {
        Field* temp = board->getField(i.x, i.y);
        if(temp != nullptr || includeAll){
            res->append(temp);
        }
    }
    return res;
}


void Field::setItem(Item* item){
    this->item = item;

    if(item!=nullptr){item->setField(this);}

    if(this->hex!=nullptr){
        if(item == nullptr){
            this->setText("");
            this->resetColor();
        }
        else{
            this->setText(item->getName());
            this->setColor(item->getColor());
        }
    }
}

void Field::clicked(){
    this->board->fieldClicked(this);
}

void Field::rightClicked()
{
    this->board->fieldRightClicked(this);
}


Board* Field::getBoard(){
       return this->board;

}

Item* Field::getItem(){
    return this->item;
}


void Field::highlight(int mode){
    this->hex->highlight(mode);
}

void Field::setColor(QColor color){
    this->hex->setColor(color);
}

void Field::setColor(int r, int g, int b, int a){
    QColor c = QColor(r,g,b,a);
    this->hex->setColor(c);
}

void Field::resetColor(){
    this->hex->resetColor();
}

int Field::getX(){
    return this->xPos;
}

int Field::getY(){
    return this->yPos;
}

double Field::getTrueX(){
    return hex->getX();
}
double Field::getTrueY(){
    return hex->getY();
}
