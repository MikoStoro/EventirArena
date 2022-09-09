#include <math.h>
#include <QPolygonF>

void createHex(){
QPolygonF hexagon;
    const float v3 = sqrt(3);
    const float size = 50.0;
    hexagon <<
               QPointF(0,0) <<
               QPointF(2*size,0) <<
               QPointF(3*size, v3*size) <<
               QPointF(2*size, 2*v3*size) <<
               QPointF(0,2*v3*size)<<
               QPointF(-1*size, v3*size);
}


void createBoard(){
    int size = 1;
    int boardSize = 5;
    int currentX = 0;
    int currentY = 0;
    int rowX = 0;
    int rowY = 0;
    for(int i = 0; i < boardSize; i++){
        currentX = rowX;
        currentY = rowY;
        for (int j = 0; j < boardSize+i; j++){
            //QGraphicsEllipseItem* field = new QGraphicsEllipseItem(currentX,currentY,size,size);
            //scene->addItem(field);
            currentX += size;
        }
        rowX -= 0.5*size;
        rowY -= sqrt(((size*size))-((size*size*0.25)));
    }

    rowX += size;

    for(int i = boardSize-2; i >= 0; i--){
        currentX = rowX;
        currentY = rowY;
        for (int j = 0; j < boardSize+i; j++){
            //QGraphicsEllipseItem* field = new QGraphicsEllipseItem(currentX,currentY,size,size);
            //scene->addItem(field);
            currentX += size;
        }
        rowX += 0.5*size;
        rowY -= sqrt(((size*size))-((size*size*0.25)));


//        int boardSize = 5;
//        double currentX = 0;
//        double currentY = 0;
//        double rowX = 0;
//        double rowY = 0;
//        double dist = size*v3;
//        for(int i = 0; i < boardSize; i++){
//            currentX = rowX;
//            currentY = rowY;
//            for (int j = 0; j < boardSize+i; j++){
//                GraphicHexagon* field = new GraphicHexagon(currentX, currentY, size);
//                QString str = QString::number(i) + "," + QString::number(j);
//                field->setText(str, scene);
//                scene->addItem(field);
//                currentX += dist;
//            }
//            rowX -= 0.5*dist;
//            rowY -= dist*v3/2;
//        }

//        rowX += dist;

//        for(int i = boardSize-2; i >= 0; i--){
//            currentX = rowX;
//            currentY = rowY;
//            for (int j = 0; j < boardSize+i; j++){
//                GraphicHexagon* field = new GraphicHexagon(currentX, currentY, size);
//                QString str = QString::number(-1*i + boardSize +1) + "," + QString::number(j);
//                field->setText(str, scene);
//                scene->addItem(field);
//                currentX += dist;
//            }
//            rowX += 0.5*dist;
//            rowY -= dist*v3/2;
//        }
    }
}


//            int boardSize = 5;
//            double currentX = 0;
//            double currentY = 0;
//            double rowX = 0;
//            double rowY = 0;
//            double dist = size*v3;
//            for(int i = 0; i < boardSize; i++){
//                currentX = rowX;
//                currentY = rowY;
//                for (int j = 0; j < boardSize+i; j++){
//                    GraphicHexagon* field = new GraphicHexagon(currentX, currentY, size);
//                    QString str = QString::number(i) + "," + QString::number(j);
//                    field->setText(str, scene);
//                    scene->addItem(field);
//                    currentX += dist;
//                }
//                rowX -= 0.5*dist;
//                rowY -= dist*v3/2;
//            }

//            rowX += dist;

//            for(int i = boardSize-2; i >= 0; i--){
//                currentX = rowX;
//                currentY = rowY;
//                for (int j = 0; j < boardSize+i; j++){
//                    GraphicHexagon* field = new GraphicHexagon(currentX, currentY, size);
//                    QString str = QString::number(boardSize*2-i-2) + "," + QString::number(j);
//                    field->setText(str, scene);
//                    scene->addItem(field);
//                    currentX += dist;
//                }
//                rowX += 0.5*dist;
//                rowY -= dist*v3/2;
//            }
