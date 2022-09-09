#ifndef COORDS_H
#define COORDS_H


class Coords
{

public:
    int x = -1;
    int y = -1;
    Coords* next = nullptr;

    Coords();
    Coords(int initX, int initY);
    Coords(int initX, int initY, Coords* n);

    // overload operators in future
    void add(int x, int y);
    void multiply(float x);


};

#endif // COORDS_H
