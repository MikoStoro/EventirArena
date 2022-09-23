#ifndef SPAWNACTION_H
#define SPAWNACTION_H

#include <QPushButton>

class SpawnAction : public QPushButton
{
private:

    int count = 0;
    QString name = "";
    int id = -1;
public:
    explicit SpawnAction(QWidget *parent = nullptr);
    explicit SpawnAction(QString text, int id, QWidget* parent = nullptr);

    void countUp();
    void resetCount();
    int getCount();
    void updateText();
    int getId();
};

#endif // SPAWNACTION_H
