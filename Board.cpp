

class Board{
private:
    int boardSize = 0;
    Field*** fields = NULL;
    int* rowLengths;
    QGraphicsScene* scene;

public:
    Board(int boardSize, QGraphicsScene* scene){
        this->scene = scene;
        this->boardSize = boardSize;
        this->fields = new Field**[boardSize*2-1];
        this->rowLengths = new int[boardSize*2-1];

        const float v3 = sqrt(3);
        int size = 25;
        double currentX = 0;
        double currentY = 0;
        double rowX = 0;
        double rowY = 0;
        double dist = size*v3;


        for(int i = 0; i < boardSize; i++){
            this->fields[i] = new Field*[boardSize+i];
            this->rowLengths[i] = boardSize+i;

            currentX = rowX;
            currentY = rowY;
            for (int j = 0; j < boardSize+i; j++){
                GraphicHexagon* hex = new GraphicHexagon(currentX, currentY, size);

                Field* field = new Field(i,j, NONE, this);
                field->linkGraphicsHex(hex);
                fields[i][j] = field;

                QString str = QString::number(i) + "," + QString::number(j);
                hex->setText(str, scene);

                scene->addItem(hex);
                currentX += dist;
            }
            rowX -= 0.5*dist;
            rowY -= dist*v3/2;
        }

        rowX += dist;

        for(int i = boardSize-2; i >= 0; i--){
            int yindex = (boardSize*2)-i-2;

            this->fields[yindex] = new Field*[boardSize+i];
            this->rowLengths[yindex] = boardSize+i;

            currentX = rowX;
            currentY = rowY;
            for (int j = 0; j < boardSize+i; j++){
                GraphicHexagon* hex = new GraphicHexagon(currentX, currentY, size);

                Field* field = new Field(yindex,j, NONE, this);
                field->linkGraphicsHex(hex);
                qDebug() << yindex << " " << j << " " << boardSize+i+1 << " " << boardSize*2-1 << '\n';
                fields[yindex][j] = field;

                QString str = QString::number(yindex) + "," + QString::number(j);
                hex->setText(str, scene);
                scene->addItem(hex);
                currentX += dist;
            }
            rowX += 0.5*dist;
            rowY -= dist*v3/2;
        }

    }

    Field* getField(int x, int y){
        if(fieldExists(x,y)){
            return(fields[x][y]);
        }else{
            return NULL;
        }
    }

    bool fieldExists(int x, int y){
        if(y>=0 && y<boardSize*2-1){
            if(x>=0 && x>rowLengths[y]){
                return true;
            }

        }
        return false;
    }

};
