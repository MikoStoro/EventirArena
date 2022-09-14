#ifndef ITEM_H
#define ITEM_H

#include <QString>
#include <QColor>
#include "pattern.h"

class Pattern;
class Field;
class Player;

class Item {
protected:
    QString name = "dude";
    Player* player = nullptr;
    Pattern* movePattern = nullptr;
    Pattern* adjacentPattern = nullptr;
    Field* currentField = nullptr;
    QVector<Field*> linkedFields;
    bool defending = false;
    Item* attackingItem = nullptr;
    QVector<Field*>* adjacentFields = nullptr;

    virtual void createMovePattern(int boardSize);

public:
    Item(Field* curr, Player* player);
    Item(Player* player);
    Item(Field* curr);
    Item();

    virtual void setField(Field* curr);
    Field* getField();
    virtual void updateAdjacentFields();

    void setPlayer(Player* player, bool active = false);
    Player* getPlayer();

    virtual void action(bool locked = false);
    virtual void markInteractions(QVector<Field*>* targets);
    //virtual void markDefense();
    virtual void processInput(Field* f);
    virtual void processDefenseInput(Field* f);

    virtual void move(Field* f);
    virtual void swap(Field* f);
    virtual void damage(Field* f);
    virtual void destroy();
    virtual void resolveMove(Field* f);
    virtual void endTurn();
    virtual void defend();
    virtual void receiveHit(Item* source);
    virtual void resetState();
    virtual bool isDefended();

    virtual void sendMessage(int messageId);
    virtual void sendMessageAround(int messageId);
    virtual void sendMessageToFields(int messageId, Pattern* pattern);
    virtual int receiveMessage(int messageId, Item* sender = nullptr);
    void addLinkedField(Field* f);
    void removeLinkedField(Field* f);
    void clearLinkedFields();
    QVector<Field*>* getLinkedFields();
    QVector<Field*>* getAdjacenFields();

    QString getName();
    void setName(QString name);
    QColor getColor();
};

#endif // ITEM_H
