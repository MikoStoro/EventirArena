#ifndef SHIELD_H
#define SHIELD_H

#include "item.h"

class Shield : public Item {
private:
    void findDefendableItems();

public:
    Shield(Field* curr, Player* player);
    Shield(Player* player);
    Shield(Field* curr);
    Shield();

    void action(int state = WAITING) override;
    void processInput(Field* f) override;
    void markInteractions(QVector<Field*>* targets) override;
    void resetState() override;

    int receiveMessage(int messageId, Item* sender) override;
};

#endif // SHIELD_H
