#ifndef TGRAPH_H
#define TGRAPH_H

#include <QObject>
#include <QFile>

#include "matrix.h"

class Graph
{

public:
    Graph();
    Graph(QString);
    ~Graph();

    QString setGraph(QString);
    int getMatrixRowDimension();
    int getMatrixColumnDimension();
    //Выбор элемента матрицы
    bool getElement(int i, int j);


private:
    Matrix<bool>* matrix;
};

#endif // TGRAPH_H
