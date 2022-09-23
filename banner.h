#ifndef BANNER_H
#define BANNER_H
#include "item.h"

class Banner : public Item
{
private:
    bool moved = false;
    bool specialAction = false;
    Item* actionTarget = nullptr;

public:
    Banner(Field* curr, Player* player);
    Banner(Player* player);
    Banner(Field* curr);
    Banner();

    void action(int state = WAITING) override;
    void markInteractions(QVector<Field*>* targets) override;
    void markSpecialInteractions(QVector<Field*>* targets);

    void processInput(Field* f) override;
    int receiveMessage(int messageId, Item* sender) override;
    void resetState() override;
    void moveTarget(Item* target);
};

#endif // BANNER_H
