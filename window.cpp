#include "window.h"
#include "qevent.h"
#include <QTimer>

Window::Window(QGraphicsView* view, QWidget *parent): QWidget{parent} {
    this->view = view;
    this->gameUI = new GameScreenUI(this);
    this->setWindowTitle("Eventir Arena");
    QString entry = "Game started";
    this->log(entry);

}

Board* Window::getBoard(){
    return this->board;
}

void Window::setBoard(Board* b){
    this->board = b;
    if(board!=nullptr){board->setWindow(this);}
}

void Window::setView(QGraphicsView *view)
{
    this->view = view;
}

QGraphicsView* Window::getView(){
    return this->view;
}

void Window::log(QString &entry)
{
    this->gameUI->addToLog(entry);
}

void Window::displayPlayer(QString *player, QColor *col) {
    this->gameUI->displayPlayer(player, col);
}

void Window::displayTurn(int turnNo){
    gameUI->displayTurn(turnNo);
}

void Window::displayGold(int gold){
    gameUI->displayGold(gold);
}

void Window::pass() {
    QPushButton* b = gameUI->passBtn;
    //disable pass btn for 1s
    b->setEnabled(false);
    QTimer::singleShot(1000, this, SLOT(enablePassBtn()));

    QString entry = QString("%1 passed").arg(*board->getActivePlayerName());
    log(entry);

    board->pass();
}

void Window::showMenu(Player* player)
{
    if(player != nullptr)
        gameUI->displayPieces(player);
}

void Window::hideMenu(){
    gameUI->hidePieces();
}

void Window::enablePassBtn(bool val){
    gameUI->passBtn->setEnabled(val);
}

void Window::enablePassBtn(){
    gameUI->passBtn->setEnabled(true);
}

