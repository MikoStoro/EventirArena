#ifndef SWORD_H
#define SWORD_H


#include "item.h"


class Sword : public Item{
private:
    bool hitMode = false;
public:
    Sword(Field* curr, Player* player);
    Sword(Player* player);
    Sword(Field* curr);
    Sword();

    void switchMode();

    void action() override;
    void processInput(Field* f) override;
    void markInteractions(QVector<Field*>* targets) override;
    void resolveAttack(Field* f) override;
    void resetState() override;
};

#endif // SWORD_H
