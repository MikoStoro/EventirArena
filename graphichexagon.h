

#ifndef GRAPHICHEXAGON_H
#define GRAPHICHEXAGON_H
#include "qwidget.h"
#include <QGraphicsPolygonItem>
#include <QGraphicsEffect>
#include <QGraphicsColorizeEffect>

class Field;
class Board;

class GraphicHexagon : public QGraphicsPolygonItem
{
private:
    double cX = 0;
    double cY = 0;
    float zValue = 0;
    float size = 0;

    bool hover = false;
    bool pressed = false;
    Qt::MouseButtons lastPressed = Qt::NoButton;

    QGraphicsSimpleTextItem* textField = nullptr;
    Field* gHex = nullptr;
    QGraphicsScene* scene;


    bool isBold = false;
    bool tempBold = false;
    QColor* borderColor = nullptr;
    QColor* baseColor = nullptr;
    QColor* hoverColor = nullptr;
    QColor* activeColor = nullptr;
    QColor* specialColor = nullptr;
    QColor* currentBorder = borderColor;
    QColor* currentColor = baseColor;

protected:
     void mousePressEvent(QGraphicsSceneMouseEvent* event);
     void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
     void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
     void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

public:
    GraphicHexagon();
    GraphicHexagon(float centerX, float centerY, float size, QGraphicsScene* s);
    void rotate(float angle);
    void setText(QString& text);
    void setGameHex(Field* hex);

    void setColor(QColor& color);
    void setColor(int r, int g, int b, int a);

    void setBorderColor(QColor& color);
    void setBorderColor(int r, int g, int b, int a);
    QPen createPen(QColor &color);

    void setBold(bool val);
    void highlight(int mode);
    void hoverHighlight(bool val);
    void resetColor();
    void refreshBorder();
    void resetBorder();
    void refreshColor();


};

#endif // GRAPHICHEXAGON_H
