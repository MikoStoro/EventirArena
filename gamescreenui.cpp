#include "gamescreenui.h"
#include "window.h"
#include <QObject>
#include "board.h"

GameScreenUI::GameScreenUI(Window* win){
    turnLabel->setAlignment(Qt::AlignCenter);
    playerLabel->setAlignment(Qt::AlignCenter);
    goldLabel->setAlignment(Qt::AlignCenter);
    this->window = win;
    passBtn->connect(passBtn, &QPushButton::released, win, &Window::pass);

    piecesMenu = new QMenu(win);


    Board* b = window->getBoard();
    SpawnAction* a = new SpawnAction("Sword", SWORD, piecesMenu);
    a->connect(a, &QAction::triggered, this, [this](){window->getBoard()->spawnItem(SWORD);});
    actions->insert(SWORD,a);
    a = new SpawnAction("Spear", SPEAR, piecesMenu);
    a->connect(a, &QAction::triggered, this, [this](){window->getBoard()->spawnItem(SPEAR);});
    actions->insert(SPEAR,a);
    a = new SpawnAction("Shield", SHIELD, piecesMenu);
    a->connect(a, &QAction::triggered,this, [this](){window->getBoard()->spawnItem(SHIELD);});
    actions->insert(SHIELD,a);
    a = new SpawnAction("Banner", BANNER, piecesMenu);
    a->connect(a, &QAction::triggered, this, [this](){window->getBoard()->spawnItem(BANNER);});
    actions->insert(BANNER,a);
    a = new SpawnAction("Eye", EYE, piecesMenu);
    a->connect(a, &QAction::triggered, this, [this](){window->getBoard()->spawnItem(EYE);});
    actions->insert(EYE,a);

    foreach(SpawnAction* a, actions->values()){
        piecesMenu->addAction(a);
    }
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

void GameScreenUI::displayPieces(int x, int y, Player* player){
    updatePieces(player);
    QSize s = piecesMenu->sizeHint();
    piecesMenu->setGeometry(x,y,s.width(), s.height());
    piecesMenu->exec(QCursor::pos());
}

void GameScreenUI::updatePieces(Player *player){
    foreach(SpawnAction* a, actions->values()){ a->resetCount(); a->setEnabled(true);}
    foreach(Item* i, *player->getSpareItems()){
        actions->value(i->id)->countUp();
    }
    foreach(SpawnAction* a, actions->values()){
        a->updateText();
        if(a->getCount() == 0){a->setEnabled(false);}
    }


}

void GameScreenUI::hidePieces(){
    piecesMenu->hide();
}

