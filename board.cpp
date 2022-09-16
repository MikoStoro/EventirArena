#include "board.h"
#include "graphichexagon.h"
#include "field.h"
#include "item.h"
#include "window.h"

#include <QDebug>

Board::Board(){   }
Board::Board(int boardSize, QGraphicsScene* scene){

    this->scene = scene;
    this->boardSize = boardSize;
    this->fields = new Field**[boardSize*2-1];
    this->rowLengths = new int[boardSize*2-1];

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
            qDebug() << yindex << " " << j << " " << boardSize+i+1 << " " << boardSize*2-1 << '\n';
            fields[yindex][j] = field;

            scene->addItem(hex);
            currentX += dist;
        }
        rowX += 0.5*dist;
        rowY -= dist*v3/2;
    }
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

    void Board::setWaitingItem(Item* i, QVector<Field*>* active, bool locked){
        if(this->state == READY){
            this->state = WAITING;
            this->waitingItem = i;
            this->setActiveFields(active);
            this->locked = locked;
        }

    }

    void Board::removeWaitingItem(bool respectLock){
        if(locked && respectLock){return;}
        if(this->state == WAITING){
            this->state = READY;
            //if(!keepState){this->waitingItem->resetState();}
            this->waitingItem = nullptr;
            this->setActiveFields(nullptr);
            this->locked = false;
        }
    }

    void Board::setLocked(bool val){
        this->locked = val;
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

    void Board::removeActiveField(Field* f){
        if(this->activeFields->contains(f)){
            this->activeFields->removeOne(f);
            f->highlight(NONE);
            if(this->activeFields->empty()){
                this->waitingItem->receiveMessage(NO_FIELDS, nullptr);
                qDebug("No suitable fields");
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
        if(state == WAITING){
            if(this->activeFields->contains(f)){
                if(this->waitingItem != nullptr){
                    qDebug() << "Clicked highlighted field";
                    this->waitingItem->processInput(f);
                }
            }else{
                if(!this->locked){
                    this->removeWaitingItem();
                    this->performFieldAction(f);
                }
            }
        }

        else if(state == READY){
            this->performFieldAction(f);
        }
    }

    void Board::performFieldAction(Field* f){
        if(f->getItem() != nullptr){
            Item* item = f->getItem();

            if(item->getPlayer()==this->activePlayer){
                qDebug() << "Action Performed";
                f->getItem()->action();
            }else{qDebug("Wrong player");}

        }
    }

    void Board::setItem(int x, int y, Item* item){
        if(fieldExists(x,y)){
            Field* target = this->getField(x,y);
            target->setItem(item);
            item->setField(target);
        }
    }

    void Board::addPlayer(Player* player){
        this->players.append(player);
    }

    void Board::addPlayer(int id){
        Player* p = new Player(id);
        this->players.append(p);
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
            qDebug("Invalid Player");
        }
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
        turnNo++;
        window->displayTurn(turnNo);
    }

    void Board::pass(){
        if(waitingItem!=nullptr && waitingItem->isDefending()){
            qDebug() << "Can't pass until board is unlocked";
            return;
        }
        if(waitingItem == nullptr){changeActivePlayer(); return;}
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

