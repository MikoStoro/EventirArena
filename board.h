#ifndef BOARD_H
#define BOARD_H
#include <QGraphicsScene>
#include <QVector>
#include "enums.h"
#include "player.h"
class Field;
class Item;
class Window;

class Board
{
private:
    int boardSize = 0;
    Field*** fields = nullptr;
    int* rowLengths;
    QGraphicsScene* scene;
    QVector<Item*> items;

    Player* activePlayer = nullptr;
    int activePlayerIndex = 0;
    QVector<Player*> players;

    int state = READY;
    Item* waitingItem = nullptr;
    QVector<Field*>* activeFields = nullptr;
    bool locked = false;

    Window* window = nullptr;

    QColor* baseFieldColor = new QColor(110,110,110, 200);
    QColor* baseBorderColor = new QColor(0,0,0,255);
    QColor* activeBorderColor = new QColor(255,255,0,255);
    QColor* specialBorderColor = new QColor(50, 255, 50 ,255);
    QColor* hoverBorderColor = new QColor(255,0,0,255);


public:
    Board();
    Board(int boardSize, QGraphicsScene* scene);
    Field* getField(int x, int y);
    bool fieldExists(int x, int y);
    int size();

    QVector<Field*>* getAdjacenFields(Field* target);
    QVector<Field*>* getAdjacentFields(int x, int y);
    int getPosition(int x);

    void setWaitingItem(Item* i = nullptr, QVector<Field*>* active = nullptr, bool locked = false);
    void removeWaitingItem(bool keepState = false);
    void setActiveFields(QVector<Field*>* a = nullptr);
    void addACtiveField(Field* f);
    void removeActiveField(Field* f);
    void addActiveField(Field* f);
    QVector<Field*>* getActiveFields();
    void setLocked(bool val);

    void setState(int state);
    int getState();

    void fieldClicked(Field* f);
    void performFieldAction(Field* f);

    void setItem(int x, int y, Item* item);

    void addPlayer(Player* player);
    void addPlayer(int id);
    void setActivePlayer(Player* player);
    void changeActivePlayer();

    void setWindow(Window* win);
    void log(QString& entry);

    QColor* getBaseFieldColor();
    QColor* getBaseBorderColor();
    QColor* getActiveBorderColor();
    QColor* getSpecialBorderColor();
    QColor* getHoverBorderColor();

    Player* getPlayer(int id);
};

#endif // BOARD_H
