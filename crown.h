#ifndef CROWN_H
#define CROWN_H

#include "item.h"

class Crown : public Item
{
private:
    bool spawnMode = false;
public:
    Crown(Field* curr, Player* player);
    Crown(Player* player);
    Crown(Field* curr);
    Crown();

    void switchMode();
    void requestSpawn(Field* f);
    void resolveSpawn();

    void action(int state = WAITING) override;
    void processInput(Field* f) override;
    void markInteractions(QVector<Field*>* targets) override;
    void resetState() override;
    int receiveMessage(int messageId, Item* sender = nullptr) override;

};

#endif // CROWN_H
