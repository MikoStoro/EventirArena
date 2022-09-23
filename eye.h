#ifndef EYE_H
#define EYE_H

#include "player.h"

class Eye : public Item {
private:
    int moveCounter = 0;
public:
    Eye(Field* curr, Player* player);
    Eye(Player* player);
    Eye(Field* curr);
    Eye();

    void action(int state = WAITING) override;
    void processInput(Field* f) override;
    void markInteractions(QVector<Field*>* targets) override;
    void resetState() override;
};

#endif // EYE_H
