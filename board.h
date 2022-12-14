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
    Q_GADGET
    int boardSize = 0;
    Field*** fields = nullptr;
    int* rowLengths;
    int height;
    QGraphicsScene* scene;
    QVector<Item*> items;

    int turnNo = 1;
    Player* activePlayer = nullptr;
    int activePlayerIndex = 0;
    QVector<Player*> players;
    QVector<Field*> startingFields[6];
    int setupStage = 1;


    int state = READY;
    Item* waitingItem = nullptr;
    QVector<Field*>* activeFields = nullptr;


    void (Board::*processLeftClick)(Field*) = nullptr;
    void (Board::*spawn)(int id) = nullptr;

    QVector<Field*> alteredFields;
    Field* spawnField = nullptr;
    Window* window = nullptr;

    QColor* baseFieldColor = new QColor(110,110,110, 200);
    QColor* baseBorderColor = new QColor(0,0,0,255);
    QColor* activeBorderColor = new QColor(255,255,0,255);
    QColor* specialBorderColor = new QColor(50, 255, 50 ,255);
    QColor* hoverBorderColor = new QColor(255,0,0,255);


public:
    Board();
    Board(int boardSize, QGraphicsScene* scene);

    void generateStartingPositions();
    void highlightStartingPosition(Player* player);
    void assignStartingPositions();
    void setupBoard();
    void setupNextStep(Field* f);
    void endSetup();


    Field* getField(int x, int y);
    bool fieldExists(int x, int y);
    int size();



    QVector<Field*>* getAdjacenFields(Field* target);
    QVector<Field*>* getAdjacentFields(int x, int y);
    int getPosition(int x);

    void setWaitingItem(Item* i = nullptr, QVector<Field*>* active = nullptr, int newStaten = WAITING);
    void removeWaitingItem(int level = LOCKED);
    void setActiveFields(QVector<Field*>* a = nullptr);
    void addACtiveField(Field* f);
    void addAlteredField(Field* f);
    void resetAlteredFields();
    void removeActiveField(Field* f);
    void addActiveField(Field* f);
    QVector<Field*>* getActiveFields();

    void setState(int state);
    int getState();

    void fieldClicked(Field* f);
    void regularClick(Field* f);
    void setupClick(Field* f);


    void fieldRightClicked(Field* f);
    void performFieldAction(Field* f);

    void setItem(int x, int y, Item* item);
    void requestSpawn(Field* f = nullptr);
    void requestSetupSpawn(Field *f = nullptr);
    void regularSpawn(int id);
    void setupSpawn(int id);


    void addPlayer(Player* player);
    void addPlayer(int id);
    void eliminatePlayer(Player* player);
    void setActivePlayer(Player* player);
    QString* getActivePlayerName();
    void changeActivePlayer();
    int getTurnNo();
    void nextTurn();
    void pass();

    void setWindow(Window* win);
    void log(QString& entry);

    QColor* getBaseFieldColor();
    QColor* getBaseBorderColor();
    QColor* getActiveBorderColor();
    QColor* getSpecialBorderColor();
    QColor* getHoverBorderColor();

    Player* getPlayer(int id);


public slots:
    void spawnItem(int id);

};

#endif // BOARD_H
