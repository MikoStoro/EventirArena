#include "gamescreenui.h"
#include "window.h"

GameScreenUI::GameScreenUI(Window* win){
    playerLabel->setAlignment(Qt::AlignCenter);
    turnLabel->setAlignment(Qt::AlignCenter);
    goldLabel->setAlignment(Qt::AlignCenter);
    this->window = win;
    passBtn->connect(passBtn, &QPushButton::released, win, &Window::pass);

}

void GameScreenUI::addToLog(QString &entry){
    gameLog->append(entry);
}

//TODO: fix the memory leak
void GameScreenUI::displayPlayer(QString* player, QColor* col){
    QString temp = "Current Player: \n";

    if(player == nullptr){temp.append("-");}
    else{temp.append(*player);}
    if(col == nullptr){*col = QColor(Qt::black);}

    playerLabel->setText(temp);
    QPalette palette = playerLabel->palette();
    palette.setColor(QPalette::WindowText, *col);
    playerLabel->setPalette(palette);
}

void GameScreenUI::displayTurn(int turnNo){
    QString temp = QString("Turn %1").arg(QString::number(turnNo));
    turnLabel->setText(temp);
}

void GameScreenUI::displayGold(int gold){
    QString temp = QString("Gold: \n %1").arg(QString::number(gold));
    turnLabel->setText(temp);
}

