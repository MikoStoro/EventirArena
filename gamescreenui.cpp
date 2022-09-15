#include "gamescreenui.h"

GameScreenUI::GameScreenUI(){
    playerLabel->setAlignment(Qt::AlignCenter);

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

void GameScreenUI::displayPiece(QString* pieceName)
{
//    QString str;
//    if(pieceName == nullptr){str = "Piece: -";}
//    else{str = "Piece: "; str.append(*pieceName);}
//    currentPlayer->setText(str);
}
