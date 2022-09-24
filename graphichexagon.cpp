#include "field.h"
#include <QGraphicsScene>
#include "graphichexagon.h"
#include <QDebug>
#include "board.h"
#include "item.h"
#include "enums.h"

#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>

GraphicHexagon::GraphicHexagon()
{

}

void GraphicHexagon::mousePressEvent(QGraphicsSceneMouseEvent* event){
    if(hover){
        this->pressed = true;
        this->lastPressed = event->buttons();
    }
}

void GraphicHexagon::mouseReleaseEvent(QGraphicsSceneMouseEvent* event){
    if(lastPressed & Qt::RightButton && hover && pressed){
        gHex->rightClicked();
        //gHex->getBoard()->removeWaitingItem(true);
        this->pressed = false;
        return;
    }
    else if(lastPressed & Qt::LeftButton && hover && pressed){
        if(this->gHex != nullptr){
            qDebug() << "Clicked " << gHex->getX() << gHex->getY() << '\n';
        }
        this->gHex->clicked();
        this->pressed = false;
        //qDebug("released");
    }
}

void GraphicHexagon::hoverEnterEvent(QGraphicsSceneHoverEvent* event){
    //qDebug() << "Mouse hover";
    this->hover = true;
    this->pressed = false;
    this->hoverHighlight(true);
    //this->highlightBorder();
}

void GraphicHexagon::hoverLeaveEvent(QGraphicsSceneHoverEvent* event){
    //qDebug() << "Mouse unhover";
    this->hover = false;
    this->pressed = false;
    this->hoverHighlight(false);
}

GraphicHexagon::GraphicHexagon(float centerX, float centerY, float size, QGraphicsScene* s){
    this->scene = s;
    const double v3 = sqrt(3);
    this->cX = centerX;
    this->cY = centerY;
    this->size = size;
    setAcceptHoverEvents(true);


    QPolygonF hexagon;
    float h = size/2*v3;
    float a = sqrt(size*size-h*h);

    hexagon <<
              QPointF(cX-size,cY) <<
              QPointF(cX-a, cY - h) <<
              QPointF(cX+a, cY - h) <<
              QPointF(cX+size, cY)<<
              QPointF(cX+a, cY + h)<<
              QPointF(cX-a, cY + h);

    this->setPolygon(hexagon);
    this->rotate(30);
};

void GraphicHexagon::rotate(float angle){
    this->setTransformOriginPoint(cX,cY);
    this->setRotation(angle);
};

void GraphicHexagon::setText(QString& text){
    if(textField == nullptr && this->scene == nullptr){return;}
    if(textField == nullptr && this->scene != nullptr){
        textField = new QGraphicsSimpleTextItem;
        this->scene->addItem(textField);
    }
    textField->setText(text);
    QRectF temp = textField->sceneBoundingRect();
    textField->setPos(cX - temp.width()/2, cY-temp.height()/2);
}

void GraphicHexagon::setGameHex(Field* hex){
    this->gHex = hex;
    Board* b = gHex->getBoard();
    this->borderColor = b->getBaseBorderColor();
    this->baseColor = b->getBaseFieldColor();
    this->activeColor = b->getActiveBorderColor();
    this->hoverColor = b->getHoverBorderColor();
    this->specialColor = b->getSpecialBorderColor();
    this->currentColor = this->baseColor;
    this->currentBorder = this->borderColor;
}


void GraphicHexagon::setColor(QColor& color){
    this->setBrush(QBrush(color));
}



void GraphicHexagon::setBorderColor(QColor& color){
    this->setPen(createPen(color));
}


void GraphicHexagon::setBorderColor(int r, int g, int b, int a){
    QColor c(r,g,b,a);
    this->setPen(createPen(c));
}

QPen GraphicHexagon::createPen(QColor &color){
    QPen pen;
    if(this->isBold||this->tempBold){pen.setWidthF(2);}
    pen.setColor(color);
    return pen;
}



void GraphicHexagon::setBold(bool val){
    this->isBold = val;
}

void GraphicHexagon::highlight(int mode){
    if(mode == NONE){
        this->setBold(false);
        this->zValue = NONE;
        this->resetBorder();
    }else if(mode == ACTIVE){
        this->setBold(true);
        this->zValue = ACTIVE;
        this->setBorderColor(*this->activeColor);
        this->currentBorder = this->activeColor;
        this->refreshBorder();
    }else if(mode == SPECIAL){
        this->setBold(true);
        this->zValue = SPECIAL;
        this->setBorderColor(*this->specialColor);
        this->currentBorder = this->specialColor;
        this->refreshBorder();
    }
    if(this->hover){this->zValue += HOVER;}
    this->setZValue(this->zValue);
}

void GraphicHexagon::hoverHighlight(bool val){
    if(val){
        this->tempBold = true;
        this->zValue += HOVER;
        this->setBorderColor(*this->hoverColor);
    }else{
        this->tempBold = false;
        this->zValue -= HOVER;
        this->refreshBorder();
    }
    this->setZValue(this->zValue);
}



void GraphicHexagon::setColor(int r, int g, int b, int a){
    this->setBrush(QBrush(QColor(r,g,b,a)));
}


void GraphicHexagon::resetColor(){
    Item* item = this->gHex->getItem();
    if(item == nullptr){this->setColor(*this->baseColor);}
    else{
        QColor c = item->getColor();
        this->setColor(c);
    }
}

void GraphicHexagon::refreshBorder(){
    this->setBorderColor(*this->currentBorder);
}

void GraphicHexagon::resetBorder(){
    this->isBold = false;
    this->tempBold = false;
    this->setBorderColor(*this->borderColor);
    this->currentBorder = this->borderColor;
}

void GraphicHexagon::refreshColor(){
    this->setColor(*this->currentBorder);
    this->currentColor = this->baseColor;
}

double GraphicHexagon::getX(){
    return cX;
}

double GraphicHexagon::getY(){
    return cY;
}




