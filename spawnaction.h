#ifndef SPAWNACTION_H
#define SPAWNACTION_H

#include <QAction>

class SpawnAction : public QAction
{
private:

    int count = 0;
    QString name = "";
    int id = -1;
public:
    explicit SpawnAction(QObject *parent = nullptr);
    explicit SpawnAction(QString text, int id, QObject* parent = nullptr);

    void countUp();
    void resetCount();
    int getCount();
    void updateText();
    int getId();
};

#endif // SPAWNACTION_H
