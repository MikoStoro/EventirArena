#ifndef PLAYER_H
#define PLAYER_H

#include "item.h"

#include <QColor>
#include <QString>

class Player
{
private:
    QString name = "player";
    QVector<Item*> spareItems;
    QVector<Item*> activeItems;
    int resources;
    int id = -1;
    QColor* playerColor = nullptr;
public:
    Player();
    Player(int id, QString name = "player");

    void initBasicItems();

    void setId(int id);
    int getId();

    void setName(QString name);
    QString* getName();
    int startingPosition = -1;
    int getStaringPosition();
    void setStartingPosition(int val);

    int getResources();

    QColor* getColor();
    void setColor(int r, int g, int b, int a = 255);

    void startTurn();

    QVector<Item*>* getSpareItems();
    QVector<Item*>* getActiveItems();
    void addSpareItem(Item* item);
    void addActiveItem(Item* item);
    void activateItem(Item* item);
    void spawnItem(int index, Field* target);
    void spawnItem(Item* item, Field* target);
    void spawnItemById(int id, Field* target, bool free = false);

    bool canSpawnItem();

    void spawnItemFree(int index, Field* target);
    void spawnItemFree(Item* item, Field* target);

    void returnItem(Field* target);
    void returnItem(Item* target);

    Item *createItemById(int id);
};

#endif // PLAYER_H
