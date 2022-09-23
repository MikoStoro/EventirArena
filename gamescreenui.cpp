#include "gamescreenui.h"
#include "window.h"
#include <QObject>
#include "board.h"

GameScreenUI::GameScreenUI(Window* win){
    this->window = win;
    QVBoxLayout* mainLayout = new QVBoxLayout;

    QHBoxLayout* gameLayout = new QHBoxLayout;
    mainLayout->addLayout(gameLayout);

    piecesSidebar = new QWidget(win);
    QVBoxLayout* piecesSidebarLayout = new QVBoxLayout;
    piecesSidebar->setLayout(piecesSidebarLayout);
    piecesSidebar->setVisible(false);

    gameLayout->addWidget(piecesSidebar);
    gameLayout->addWidget(win->getView());

    QHBoxLayout* UILayout = new QHBoxLayout;
    mainLayout->addLayout(UILayout);


    QVBoxLayout* dataPanel = new QVBoxLayout;

    //dataPanel->addWidget(gameUI.turnLabel);
    dataPanel->addWidget(playerLabel);
    dataPanel->addWidget(goldLabel);
    dataPanel->addWidget(passBtn);

    UILayout->addLayout(dataPanel);
    UILayout->addWidget(gameLog);
    gameLog->setReadOnly(true);


    win->setLayout(mainLayout);


    turnLabel->setAlignment(Qt::AlignCenter);
    playerLabel->setAlignment(Qt::AlignCenter);
    goldLabel->setAlignment(Qt::AlignCenter);

    passBtn->connect(passBtn, &QPushButton::released, win, &Window::pass);

    piecesMenu = new QMenu(win);

    SpawnAction* a = new SpawnAction("Sword", SWORD, piecesMenu);
    a->connect(a, &QPushButton::released, this, [this](){window->getBoard()->spawnItem(SWORD);});
    actions->insert(SWORD,a);
    a = new SpawnAction("Spear", SPEAR, piecesMenu);
    a->connect(a, &QPushButton::released, this, [this](){window->getBoard()->spawnItem(SPEAR);});
    actions->insert(SPEAR,a);
    a = new SpawnAction("Shield", SHIELD, piecesMenu);
    a->connect(a, &QPushButton::released,this, [this](){window->getBoard()->spawnItem(SHIELD);});
    actions->insert(SHIELD,a);
    a = new SpawnAction("Banner", BANNER, piecesMenu);
    a->connect(a, &QPushButton::released, this, [this](){window->getBoard()->spawnItem(BANNER);});
    actions->insert(BANNER,a);
    a = new SpawnAction("Eye", EYE, piecesMenu);
    a->connect(a, &QPushButton::released, this, [this](){window->getBoard()->spawnItem(EYE);});
    actions->insert(EYE,a);
    a = new SpawnAction("Crown", CROWN, piecesMenu);
    a->connect(a, &QPushButton::released,this, [this](){window->getBoard()->spawnItem(CROWN);});
    actions->insert(CROWN,a);

    foreach(SpawnAction* a, actions->values()){
        piecesSidebarLayout->addWidget(a);
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

void GameScreenUI::displayPieces(Player* player){
    updatePieces(player);
    piecesSidebar->setVisible(true);
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
    piecesSidebar->setVisible(false);
}

