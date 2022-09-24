#include "player.h"
#include "crown.h"
#include "enums.h"
#include "field.h"
#include <QDebug>

#include "sword.h"
#include "shield.h"
#include "banner.h"
#include "spear.h"
#include "eye.h"


Player::Player()
{
    this->id = A;
}

Player::Player(int id, QString name){
    this->id = id;
    this->name = name;
}

void Player::initBasicItems()
{
    addSpareItem(createItemById(SWORD));
    addSpareItem(createItemById(SWORD));
    addSpareItem(createItemById(SWORD));
    addSpareItem(createItemById(SPEAR));
    addSpareItem(createItemById(SPEAR));
    addSpareItem(createItemById(SPEAR));
    addSpareItem(createItemById(SHIELD));
    addSpareItem(createItemById(SHIELD));
    addSpareItem(createItemById(BANNER));
    addSpareItem(createItemById(BANNER));
    addSpareItem(createItemById(EYE));
    addSpareItem(createItemById(EYE));
    addSpareItem(createItemById(CROWN));
}

void Player::setId(int id){
    this->id = id;
}

int Player::getId(){
    return this->id;
}

void Player::setName(QString name){
    this->name = name;
}

QString *Player::getName()
{
    return &this->name;
}

int Player::getResources(){
    return resources;
}

QColor* Player::getColor(){
    return this->playerColor;
}

void Player::setColor(int r, int g, int b, int a){
    this->playerColor = new QColor(r,g,b,a);
}

QVector<Item *> *Player::getSpareItems(){
    return &spareItems;
}

QVector<Item *> *Player::getActiveItems()
{
    return &activeItems;
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

void Player::spawnItem(int index, Field *target){

}

void Player::spawnItem(Item *item, Field *target){
    int pieceCost = activeItems.length() + 1;
    if(resources >= pieceCost){
        resources -= pieceCost;
        spawnItemFree(item, target);
    }
}

void Player::spawnItemById(int id, Field *target, bool free){
    foreach(Item* i, spareItems){
        if(i->id == id){
            if(free){spawnItemFree(i,target);}
            else{spawnItem(i,target);}
            break;
        }
    }
}

bool Player::canSpawnItem(){
    if(spareItems.empty()){return false;}
    return true;
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

Item *Player::createItemById(int id){
    Item* ret;
    switch(id){
        case SWORD:
            ret = new Sword(this);
            break;
        case SPEAR:
            ret = new Spear(this);
            break;
        case SHIELD:
            ret = new Shield(this);
            break;
        case BANNER:
            ret = new Banner(this);
            break;
        case EYE:
            ret = new Eye(this);
            break;
        case CROWN:
        //change after adding crown
            ret = new Crown(this);
            break;
        default:
            ret = nullptr;
    }
    return ret;
}


