#include "window.h"



Window::Window(QWidget *parent): QWidget{parent} {
    this->setWindowTitle("Eventir Arena");
    QString temp = "Game started";
    this->log(temp);
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

void Window::displayPlayer(QString *player, QColor *col)
{
    this->gameUI.displayPlayer(player, col);
}

void Window::initGameScreen(){
    if(this->view == nullptr){return;}

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(view);
    QHBoxLayout* UILayout = new QHBoxLayout;
    mainLayout->addLayout(UILayout);



    QVBoxLayout* dataPanel = new QVBoxLayout;

    dataPanel->addWidget(gameUI.playerLabel);
    dataPanel->addWidget(gameUI.selectedPiece);

    UILayout->addLayout(dataPanel);
    UILayout->addWidget(gameUI.gameLog);
    gameUI.gameLog->setReadOnly(true);
    UILayout->addWidget(gameUI.passBtn);

    this->setLayout(mainLayout);

}

