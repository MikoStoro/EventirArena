#include "shield.h"
#include "field.h"
#include "board.h"

Shield::Shield(Field* curr, Player* player) : Item(curr,player){
    this->setName("Shield");
}
Shield::Shield(Player* player) : Item(player){
    this->setName("Shield");
}
Shield::Shield(Field* curr) : Item(curr){
    this->setName("Shield");
}
Shield::Shield() : Item(){
    this->setName("Shield");
}

void Shield::action(){
    QVector<Field*>* adj = this->currentField->getFields(this->movePattern);
    this->currentField->getBoard()->setWaitingItem(this, adj);
    this->markInteractions(this->adjacentFields);
}

void Shield::processInput(Field* f){
    Item* targetItem = f->getItem();
    Board* b = currentField->getBoard();

    if(this->defending){
        qDebug("defending");
        this->processDefenseInput(f);
        b->removeWaitingItem();
        return;
    }

    if(targetItem == nullptr){
        this->move(f);
        this->findDefendableItems();
        b->removeWaitingItem();
        b->changeActivePlayer();
    }
}

void Shield::markInteractions(QVector<Field*>* targets){
    foreach(Field* f, *targets){
        if(f->getItem() != nullptr){
            if(f->getItem()->getPlayer() != nullptr){
                this->currentField->getBoard()->removeActiveField(f);
            }
        }
    }
}

void Shield::resetState(){
    return;
}

void Shield::findDefendableItems(){
    Item* target;
    foreach(Field* f, *this->adjacentFields){
        target = f->getItem();
        if(target != nullptr && target->getPlayer() == this->getPlayer()){
            target->addLinkedField(this->currentField);
        }
    }
}

int Shield::receiveMessage(int messageId, Item* sender) {
    if(messageId == DEFEND){
        return TRUE;
    }else if(messageId== MOVED){
        foreach(Field* f, *this->adjacentFields){
            if(f->getItem() == sender){
                sender->addLinkedField(this->currentField);
            }
        }
    }
}
