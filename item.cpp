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
    this->board = curr->getBoard();
    if(this->currentField != nullptr){
        this->updateAdjacentFields();
    }
    if(this->movePattern == nullptr){
        delete this->movePattern;
        this->createMovePattern(board->size());
//        this->movePattern = new Pattern(curr->getBoard()->size());
//        this->movePattern->makeAdjacent();
    }
}


Field* Item::getField(){
    return this->currentField;
}

void Item::updateAdjacentFields(){
    if(this->currentField != nullptr){
        if(this->adjacentFields != nullptr){
            this->adjacentFields->clear();
            delete this->adjacentFields;
        }
        this->adjacentFields = this->currentField->getAdjacentFields();
    }
}

void Item::action(bool locked){
    if(this->movePattern == nullptr){return;}

    QVector<Field*>* adj = this->currentField->getFields(this->movePattern);
    board->setWaitingItem(this, adj, locked);
    this->markInteractions(adj);
}

void Item::markInteractions(QVector<Field*>* targets){
    foreach(Field* f, *targets){
        if(f->getItem() != nullptr){
            if(f->getItem()->getPlayer() == this->getPlayer()){
                board->removeActiveField(f);
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
        this->board->setWaitingItem(this, defenders, true);
    }else{
        delete defenders;
        Item* a = this->attackingItem;
        Field* curr = this->currentField;
        this->destroy();
        a->resolveMove(curr);
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

bool Item::isDefending(){
    return defending;
}

void Item::processInput(Field* f){
    Item* targetItem = f->getItem();

    if(this->defending){
        this->processDefenseInput(f);
        board->removeWaitingItem();
        return;
    }

    if(targetItem == nullptr){
        this->move(f);
        this->endTurn();
    }else if(targetItem->getPlayer() != this->getPlayer()){
        board->removeWaitingItem();
        this->damage(f);
    }
}

void Item::processDefenseInput(Field* f){
    Item* attacking = this->attackingItem;
    this->defending = false;
    this->attackingItem = nullptr;

    if(f->getItem() != this){
        QString entry = QString("%1(%2,%3) defends %4(%5,%6)").arg(
                    f->getItem()->getName(),
                    QString::number(f->getX()),
                    QString::number(f->getY()),
                    name,
                    QString::number(currentField->getX()),
                    QString::number(currentField->getY()));
        board->log(entry);
    }
    f->getItem()->destroy();
    attacking->resolveMove(f);
}

void Item::move(Field* f){
    if(f != nullptr){
        QString entry = QString("%1: %2(%3,%4) moves to (%5,%6)").arg(
                      *player->getName(),
                      this->name,
                      QString::number(currentField->getX()),
                      QString::number(currentField->getY()),
                      QString::number(f->getX()),
                      QString::number(f->getY()));


        board->log(entry);
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

        QString entry = QString("%1: %2(%3,%4) swaps with %5(%6,%7)").arg(
                    *player->getName(),
                    name,
                    QString::number(currentField->getX()),
                    QString::number(currentField->getY()),
                    f->getItem()->getName(),
                    QString::number(f->getX()),
                    QString::number(f->getY()));
        board->log(entry);
        this->currentField->setItem(target);
        target->setField(this->currentField);
        f->setItem(this);
        this->setField(f);

        this->clearLinkedFields();
        this->sendMessageAround(MOVED);
        target->clearLinkedFields();
        target->sendMessageAround(MOVED);
    }
}

void Item::damage(Field* f){
    if(f!= nullptr){
        Item* target = f->getItem();
        if(target != nullptr){
            QString entry = QString("%1: %2 hits %3").arg(*player->getName(),fullName(),f->getItem()->fullName());
            board->log(entry);

            target->receiveHit(this);
        }
    }
}

void Item::endTurn(){
    this->resetState();
    board->removeWaitingItem();
    board->nextTurn();
}

void Item::pass()
{
    if(defending){
        qDebug() << "Can't pass until attack is resolved";
        return;
    }

    QString entry = QString("%1 passed").arg(*player->getName());
    board->log(entry);
    endTurn();
}

void Item::resolveMove(Field* f){
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

    QString entry = QString("%1 destroyed").arg(fullName());
    board->log(entry);

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
    if(messageId == RESET_STATE){
        this->resetState();
    }
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

QString Item::fullName()
{
    return QString("%1(%2,%3)").arg(
                name,
                QString::number(currentField->getX()),
                QString::number(currentField->getY()));
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

QVector<Field*>* Item::getAdjacenFields(){
    QVector<Field*>* temp = this->currentField->getAdjacentFields();
    return temp;
}



