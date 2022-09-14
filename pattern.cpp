#include "pattern.h"
#include "enums.h"

#include <QDebug>

Pattern::Pattern(int boardSize)
{
    this->boardCenter = boardSize-1;
}

int Pattern::getSize(){
    return this->offsets.size();
}

void Pattern::addOffset(int x, int y){
    Coords temp = Coords(x,y);
    this->offsets.append(temp);
}

void Pattern::addOffset(Coords c){
    this->offsets.append(c);
}

Coords Pattern::getOffset(int index){
    return this->offsets[index];
}

int Pattern::getBoardPart(Coords origin){
    return getBoardPart(origin.x);
}


int Pattern::distanceFromCenter(int x){
    int res = qAbs(x - this->boardCenter);
    return res;

}

int Pattern::pickSmaller(int a, int b){
    if(a < b){return a;}
    return b;
}

int Pattern::getBoardPart(int x){
    if(x == boardCenter){ return CENTER;}
    else if (x < boardCenter){return LOWER;}
    else {return UPPER;}
}

bool Pattern::isUpward(Coords c){
    if(c.x > 0){return true;}
    return false;
}

bool Pattern::isDownward(Coords c){
    if(c.x < 0){return true;}
    return false;
}

Coords Pattern::fix(Coords c, int initX, Coords o){
    int offset = pickSmaller(distanceFromCenter(initX),qAbs(o.x));
    qDebug() << distanceFromCenter(initX) << o.x << offset;
    return(Coords(c.x, c.y+offset));
}

QVector<Coords> Pattern::transform(int initX, int initY){
    QVector<Coords> result;

    for(int i = 0; i < getSize(); i++){
        Coords res(initX, initY);
        Coords offset = offsets[i];

        res.x += offset.x;
        res.y += offset.y;
        int boardPart = getBoardPart(initX);
        if((isUpward(offset) && boardPart == LOWER) || (isDownward(offset) && boardPart == UPPER)){
                res = fix(res, initX, offset);
        }

        result.append(res);
    }
    return result;
}

QVector<Coords> Pattern::transform(Coords origin){
    return transform(origin.x, origin.y);
}

void Pattern::makeAdjacent(){
    this->offsets.clear();
    addOffset(0,1);
    addOffset(0,-1);
    addOffset(1,-1);
    addOffset(1,0);
    addOffset(-1,-1);
    addOffset(-1,0);
}








