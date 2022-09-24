#include "spear.h"
#include "board.h"
#include "field.h"




Spear::Spear(Field* curr, Player* player) : Item(curr,player){
    this->name = "Spear";
    createMovePattern(this->currentField->getBoard()->size());
    id = SPEAR;
}

Spear::Spear(Player* player) : Item(player){
    this->name = "Spear";
    id = SPEAR;
}

Spear::Spear(Field* curr) : Item(curr){
    this->name = "Spear";
    createMovePattern(this->currentField->getBoard()->size());
    id = SPEAR;
}
Spear::Spear() : Item(){
    this->name = "Spear";
    id = SPEAR;
}

void Spear::createMovePattern(int boardSize){
    if(this->movePattern != nullptr){delete this->movePattern;}
    if(this->collisionPattern != nullptr){delete collisionPattern;}
    this->movePattern = new Pattern(boardSize);
    this->collisionPattern = new Pattern(boardSize);

    //order of offsets is important
    collisionPattern->addOffset(0,1);
    collisionPattern->addOffset(0,-1);
    collisionPattern->addOffset(1,-1);
    collisionPattern->addOffset(1,0);
    collisionPattern->addOffset(-1,-1);
    collisionPattern->addOffset(-1,0);

    movePattern->addOffset(0,2);
    movePattern->addOffset(0,-2);
    movePattern->addOffset(2,-2);
    movePattern->addOffset(2,0);
    movePattern->addOffset(-2,-2);
    movePattern->addOffset(-2,0);

}

void Spear::clearFieldBuffer(){
     if(this->fieldBuffer != nullptr){this->fieldBuffer->clear();}
}

void Spear::resetFieldBuffer(){
    if(this->fieldBuffer != nullptr){
        delete this->fieldBuffer;
        this->fieldBuffer = nullptr;
    }
}

QVector<Field*>* Spear::processCollisions(){
    //ret will be passed to board.setWaitingItem and will be deleted
    QVector<Field*>* ret = new  QVector<Field*>;
    foreach(fieldPair p, *fieldBuffer){
        Item* temp = nullptr;
        if(p.collision == nullptr || p.move == nullptr){fieldBuffer->removeOne(p); continue;}

        temp = p.collision->getItem();
        if(temp != nullptr && (temp->isDefended() || temp->getPlayer() == this->player)){
            this->fieldBuffer->removeOne(p); continue;
        }
        temp = p.move->getItem();
        if(p.move->getItem() != nullptr && (temp->isDefended() || temp->getPlayer() == this->player)){
            this->fieldBuffer->removeOne(p); continue;
        }
        ret->append(p.move);
    }
    return ret;
}

void Spear::action(int state) {
    this->clearFieldBuffer();
    Board* b = this->currentField->getBoard();

    QVector<Field*>* collisionTemp = this->currentField->getFields(collisionPattern, true);
    for(int i = 0; i < collisionTemp->length(); i++){
        fieldPair tempPair;
        tempPair.collision = (*collisionTemp)[i];
        this->fieldBuffer->append(tempPair);
    }

    QVector<Field*>* moveTemp  = this->currentField->getFields(movePattern, true);
    for(int i = 0; i < moveTemp->length(); i++){
        (*this->fieldBuffer)[i].move = (*moveTemp)[i];

    }

    delete collisionTemp;
    delete moveTemp;

    QVector<Field*>* activeFields = this->processCollisions();
    b->setWaitingItem(this, activeFields, state);
    this->markSpearInteractions();

}

void Spear::markSpearInteractions() {
    Field* moveField = nullptr;
    Field* collisionField = nullptr;

    foreach(fieldPair p, *fieldBuffer){
        collisionField = p.collision;
        moveField = p.move;

        if(moveField->getItem() != nullptr || collisionField->getItem() != nullptr){
            moveField->highlight(SPECIAL);
        }

        //p.collision->highlight(SPECIAL);

    }

}

void Spear::processInput(Field* f) {
    foreach(fieldPair p,*fieldBuffer){
        if(f == p.move){
            if(p.move->getItem()!=nullptr){p.move->getItem()->destroy();}
            if(p.collision->getItem()!=nullptr){p.collision->getItem()->destroy();}
            this->move(f);
            break;
        }
    }
    this->resetState();
    this->endTurn();

}


void Spear::resolveMove(Field* f) {}
void Spear::resetState() {
    Item::resetState();

}
