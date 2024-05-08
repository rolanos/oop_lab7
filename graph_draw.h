#ifndef GRAPHDRAW_H
#define GRAPHDRAW_H

#include <QPainter>
#include "graph.h"

class GraphDraw
{

public:
    GraphDraw();
    GraphDraw(Graph);

    void draw(QPainter*, QRect);

private:
    Graph graph;

    void drawLines(QPointF*, QPainter*, int i, int j, qreal);
};

#endif // GRAPHDRAW_H
