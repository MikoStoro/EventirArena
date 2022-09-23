#include "spawnaction.h"

SpawnAction::SpawnAction(QWidget *parent): QPushButton(parent){

}

SpawnAction::SpawnAction(QString text, int id, QWidget *parent):QPushButton(text,parent){
    this->id = id;
    this->name = text;
}

void SpawnAction::countUp(){
    count++;
}

void SpawnAction::resetCount(){
    count = 0;
}

void SpawnAction::updateText(){
    QString temp = QString("%1: %2").arg(name,QString::number(count));
    this->setText(temp);
}

int SpawnAction::getId(){
    return id;
}

int SpawnAction::getCount(){
    return count;
}
