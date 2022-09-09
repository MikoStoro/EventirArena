#include "item.h"

#include <QVector>
#include "pattern.h"
#include "coords.h"
#include "board.h"
#include "field.h"
#include "player.h"
#include "QDebug"

Item::Item(Field* curr, Player* player){
    curr->setItem(this);
    this->currentField = curr;
    this->createMovePattern(curr->getBoard()->size());
    this->adjacentPattern = this->movePattern;
    this->setPlayer(player);
}

Item::Item(Player* player){
    this->setPlayer(player);
}

Item::Item(Field* curr){
    this->currentField = curr;
    this->createMovePattern(curr->getBoard()->size());
    this->adjacentPattern = this->movePattern;
}

Item::Item(){}

void Item::createMovePattern(int boardSize){
    if(this->movePattern != nullptr){
        delete this->movePattern;
    }
    this->movePattern = new Pattern(boardSize);
    this->movePattern->makeAdjacent();
}

void Item::setPlayer(Player* player, bool active){
    this->player = player;
    if(active){player->addActiveItem(this);}
    else{player->addSpareItem(this);}
}

Player* Item::getPlayer(){
    return this->player;
}

void Item::setField(Field* curr){
    this->currentField = curr;
    if(this->currentField != nullptr){
        this->updateAdjacentFields();
    }
    if(this->movePattern == nullptr){
        delete this->movePattern;
        this->movePattern = new Pattern(curr->getBoard()->size());
        this->movePattern->makeAdjacent();
    }
}


Field* Item::getField(){
    return this->currentField;
}

void Item::updateAdjacentFields(){
    if(this->currentField != nullptr){
        if(this->adjacentFields != nullptr){delete this->adjacentFields;}
        this->adjacentFields = this->currentField->getAdjacentFields();
    }
}

void Item::action(){
    if(this->movePattern == nullptr){return;}

    QVector<Field*>* adj = this->currentField->getFields(this->movePattern);
    currentField->getBoard()->setWaitingItem(this, adj);
    this->markInteractions(adj);
}

void Item::markInteractions(QVector<Field*>* targets){
    foreach(Field* f, *targets){
        if(f->getItem() != nullptr){
            if(f->getItem()->getPlayer() == this->getPlayer()){
                currentField->getBoard()->removeActiveField(f);
            }else{
                f->highlight(SPECIAL);
            }
        }
    }
}

void Item::defend(){
    QVector<Field*>* defenders = new QVector<Field*>;
    //Board* b = this->currentField->getBoard();
    Item* temp;
    foreach(Field* f, this->linkedFields){
        temp = f->getItem();
        if(temp != nullptr && temp->receiveMessage(DEFEND,this) == TRUE){
            defenders->append(f);
            f->highlight(SPECIAL);
        }
    }
    if(!defenders->empty()){
        defenders->append(this->currentField);
        this->defending = true;
        this->currentField->getBoard()->setWaitingItem(this, defenders, true);
    }else{
        delete defenders;
        Item* a = this->attackingItem;
        Field* curr = this->currentField;
        this->destroy();
        a->resolveAttack(curr);
    }
}

bool Item::isDefended(){
    Item* temp;
    foreach(Field* f, this->linkedFields){
        temp = f->getItem();
        if(temp != nullptr && temp->receiveMessage(DEFEND,this) == TRUE){
            return true;
        }
    }
    return false;
}

void Item::processInput(Field* f){
    Item* targetItem = f->getItem();
    Board* b = currentField->getBoard();

    if(this->defending){
        this->processDefenseInput(f);
        b->removeWaitingItem();
        return;
    }

    if(targetItem == nullptr){
        this->move(f);
        this->endTurn();
    }else if(targetItem->getPlayer() != this->getPlayer()){
        b->removeWaitingItem();
        this->damage(f);
    }
}

void Item::processDefenseInput(Field* f){
    Item* attacking = this->attackingItem;
    this->defending = false;
    this->attackingItem = nullptr;
    f->getItem()->destroy();
    attacking->resolveAttack(f);
}

void Item::move(Field* f){
    if(f != nullptr){
        this->currentField->setItem(nullptr);
        this->currentField = f;
        f->setItem(this);
        this->clearLinkedFields();
        this->sendMessageAround(MOVED);
    }
}

void Item::swap(Field* f){
    if(f!= nullptr){
        Item* target = f->getItem();
        if(target == nullptr){
            this->move(f);
            return;
        }
        this->currentField->setItem(target);
        f->setItem(this);
        target->setField(this->currentField);
        this->setField(f);
    }
}

void Item::damage(Field* f){
    if(f!= nullptr){
        Item* target = f->getItem();
        if(target != nullptr){
            qDebug() << this->name + " destroys " + target->getName();
            target->receiveHit(this);
        }
    }
}

void Item::endTurn(){
    Board* b = this->currentField->getBoard();
    this->resetState();
    b->removeWaitingItem();
    b->changeActivePlayer();
}

void Item::resolveAttack(Field* f){
    if(f->getItem() == nullptr){
        this->move(f);
    }
    this->endTurn();
}

void Item::destroy(){
    foreach (Field* f, *this->adjacentFields) {
        if(f->getItem()!=nullptr){
            f->getItem()->removeLinkedField(this->currentField);
        }
    }
    this->resetState();
    this->currentField->setItem(nullptr);
    this->currentField = nullptr;
    this->getPlayer()->returnItem(this);
}


void Item::receiveHit(Item* source){
    this->attackingItem = source;
    this->defend();
}

void Item::resetState(){
    this->defending = false;
    this->attackingItem = nullptr;
    return;
}

void Item::sendMessage(int messageId){
    foreach(Field* f, this->linkedFields){
        f->getItem()->receiveMessage(messageId, this);
    }
}

void Item::sendMessageAround(int messageId){
    foreach(Field* f, *this->adjacentFields){
        if(f->getItem() != nullptr){
            f->getItem()->receiveMessage(messageId, this);
        }
    }
}

void Item::sendMessageToFields(int messageId, Pattern* pattern){
    QVector<Field*>* target = this->currentField->getFields(pattern);
    foreach(Field* f, *target){
        f->getItem()->receiveMessage(messageId, this);
    }
    delete target;
}

int Item::receiveMessage(int messageId, Item* sender){
    return PASS;
}

void Item::addLinkedField(Field* f){
    if(f != nullptr){
        this->linkedFields.append(f);
    }
}

void Item::removeLinkedField(Field* f){
    if(f!= nullptr){
        this->linkedFields.removeAll(f);
    }
}

void Item::clearLinkedFields(){
    this->linkedFields.clear();
}

QVector<Field*>* Item::getLinkedFields(){
    return &this->linkedFields;

}

QString Item::getName(){
    return this->name;
}

void Item::setName(QString newName){
    this->name = newName;
    if(this->currentField != nullptr){
        this->currentField->setText(this->name);
    }
}

QColor Item::getColor(){
    return *this->player->getColor();
}



