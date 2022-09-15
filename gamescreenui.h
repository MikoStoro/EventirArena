#ifndef GAMESCREENUI_H
#define GAMESCREENUI_H


#include <QPushButton>
#include <QTextEdit>
#include <QLabel>

#include <QString>

class GameScreenUI{
private:
public:
    GameScreenUI();

    QPushButton* passBtn = new QPushButton("Pass");
    QTextEdit* gameLog = new QTextEdit("");
    QLabel* playerLabel = new QLabel("Player: \n -");
    QLabel* selectedPiece = new QLabel("Piece: -");


    void addToLog(QString& entry);
    void displayPlayer(QString* player = nullptr, QColor* col = nullptr);
    void displayPiece(QString* pieceName = nullptr);
};


#endif // GAMESCREENUI_H
