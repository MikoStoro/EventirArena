#ifndef WINDOW_H
#define WINDOW_H

#include "board.h"
#include "gamescreenui.h"
#include "qgraphicsview.h"
#include <QWidget>

#include <QPushButton>
#include <QTextEdit>
#include <QLabel>

#include <QString>

#include <QVBoxLayout>
#include <QHBoxLayout>


class Window : public QWidget
{
private:
    Q_OBJECT
    QGraphicsView* view = nullptr;
    GameScreenUI gameUI = GameScreenUI(this);

    Board* board;


    void initMenuScreen();
    void clearScreen();
protected:
void contextMenuEvent(QContextMenuEvent *event);

public:
    explicit Window(QWidget *parent = nullptr);

    void initGameScreen();

    Board* getBoard();
    void setBoard(Board* b);
    void setView(QGraphicsView* view);

    //game functions
    void log(QString& entry);
    void displayPlayer(QString* player = nullptr, QColor* col = nullptr);
    void displayTurn(int turnNo = 1);
    void displayGold(int gold = 0);
    void pass();
    void showMenu(bool mode, int x = -1, int y = -1, Player* player = nullptr);

signals:

};


#endif // WINDOW_H
