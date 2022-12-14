#ifndef ITEM_H
#define ITEM_H

#include <QString>
#include <QColor>
#include "pattern.h"
#include "enums.h"

class Pattern;
class Field;
class Player;
class Board;

class Item {
protected:
    QString name = "dude";
    Player* player = nullptr;
    Pattern* movePattern = nullptr;
    Pattern* adjacentPattern = nullptr;
    Field* currentField = nullptr;

    QVector<Field*> linkedFields;
    bool defending = false;
    bool locked = false;
    Item* attackingItem = nullptr;
    QVector<Field*>* adjacentFields = nullptr;

    virtual void createMovePattern(int boardSize);

public:
    Item(Field* curr, Player* player);
    Item(Player* player);
    Item(Field* curr);
    Item();

    int id = -1;

    Board* board = nullptr;

    virtual void setField(Field* curr);
    Field* getField();
    virtual void updateAdjacentFields();

    void setPlayer(Player* player, bool active = false);
    Player* getPlayer();

    virtual void action(int state = WAITING);
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
    virtual void pass();
    virtual void defend();
    virtual void receiveHit(Item* source);
    virtual void resetState();
    virtual bool isDefended();
    virtual bool isLocked();

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
    QString fullName();
    void setName(QString name);
    QColor getColor();
};

#endif // ITEM_H
