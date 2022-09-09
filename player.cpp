#include "player.h"
#include "enums.h"
#include "field.h"
#include <QDebug>

Player::Player()
{
    this->id = A;
}

Player::Player(int id, QString name){
    this->id = id;
    this->name = name;
}

void Player::setId(int id){
    this->id = id;
}

int Player::getId(){
    return this->id;
}

QColor* Player::getColor(){
    return this->playerColor;
}

void Player::setColor(int r, int g, int b, int a){
    this->playerColor = new QColor(r,g,b,a);
}

void Player::addActiveItem(Item* item){
    this->activeItems.append(item);
}

void Player::addSpareItem(Item* item){
    this->spareItems.append(item);
}

void Player::activateItem(Item* item){
    if(this->spareItems.contains(item)){
        this->spareItems.removeOne(item);
    }
    if(!this->activeItems.contains(item)){
        this->activeItems.append(item);
    }
}

void Player::spawnItemFree(int index, Field* target){
    if(index < spareItems.size()){
        Item* temp = spareItems[index];
        this->spareItems.remove(index);
        this->activeItems.append(temp);
        target->setItem(temp);
    }else{
        qDebug("Item existn't");
    }
}

void Player::spawnItemFree(Item* item, Field* target){
    if(spareItems.contains(item)){
        this->spareItems.removeOne(item);
        this->activeItems.append(item);
        target->setItem(item);
    }else{
        qDebug("Item existn't");
    }
}

void Player::returnItem(Field* target){
    if(target != nullptr && target->getItem()!=nullptr){
        returnItem(target->getItem());
    }
}

void Player::returnItem(Item* target){
    if(target!=nullptr && this->activeItems.contains(target)){
        this->activeItems.removeOne(target);
        this->spareItems.append(target);
    }else{ qDebug("Item existn't"); }
}

