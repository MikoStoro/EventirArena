#ifndef GAMESCREENUI_H
#define GAMESCREENUI_H

#include <QPushButton>
#include <QTextEdit>
#include <QLabel>

#include <QString>

class Window;

class GameScreenUI{
private:
public:
    GameScreenUI(Window* win);

    Window* window = nullptr;

    QPushButton* passBtn = new QPushButton("Pass");
    QTextEdit* gameLog = new QTextEdit("");
    QLabel* playerLabel = new QLabel("Player: \n -");
    QLabel* turnLabel = new QLabel("Turn -");
    QLabel* goldLabel = new QLabel("Gold \n -");



    void addToLog(QString& entry);
    void displayPlayer(QString* player = nullptr, QColor* col = nullptr);
    void displayTurn(int turnNo = 1);
    void displayGold(int gold = 0);
};


#endif // GAMESCREENUI_H
