#include "sword.h"
#include "board.h"
#include "field.h"


Sword::Sword(Field* curr, Player* player) : Item(curr,player){
    this->name = "Sword";         id = SWORD;
}
Sword::Sword(Player* player) : Item(player){
    this->name = "Sword";id = SWORD;
}
Sword::Sword(Field* curr) : Item(curr){
    this->name = "Sword";id = SWORD;
}
Sword::Sword() : Item(){
    this->name = "Sword";id = SWORD;
}

void Sword::switchMode(){
    if(this->hitMode){
        this->hitMode = false;
        this->setName("Sword");
    }else{
        this->hitMode = true;
        this->setName("Sword*");
    }
}

void Sword::action(bool locked){
    if(this->movePattern == nullptr){return;}
    QVector<Field*>* adj = this->currentField->getFields(this->movePattern);
    adj->append(this->currentField);
    this->currentField->getBoard()->setWaitingItem(this, adj, locked);
    this->markInteractions(adj);
}

void Sword::processInput(Field* f){
    Item* targetItem = f->getItem();
    Board* b = currentField->getBoard();

    if(this->defending){
        this->processDefenseInput(f);
        b->removeWaitingItem();
        return;
    }

    if(targetItem == this){
        this->switchMode();
        b->removeWaitingItem(true);
        this->action();
        return;
    }

        if(targetItem == nullptr && !this->hitMode){
            this->move(f);
            this->endTurn();
        }else if(targetItem->getPlayer() != this->getPlayer()){
            b->removeWaitingItem();
            this->damage(f);
        }
}

void Sword::markInteractions(QVector<Field*>* targets){
        foreach(Field* f, *targets){
            if(f->getItem() != nullptr){
                Item* item = f->getItem();
                if(item == this){
                    //highlight self
                    f->highlight(SPECIAL);
                }else if(item->getPlayer() == this->getPlayer()){
                    //remove friendly targets
                    currentField->getBoard()->removeActiveField(f);
                }else if(item->isDefended() && !this->hitMode){
                    //sword cannot enter the field
                    currentField->getBoard()->removeActiveField(f);
                }else{
                    //highlight enemies
                    f->highlight(SPECIAL);
                }
            }else{
                //no target
                if(this->hitMode){
                    currentField->getBoard()->removeActiveField(f);
                }
            }
        }
}

void Sword::resolveMove(Field* f){
    if(!this->hitMode && f->getItem() == nullptr){
        this->move(f);
    }
    this->resetState();
    this->endTurn();
}

void Sword::resetState(){
    this->hitMode = false;
    this->defending = false;
    this->attackingItem = nullptr;
    this->setName("Sword");
}
