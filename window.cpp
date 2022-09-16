#include "window.h"



Window::Window(QWidget *parent): QWidget{parent} {
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

void Window::log(QString &entry)
{
    this->gameUI.addToLog(entry);
}

void Window::displayPlayer(QString *player, QColor *col) {
    this->gameUI.displayPlayer(player, col);
}

void Window::displayTurn(int turnNo){
    gameUI.displayTurn(turnNo);
}

void Window::displayGold(int gold){
    gameUI.displayGold(gold);
}

void Window::pass() {
    board->pass();
}

void Window::initGameScreen(){
    if(this->view == nullptr){return;}

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(view);
    QHBoxLayout* UILayout = new QHBoxLayout;
    mainLayout->addLayout(UILayout);


    QVBoxLayout* dataPanel = new QVBoxLayout;

    dataPanel->addWidget(gameUI.turnLabel);
    dataPanel->addWidget(gameUI.playerLabel);
    dataPanel->addWidget(gameUI.goldLabel);

    UILayout->addLayout(dataPanel);
    UILayout->addWidget(gameUI.gameLog);
    gameUI.gameLog->setReadOnly(true);
    UILayout->addWidget(gameUI.passBtn);

    this->setLayout(mainLayout);

}

