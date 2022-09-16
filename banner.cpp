#include "banner.h"
#include "board.h"
#include "field.h"

Banner::Banner(Field* curr, Player* player) : Item(curr,player){
    this->name = "Banner";
}
Banner::Banner(Player* player) : Item(player){
    this->name = "Banner";
}
Banner::Banner(Field* curr) : Item(curr){
    this->name = "Banner";
}
Banner::Banner() : Item(){
    this->name = "Banner";
}

void Banner::action(bool locked){
    if(this->movePattern == nullptr){return;}
    QVector<Field*>* adj = this->currentField->getFields(this->movePattern);
    this->currentField->getBoard()->setWaitingItem(this, adj, locked);
    this->markInteractions(adj);
}

void Banner::markInteractions(QVector<Field*>* targets){
    Board* b = currentField->getBoard();
    foreach(Field* f, *targets){
        Item* item = f->getItem();

        if(this->specialAction){
            if(item != nullptr){
                b->removeActiveField(f);
            }
        }

        else if(this->moved){
            if(item == nullptr || item->getPlayer()!=this->player){
                b->removeActiveField(f);
            }else if(item->getPlayer() == this->player){
                f->highlight(SPECIAL);
            }

        }else{
            //normal move
            if(item!=nullptr){
                if(item->getPlayer() == this->player){
                    f->highlight(SPECIAL);
                }else{
                    b->removeActiveField(f);
                }
            }

        }
    }

}

void Banner::processInput(Field* f){
    Board* b = currentField->getBoard();
    Item* target= f->getItem();

    if(this->defending){
        this->processDefenseInput(f);
        b->removeWaitingItem();
        return;
    }

    else if(this->specialAction){
        this->actionTarget->move(f);
        b->removeWaitingItem();
        this->resetState();
        this->actionTarget->action(true);

    }

    else if(target == nullptr){
        //empty field clicked
        this->move(f);
        this->moved = true;
        b->removeWaitingItem();
        this->action(true);

    }else if(target->getPlayer() == this->player){
        //ally clicked
        b->removeWaitingItem();
        this->moveTarget(target);
    }
}

void Banner::moveTarget(Item* target){
    QVector<Field*>* adj = target->getAdjacenFields();
    Board* b = this->currentField->getBoard();
    this->actionTarget = target;
    this->specialAction = true;
    b->setWaitingItem(this, adj, true);
    this->markInteractions(adj);
}


//void Banner::markSpecialInteractions(QVector<Field*>* targets){

//}

void Banner::resetState(){
    this->defending = false;
    this->attackingItem = nullptr;
    this->moved = false;
    this->specialAction = false;
    return;
}

int Banner::receiveMessage(int messageId, Item* sender){
    if(messageId==NO_FIELDS && (this->specialAction || this->moved)){
        this->resetState();
        this->endTurn();
        return PASS;
    }

    return Item::receiveMessage(messageId,sender);
}

