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

    void setId(int id);
    int getId();

    void setName(QString name);
    QString* getName();

    QColor* getColor();
    void setColor(int r, int g, int b, int a = 255);

    void addSpareItem(Item* item);
    void addActiveItem(Item* item);
    void activateItem(Item* item);
    void spawnItem(int index, Field* target);
    void spawnItem(Item* item, Field* target);

    void spawnItemFree(int index, Field* target);
    void spawnItemFree(Item* item, Field* target);

    void returnItem(Field* target);
    void returnItem(Item* target);

};

#endif // PLAYER_H
