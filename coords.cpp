#include "coords.h"

Coords::Coords(){}

Coords::Coords(int initX, int initY){
    this->x = initX;
    this->y = initY;
}

Coords::Coords(int initX, int initY, Coords* n){
    this->x = initX;
    this->y = initY;
    this->next = n;
}


void Coords::add(int x, int y){
    this->x += x;
    this->y += y;
}

void Coords::multiply(float x){
    this->x *= x;
    this->y *= x;
}
