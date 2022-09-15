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
    GameScreenUI gameUI;

    Board* board;


    void initMenuScreen();
    void clearScreen();
public:
    explicit Window(QWidget *parent = nullptr);

    void initGameScreen();

    Board* getBoard();
    void setBoard(Board* b);
    void setView(QGraphicsView* view);

    //game functions
    void log(QString& entry);
    void displayPlayer(QString* player = nullptr, QColor* col = nullptr);

signals:

};


#endif // WINDOW_H