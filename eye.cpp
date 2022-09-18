#include "eye.h"
#include "board.h"
#include "field.h"

Eye::Eye(Field* curr, Player* player) : Item(curr, player){this->name = "Eye";    id = EYE;}
Eye::Eye(Player* player) : Item(player){this->name = "Eye"; id = EYE;}
Eye::Eye(Field* curr) : Item(curr){this->name = "Eye"; id = EYE;}
Eye::Eye() : Item(){this->name = "Eye"; id = EYE;}

void Eye::action(bool locked) {
    if(this->moveCounter >= 3){
        this->resetState();
        this->endTurn();
        return;
    }

     if(this->movePattern == nullptr){return;}
     QVector<Field*>* adj = this->currentField->getFields(this->movePattern);
     this->currentField->getBoard()->setWaitingItem(this, adj, locked);
     this->markInteractions(adj);
}
void Eye::processInput(Field* f) {
    Item* targetItem = f->getItem();
    Board* b = currentField->getBoard();

    if(this->defending){
        this->processDefenseInput(f);
        b->removeWaitingItem();
        return;
    }

    this->moveCounter++;
    if(targetItem == nullptr){
        this->move(f);
    }else{
        this->swap(f);
    }
    b->removeWaitingItem();
    this->action(true);
}

void Eye::markInteractions(QVector<Field*>* targets) {
    foreach(Field* f, *targets){
        if(f->getItem() != nullptr){
            f->highlight(SPECIAL);
        }
    }
}
void Eye::resetState() {
    this->moveCounter = 0;
    Item::resetState();
    return;
}
