#include "board.h"
#include "graphichexagon.h"
#include "field.h"
#include "item.h"
#include "window.h"

#include <QDebug>
#include <QString>



Board::Board(){}
Board::Board(int boardSize, QGraphicsScene* scene){

    this->processLeftClick = &Board::regularClick;
    this->spawn = &Board::regularSpawn;
    this->scene = scene;
    this->boardSize = boardSize;
    this->fields = new Field**[boardSize*2-1];
    this->rowLengths = new int[boardSize*2-1];
    height = boardSize*2-1;

    const float v3 = sqrt(3);
    int size = 45;
    double currentX = 0;
    double currentY = 0;
    double rowX = 0;
    double rowY = 0;
    double dist = size*v3;

    for(int i = 0; i < boardSize; i++){
        this->fields[i] = new Field*[boardSize+i];
        this->rowLengths[i] = boardSize+i;

        currentX = rowX;
        currentY = rowY;
        for (int j = 0; j < boardSize+i; j++){
            GraphicHexagon* hex = new GraphicHexagon(currentX, currentY, size, scene);
            Field* field = new Field(i,j, this);
            field->linkGraphicsHex(hex);
            fields[i][j] = field;

            scene->addItem(hex);
            currentX += dist;
        }
        rowX -= 0.5*dist;
        rowY -= dist*v3/2;
    }

    rowX += dist;

    for(int i = boardSize-2; i >= 0; i--){
        int yindex = (boardSize*2)-i-2;

        this->fields[yindex] = new Field*[boardSize+i];
        this->rowLengths[yindex] = boardSize+i;

        currentX = rowX;
        currentY = rowY;
        for (int j = 0; j < boardSize+i; j++){
            GraphicHexagon* hex = new GraphicHexagon(currentX, currentY, size, scene);

            Field* field = new Field(yindex,j, this);
            field->linkGraphicsHex(hex);
            //qDebug() << yindex << " " << j << " " << boardSize+i+1 << " " << boardSize*2-1 << '\n';
            fields[yindex][j] = field;

            scene->addItem(hex);
            currentX += dist;
        }
        rowX += 0.5*dist;
        rowY -= dist*v3/2;
    }

}

void Board::generateStartingPositions(){
        //startingFields[0]
    int maxIndex = rowLengths[0]-1;
    for(int x = 1; x < maxIndex; x++){
        startingFields[0].append(getField(0,x));
    }


    //startingField[1]
    maxIndex = boardSize-1;
    for(int y = 1; y < maxIndex; y++){
        int x = rowLengths[y]-1;
        startingFields[1].append(getField(y, x));
    }

    //startingField[2]
    maxIndex = height-1;
    for(int y = boardSize; y < maxIndex; y++){
        int x = rowLengths[y]-1;
        qDebug() << y << x;
        startingFields[2].append(getField(y,x));
    }

    //startingField[3]
    maxIndex = rowLengths[height-1]-1;
    for(int x = 1; x<maxIndex; x++){
        startingFields[3].append(getField(height-1, x));
    }

    //startingFields[4]
    maxIndex = height-1;
    for(int y = boardSize; y < maxIndex; y++){
        startingFields[4].append(getField(y,0));
    }

    maxIndex = boardSize-1;
    for(int y = 1; y < maxIndex; y++){
        startingFields[5].append(getField(y,0));
    }

    assignStartingPositions();
}

void Board::highlightStartingPosition(Player *player){
    int posIndex = player->getStaringPosition();
    foreach(Field* f, startingFields[posIndex]){
        if(f->getItem()==nullptr){
            f->highlight(ACTIVE);
        }
    }
}

void Board::assignStartingPositions()
{
    switch(players.length()){
        case 2:
            players[0]->setStartingPosition(0);
            players[1]->setStartingPosition(3);
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
    default:
        return;

    }
}

void Board::setupBoard(){
    this->processLeftClick = &Board::setupClick;
    this->spawn = &Board::setupSpawn;
    setActivePlayer(players[0]);
    activePlayerIndex = 0;
    resetAlteredFields();
    highlightStartingPosition(activePlayer);
    window->enablePassBtn(false);
    setupStage = 1;

}

void Board::setupNextStep(Field *f){
    static bool spawnRequested = false;
    if(startingFields[activePlayer->startingPosition].contains(f)){
        if(setupStage<=players.length()){
            requestSpawn(f);
            spawnItem(CROWN);
        }else if (setupStage <= players.length()*(boardSize-2)){
            if(f->getItem() == nullptr)
                requestSetupSpawn(f);
        }else{
           endSetup();
        }
    }
}

void Board::endSetup()
{
    setupStage= 1;
    setActivePlayer(players[0]);
    activePlayerIndex = 0;
    resetAlteredFields();
    window->enablePassBtn(true);
    this->processLeftClick = &Board::regularClick;
    this->spawn = &Board::regularSpawn;
}

Field* Board::getField(int x, int y){
        if(fieldExists(x,y)){
            return(fields[x][y]);
        }else{
            return nullptr;
        }
    }

    bool Board::fieldExists(int x, int y){
        if(x>=0 && x<boardSize*2-1){
            if(y>=0 && y<rowLengths[x]){
                return true;
            }

        }
        return false;
    }

    QVector<Field*>* Board::getAdjacenFields(Field* target){
        //placeholder
        return nullptr;
    }

    int Board::size(){
        return boardSize;
    }

    int Board::getPosition(int x){
        if(x == boardSize-1){return CENTER;}
        if(x > boardSize -1){return UPPER;}
        return LOWER;
    }

    void Board::setWaitingItem(Item* i, QVector<Field*>* active, int newState){
        if(this->state == READY){
            this->state = newState;
            this->waitingItem = i;
            this->setActiveFields(active);
        }

    }

    void Board::removeWaitingItem(int level){
        if(level < state){return;}
        if(this->state != READY){
            this->state = READY;
            //if(!keepState){this->waitingItem->resetState();}
            this->waitingItem = nullptr;
            this->setActiveFields(nullptr);
        }
    }

    void Board::setState(int state){
        this->state = state;
        if(this->state == READY){this->removeWaitingItem();}
    }


    void Board::setActiveFields(QVector<Field*>* a){
        if(this->activeFields != nullptr){
            foreach (Field* f, *this->activeFields) {
                f->highlight(NONE);
            }

            delete activeFields;
        }

        this->activeFields = a;
        if(a != nullptr){
            foreach (Field* f, *this->activeFields) {
                f->highlight(ACTIVE);
            }
        }
    }

    void Board::addAlteredField(Field *f){
        alteredFields.append(f);
    }

    void Board::resetAlteredFields(){
        foreach(Field* f, alteredFields){
            f->highlight(NONE);
        }
        alteredFields.clear();
    }

    void Board::removeActiveField(Field* f){
        if(this->activeFields->contains(f)){
            this->activeFields->removeOne(f);
            f->highlight(NONE);
            if(this->activeFields->empty()){
                this->waitingItem->receiveMessage(NO_FIELDS, nullptr);
                //qDebug("No suitable fields");
                this->removeWaitingItem();
            }
        }
    }

    void Board::addActiveField(Field* f){
        if(!this->activeFields->contains(f)){
            this->activeFields->append(f);
            f->highlight(ACTIVE);
        }
    }

    int Board::getState(){
        return this->state;
    }



    void Board::fieldClicked(Field* f){
        if(processLeftClick != nullptr){
            (this->*processLeftClick)(f);
        }
    }



    void Board::regularClick(Field *f)
    {
        if(state >= WAITING){
            if(this->activeFields != nullptr && this->activeFields->contains(f)){
                if(this->waitingItem != nullptr){
                    //qDebug() << "Clicked highlighted field";
                    this->waitingItem->processInput(f);
                }
            }else{
                if(state<LOCKED){
                    window->hideMenu();
                    this->removeWaitingItem();
                    this->performFieldAction(f);
                }
            }
        }

        else if(state == READY){
            this->performFieldAction(f);
        }
    }



    void Board::setupClick(Field *f)
    {
        setupNextStep(f);
    }



    void Board::fieldRightClicked(Field *f){
        //will be changed
//        if(state == READY){
//            removeWaitingItem(WAITING);
//            spawnField = f;
//            requestSpawn(f);
//        }

        if(state<LOCKED){
            if(waitingItem != nullptr){removeWaitingItem(WAITING); window->hideMenu();}
            else{setState(READY); window->hideMenu();}
        }
    }

    void Board::spawnItem(int id){
        if(this->spawn != nullptr){
            (this->*spawn)(id);
        }
    }

    void Board::performFieldAction(Field* f){
        if(f->getItem() != nullptr){
            Item* item = f->getItem();

            if(item->getPlayer()==this->activePlayer){
                //qDebug() << "Action Performed";
                f->getItem()->action();
            }else{
                //qDebug("Wrong player");
            }
        }
    }

    void Board::setItem(int x, int y, Item* item){
        if(fieldExists(x,y)){
            Field* target = this->getField(x,y);
            target->setItem(item);
            item->setField(target);
        }
    }



    void Board::requestSpawn(Field *f){
        if(f!=nullptr && f->getItem() == nullptr){
            spawnField = f;
            f->highlight(SPECIAL);
            setState(LOCKED);
            window->showMenu(activePlayer);
        }
    }

    void Board::regularSpawn(int id)
    {
        activePlayer->spawnItemById(id,spawnField,true);
        setState(READY);
        spawnField->highlight(NONE);
        spawnField = nullptr;

        if(waitingItem != nullptr){
            waitingItem->receiveMessage(SPAWN_RESOLVED);
        }

        window->hideMenu();
    }

    void Board::setupSpawn(int id)
    {
        regularSpawn(id);
        changeActivePlayer();
        resetAlteredFields();
        highlightStartingPosition(activePlayer);
        setupStage++;
        if(setupStage > players.length()*(boardSize-2)){
            endSetup();
        }
    }

    void Board::requestSetupSpawn(Field* f){
        if(f!=nullptr && f->getItem() == nullptr){
            if(spawnField != nullptr){spawnField->highlight(ACTIVE);}
            spawnField = f;
            f->highlight(SPECIAL);
            window->showMenu(activePlayer);
        }
    }

    void Board::addPlayer(Player* player){
        this->players.append(player);
    }

    void Board::addPlayer(int id){
        Player* p = new Player(id);
        this->players.append(p);
    }

    void Board::eliminatePlayer(Player *player){
        foreach(Item* i, *player->getActiveItems()){
            i->destroy();
        }
        players.removeAll(player);
        if(players.length() == 1){
            Player* winner = players[0];
            QString entry = QString("Player %1 won!").arg(*winner->getName());
            log(entry);
        }
    }

    Player* Board::getPlayer(int id){
        foreach(Player* p, this->players){
            if(p->getId() == id){return p;}
        }
        return nullptr;
    }

    void Board::setActivePlayer(Player* player){
        if(this->players.contains(player)){
            this->activePlayer = player;
            activePlayerIndex = players.lastIndexOf(player);
            window->displayPlayer(this->activePlayer->getName(), this->activePlayer->getColor());
        }else{
            //qDebug("Invalid Player");
        }
    }

    QString *Board::getActivePlayerName(){
        return activePlayer->getName();
    }

    void Board::changeActivePlayer(){
        if(this->activePlayerIndex < players.size()-1){activePlayerIndex += 1;}
        else{this->activePlayerIndex = 0;}
        activePlayer = players[activePlayerIndex];

        window->displayPlayer(this->activePlayer->getName(), this->activePlayer->getColor());
        window->displayGold(activePlayer->getResources());
    }


    int Board::getTurnNo(){
        return turnNo;
    }

    void Board::nextTurn(){
        changeActivePlayer();
        activePlayer->startTurn();
        resetAlteredFields();
        window->hideMenu();
        turnNo++;
        window->displayTurn(turnNo);
    }

    void Board::pass(){
        if(state>=SECURE){
           //qDebug() << "Can't pass until board is unlocked";
            return;
        }
        spawnField = nullptr;
        if(waitingItem == nullptr){nextTurn(); setState(READY); return;}
        waitingItem->pass();
    }

    void Board::setWindow(Window *win){
        this->window = win;
    }

    void Board::log(QString &entry){
        if(window != nullptr){this->window->log(entry);}
    }


    QColor* Board::getBaseFieldColor(){
        return this->baseFieldColor;
    }

    QColor* Board::getBaseBorderColor(){
        return this->baseBorderColor;
    }

    QColor* Board::getActiveBorderColor(){
        return this->activeBorderColor;
    }

    QColor* Board::getSpecialBorderColor(){
        return this->specialBorderColor;
    }

    QColor* Board::getHoverBorderColor(){
        return this->hoverBorderColor;
    }

    QVector<Field*>* Board::getActiveFields(){
        return this->activeFields;
    }

