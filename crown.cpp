#include "crown.h"
#include "board.h"
#include "field.h"

Crown::Crown(Field* curr, Player* player) : Item(curr,player){
    this->name = "Crown";
    id = CROWN;
}
Crown::Crown(Player* player) : Item(player){
    this->name = "Crown";
    id = CROWN;
}
Crown::Crown(Field* curr) : Item(curr){
    this->name = "Crown";
    id = CROWN;
}
Crown::Crown() : Item(){
    this->name = "Crown";
    id = CROWN;
}

void Crown::action(int state){
    if(this->movePattern == nullptr){return;}
    QVector<Field*>* adj = currentField->getFields(this->movePattern);
    adj->append(currentField);
    board->setWaitingItem(this, adj, state);
    markInteractions(adj);
}

void Crown::switchMode(){
    if(this->spawnMode){
        this->spawnMode = false;
        this->setName("Crown");
    }else{
        if(!player->canSpawnItem()){
            QString entry = QString("%1 cannot perform spawn action right now").arg(fullName());
            return;
        }
        spawnMode = true;
        setName("Crown*");
    }
}

void Crown::processInput(Field* f){
    Item* targetItem = f->getItem();
    Board* b = currentField->getBoard();

    if(this->defending){
        processDefenseInput(f);
        b->removeWaitingItem();
        return;
    }

    if(targetItem == this){
        switchMode();
        b->removeWaitingItem();
        this->action();
        return;
    }
    if(!spawnMode){
        if(targetItem == nullptr){
            move(f);
            endTurn();
        }else{
            targetItem->destroy();
            move(f);
            endTurn();
        }
    }else{
        //is in spawn mode
        b->removeWaitingItem();
        b->setWaitingItem(this);
        b->requestSpawn(f);

    }
}

void Crown::markInteractions(QVector<Field *> *targets)
{
    foreach(Field* f, *targets){
        Item* item = f->getItem();
        if(item == this){
            f->highlight(SPECIAL);
            continue;
        }
        if(spawnMode){
            if(item == nullptr){f->highlight(SPECIAL);}
            else{board->removeActiveField(f);}
        }else{
            if(item!=nullptr){
                if(item->getPlayer() == player){board->removeActiveField(f);}
                else{f->highlight(SPECIAL);}
            }

        }
      }
}


void Crown::resetState()
{
    spawnMode = false;
    defending = false;
    attackingItem = nullptr;
    setName("Crown");
}

int Crown::receiveMessage(int messageId, Item *sender)
{
    if(messageId == SPAWN_RESOLVED){
        endTurn();
    }else{
        Item::receiveMessage(messageId, sender);
    }
}

void Crown::destroy()
{
    Item::destroy();
    board->eliminatePlayer(this->player);
}
