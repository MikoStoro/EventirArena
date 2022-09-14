#ifndef PATTERN_H
#define PATTERN_H

#include "coords.h"
#include <QVector>

class Pattern
{
private:
    QVector<Coords> offsets;
    int boardCenter = -1;

public:
    Pattern(int boardCenter);
    int getSize();
    void addOffset(int x, int y);
    void addOffset(Coords c);
    Coords getOffset(int index);
    QVector<Coords> transform(int initX, int initY);
    QVector<Coords> transform(Coords origin);
    int getBoardPart(Coords origin);
    int getBoardPart(int x);


    int distanceFromCenter(int x);
    int pickSmaller(int a, int b);

    bool isUpward(Coords c);
    bool isDownward(Coords c);
    Coords fix(Coords c, int initX, Coords o);


    void makeAdjacent();

};

#endif // PATTERN_H
