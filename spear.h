#ifndef SPEAR_H
#define SPEAR_H


#include "player.h"

struct fieldPair{
    Field* collision = nullptr;
    Field* move = nullptr;

    bool operator ==(const fieldPair& b)const {
        return (this->collision == b.collision) && (this->move == b.move);
    }
};

class Spear : public Item{
private:
    Pattern* collisionPattern = nullptr;
    //first for collision field, second for move field
    QVector<fieldPair>* fieldBuffer = new QVector<fieldPair>;
    void createMovePattern(int boardSize) override;
    QVector<Field*>* processCollisions();
    void resetFieldBuffer();
    void clearFieldBuffer();

public:
    Spear(Field* curr, Player* player);
    Spear(Player* player);
    Spear(Field* curr);
    Spear();

    void action(bool locked = false) override;
    void processInput(Field* f) override;
    void markSpearInteractions();
    void resolveMove(Field* f) override;
    void resetState() override;
};

#endif // SPEAR_H
