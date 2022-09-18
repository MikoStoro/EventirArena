#ifndef GAMESCREENUI_H
#define GAMESCREENUI_H

#include "player.h"

#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QToolBar>
#include "spawnaction.h"
#include <QMap>
#include <QMenu>

#include <QString>

class Window;

class GameScreenUI : public QObject{
private:
    Q_GADGET
public:
    GameScreenUI(Window* win);

    Window* window = nullptr;

    QPushButton* passBtn = new QPushButton("Pass");
    QTextEdit* gameLog = new QTextEdit("");
    QLabel* playerLabel = new QLabel("Player: \n -");
    QLabel* turnLabel = new QLabel("Turn -");
    QLabel* goldLabel = new QLabel("Gold \n -");

    QMenu* piecesMenu = nullptr;

    QMap<int,SpawnAction*>* actions = new QMap<int,SpawnAction*>;


    void addToLog(QString& entry);
    void displayPlayer(QString* player = nullptr, QColor* col = nullptr);
    void displayTurn(int turnNo = 1);
    void displayGold(int gold = 0);
    void displayPieces(int x, int y, Player* player);
    void updatePieces(Player* player);
    void hidePieces();
};


#endif // GAMESCREENUI_H
